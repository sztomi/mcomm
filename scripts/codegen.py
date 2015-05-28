#!/usr/bin/python2
# vim: set fileencoding=utf-8

import sys
import os
import clang.cindex
import itertools
import re
import fnmatch
import argparse
import functools
import linecache
from multiprocessing import Pool
from mako.template import Template
from collections import defaultdict

sys.path.insert(0, '/usr/local/lib')
sys.path.insert(0, '/usr/lib')
sys.path.insert(0, os.path.expanduser('~/lib'))

def get_annotations(node):
    return [c.displayname for c in node.get_children()
            if c.kind == clang.cindex.CursorKind.ANNOTATE_ATTR]

class _Util(object):
    @staticmethod
    def split_param_list(f):
        match = re.search(r'\((.*)\)', f.source_line)
        if match:
            param_list = match.group(1).split(',')
            is_done, i, result = False, 0, []
            count = len(param_list)
            while not is_done:
                p = param_list[i].strip()
                if '<' in p and i+1 < count:
                    p += ', ' + param_list[i+1].split()[0] + ' ' + param_list[i+1].split()[1]
                    result.append(p)
                    i += 1
                else:
                    result.append(p)
                i += 1
                is_done = (i >= count)
            return result
        else:
            return []

    @staticmethod
    def header2source(header):
        return os.path.splitext(header)[0] + '.cpp'

    @staticmethod
    def tokens_to_typestr(tokenlist):
        type_str = ''
        for i, t in enumerate(tokenlist):
            if t.spelling == 'virtual' or t.spelling == 'static':
                continue
            type_str += t.spelling
            next_is_punct = ((i + 1 < len(tokenlist))
                             and tokenlist[i+1].kind == clang.cindex.TokenKind.PUNCTUATION)
            if (not next_is_punct
                and t.kind != clang.cindex.TokenKind.PUNCTUATION
                and i != len(tokenlist) - 1):
                type_str += ' '
        return type_str


class CodeObject(object):
    def __init__(self, cursor, parent=None):
        self.name = cursor.spelling
        self.annotations = get_annotations(cursor)
        loc = cursor.location
        self.source_line = linecache.getline(loc.file.name, loc.line)
        self.parent = parent


class Argument(object):
    def __init__(self, declaration):
        self.default_value = None
        self.name = declaration.split(' ')[-1]
        """ Handle default parameters """
        if '=' in declaration:
            self.default_value = declaration.split('=')[1].strip()
            tokens = re.split(r'[\s&\*=]+', declaration)
            self.name = tokens[-2]
            self.type_str = ' '.join(declaration.split('=')[0].split(' ')[:-2])
        else:
            self.type_str = ' '.join(declaration.split('=')[0].split(' ')[:-1])

        while self.name[0] == '&' or self.name[0] == '*':
            self.type_str += self.name[0]
            self.name = self.name[1:]

    def __str__(self):
        return '{} {}'.format(self.type_str, self.name)

class Function(CodeObject):
    def __init__(self, cursor):
        CodeObject.__init__(self, cursor)
        self.name = cursor.spelling
        self.arguments = []
        self.annotations = get_annotations(cursor)
        self.access = cursor.access_specifier
        self.is_static = cursor.is_static_method()
        self.is_virtual = 'virtual' in self.source_line
        # this does not work:
        # self.is_purevirtual = cursor.is_purevirtual_method()
        if re.search(r'\s*=\s*0\s*;\s*$', self.source_line):
            self.is_purevirtual = True
            self.is_virtual = False
        else:
            self.is_purevirtual = False

        """ Extract return type """
        ret_type_tokens = []
        if (cursor.kind == clang.cindex.CursorKind.CONSTRUCTOR or
           cursor.kind == clang.cindex.CursorKind.DESTRUCTOR):
            self.return_type_str = ''
        else:
            for token in cursor.get_tokens():
                if token.spelling == self.name:
                    break
                ret_type_tokens.append(token)
            self.return_type_str = _Util.tokens_to_typestr(ret_type_tokens)

        """ Extract arguments """
        param_decl_list = _Util.split_param_list(self)
        unordered_arguments = []
        for decl in param_decl_list:
            if len(decl) > 0:
                a = Argument(decl)
                unordered_arguments.append(a)
        for pd in param_decl_list:
            arg_found = False
            for ua in unordered_arguments:
                if arg_found: break
                if ua.name in pd:
                    self.arguments.append(ua)
                    arg_found = True


class Property(CodeObject):
    def __init__(self, cursor):
        CodeObject.__init__(self, cursor)
        self.name = self.name
        self.getter = None
        self.setter = None

class Class(CodeObject):
    def __init__(self, cursor):
        CodeObject.__init__(self, cursor)
        self.functions = []
        self.properties = dict()
        self.base_names = []

        if cursor.lexical_parent.kind == clang.cindex.CursorKind.NAMESPACE:
            self.namespace = cursor.lexical_parent.spelling
        else:
            self.namespace = ""

        self.fullname = "{}::{}".format(self.namespace, self.name)

        for c in cursor.get_children():
            if (c.kind == clang.cindex.CursorKind.CXX_METHOD and
                c.access_specifier == clang.cindex.AccessSpecifier.PUBLIC):
                f = Function(c)
                if 'getter' in f.annotations:
                    prop_name = f.name
                    if not prop_name in self.properties:
                        self.properties[prop_name] = Property(c)
                    self.properties[prop_name].getter = f
                elif 'setter' in f.annotations:
                    prop_name = f.name[3].lower() + f.name[4:]
                    if not prop_name in self.properties:
                        self.properties[prop_name] = Property(c)
                    self.properties[prop_name].setter = f
                elif not f.is_static:
                    self.functions.append(f)
            elif (c.kind == clang.cindex.CursorKind.CXX_BASE_SPECIFIER):
                if len(c.displayname.split()) > 1:
                    self.base_names.append(c.displayname.split()[1])
                else:
                    self.base_names.append(c.displayname)

    @property
    def is_abstract(self):
        return sum(1 for f in self.functions if f.is_purevirtual) > 0

def build_classes(cursor, filename):
    result = []
    for c in cursor.get_children():
        if (c.kind == clang.cindex.CursorKind.CLASS_DECL
            and c.location.file.name == filename):
            a_class = Class(c)
            a_class.filename = filename
            result.append(a_class)
        elif c.kind == clang.cindex.CursorKind.NAMESPACE:
            child_classes = build_classes(c, filename)
            result.extend(child_classes)

    return result

def process_file_gen(filename, args, reflected_types):
    index = clang.cindex.Index.create()
    if args.verbose: print "Processing", filename
    translation_unit = index.parse(filename,
                                   ['-x', 'c++', '-std=c++11',
                                    '-D__CODE_GENERATOR__',
                                    '-DDEBUG',
                                    '-DUNIX',
                                    '-Isrc',
                                    '-I../src',
                                    '-Isrc/3rdparty/include',
                                    '-Isrc/3rdparty/include/lua',
                                    '-Itest/include',
                                    '-isystem/usr/local/include',
                                    '-isystem/usr/lib/clang/3.6.0/include',
                                    '-isystem/usr/include'])
    classes = build_classes(translation_unit.cursor, filename)
    return [c for c in classes if c.fullname in reflected_types]

def enum_headers(directory):
    headers = []
    for root, dirnames, filenames in os.walk(directory):
        for filename in fnmatch.filter(filenames, '*.h'):
            headers.append(os.path.join(root, filename))
    return headers

def collect_reflected_types(headers):
    reflected_types = []
    reflect_rgx = re.compile(r'REFLECT_TYPE\((?P<class_name>.*?)\)')
    for header in headers:
        with open(header, "r") as f:
            for line in f:
                match = reflect_rgx.match(line)
                if match and match.group('class_name'):
                    reflected_types.append(match.group('class_name'))
    return reflected_types

def main():
    parser = argparse.ArgumentParser(description="This script generates code " +
                                     "for Boost.Python and CAMP binding")
    parser.add_argument('-d', '--directory', metavar='DIR', dest='inputdir',
                        help="The input directory to recursively " +
                        "scan for headers",
                        default="src")
    parser.add_argument('outputfile', nargs='?',
                        default="generated/generated.cc")
    parser.add_argument('-v', '--verbose', help="Display processed file",
                        action='store_true', default=False)
    args = parser.parse_args()
    if not args.inputdir:
        parser.print_help()
        sys.exit(1)

    headers = enum_headers(args.inputdir)
    reflected_types = collect_reflected_types(headers)
    print "Reflected types:", reflected_types

    pool = Pool(processes=8)
    process_file = functools.partial(process_file_gen, args=args,
                                     reflected_types=reflected_types)
    all_classes = list(itertools.chain(*pool.map(process_file, headers)))

    script_dir = os.path.dirname(os.path.realpath(__file__))
    tpl = Template(filename=os.path.join(script_dir, 'bind_python.mako'))
    rendered = tpl.render(
                 classes=all_classes,
                 module_name='mcomm')

    output_dir = os.path.dirname(args.outputfile)

    if not os.path.isdir(output_dir): os.mkdir(output_dir)

    with open(args.outputfile, 'w') as f:
        f.write(rendered)

if __name__ == '__main__': main()


