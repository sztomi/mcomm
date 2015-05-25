#!/usr/bin/python2
# vim: set fileencoding=utf-8
import clang.cindex
import asciitree
import sys

def node_children(node):
    return [c for c in node.get_children() if c.location.file.name == sys.argv[1]]

def print_node(node):
    text = node.spelling + "|" + node.displayname
    kind = str(node.kind)[str(node.kind).index('.')+1:]
    return '{} {}'.format(kind, text)

if len(sys.argv) != 2:
    print("Usage: dump_ast.py [header file name]")
    sys.exit()

#clang.cindex.Config.set_library_file('/usr/local/lib/libclang.so')
filename = sys.argv[1]
index = clang.cindex.Index.create()
translation_unit = index.parse(filename,
                               ['-x', 'c++', '-std=c++11',
                                '-D__CODE_GENERATOR__',
                                '-DDEBUG',
                                '-DUNIX',
                                '-I../src',
                                '-Isrc',
                                '-Isrc/3rdparty/include',
                                '-Isrc/3rdparty/include/lua',
                                '-Itest/include',
                                '-isystem/usr/local/include',
                                '-isystem/usr/bin/../lib/clang/3.6.0/include',
                                '-isystem/usr/include'])

print(asciitree.draw_tree(translation_unit.cursor, node_children, print_node))

