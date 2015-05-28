<%
import os
import re

def snake_case(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()
%>
#include "precompiled.h"
#include "bindings/external_types.h"
% for f in set([c.filename for c in classes]):
#include "${os.path.relpath(f, "src")}"
% endfor

using namespace boost::python;
using namespace mcomm;
<%
abstract_classes = [c for c in classes if c.is_abstract]
%>
% for c in abstract_classes:
// Wrapper for abstract class ${c.fullname}
struct ${c.name}Wrap : ${c.fullname}, boost::python::wrapper<${c.fullname}>
{
    ${c.name}Wrap() {}
    ${c.name}Wrap(${c.fullname} const& rhs)
        : ${c.fullname}(rhs)
    {}

% for f in c.functions:
<% arglst = ', '.join([str(a) for a in f.arguments]) %>\
    ${f.return_type_str} ${f.name}(${arglst})
    {
    % if f.return_type_str != 'void':
        return get_override("${f.name}")(${' '.join([a.name for a in f.arguments])});
    % else:
        get_override("${f.name}")(${' '.join([a.name for a in f.arguments])});
    % endif
    }

% endfor
};
% endfor

BOOST_PYTHON_MODULE(${module_name})
{
% for c in classes:
    % if len(c.functions) == 0 and len(c.properties) == 0:
<% continue %>
    % endif
    // ${c.filename}
<% class_name = c.name if not c.is_abstract else c.name+"Wrap" %>\
    % if len(c.base_names) > 0:
    class_<${class_name}, bases<${','.join(c.base_names)}>>("${c.name}")
    % else:
    class_<${class_name}>("${c.name}")
    % endif
    % for f in c.functions:
        % if not "hidden" in f.annotations:
        % if not f.is_purevirtual:
        .def("${snake_case(f.name)}", &${class_name}::${f.name})
        % else:
        .def("${snake_case(f.name)}", pure_virtual(&${class_name}::${f.name}))
        % endif
        % endif
    % endfor
	% for p in c.properties:
		% if c.properties[p].setter:
        .add_property("${snake_case(c.properties[p].name)}", &${class_name}::${c.properties[p].getter.name}, &${c.name}::${c.properties[p].setter.name})
		% else:
        .add_property("${snake_case(c.properties[p].name)}", &${class_name}::${c.properties[p].getter.name})
		% endif
	% endfor
    ;

% endfor
}

void init_camp_bindings()
{
% for c in classes:
    % if len(c.functions) == 0 and len(c.properties) == 0:
<% continue %>
    % endif
    // ${c.filename}
    % if c.is_abstract:
    camp::Class::declare<${c.fullname}>();
    % else:
    camp::Class::declare<${c.fullname}>()
        .constructor0()
    % for f in c.functions:
        % if not "hidden" in f.annotations:
        .function("${f.name}", &${c.name}::${f.name})
        % endif
    % endfor
	% for p in c.properties:
		% if c.properties[p].setter:
        .property("${c.properties[p].name}", &${c.name}::${c.properties[p].getter.name}, &${c.name}::${c.properties[p].setter.name})
		% else:
        .property("${c.properties[p].name}", &${c.name}::${c.properties[p].getter.name})
		% endif
	% endfor
    ;
    % endif

% endfor
}

namespace mcomm
{

void initGeneratedBindings()
{
    Py_Initialize();
    PyInit_${module_name}();
    init_camp_bindings();
}

}
