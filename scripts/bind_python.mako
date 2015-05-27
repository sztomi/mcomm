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

BOOST_PYTHON_MODULE(${module_name})
{
% for c in classes:
    % if len(c.functions) == 0 and len(c.properties) == 0:
<% continue %>
    % endif
    // ${c.filename}
	% if len(c.base_names) > 0:
    class_<${c.fullname}, bases<${','.join(c.base_names)}>>("${c.name}")
	% else:
    class_<${c.fullname}>("${c.name}")
	% endif
    % for f in c.functions:
        % if not "hidden" in f.annotations:
        % if not f.is_purevirtual:
        .def("${snake_case(f.name)}", &${c.name}::${f.name})
        % else:
        .def("${snake_case(f.name)}", pure_virtual(&${c.name}::${f.name}))
        % endif
        % endif
    % endfor
	% for p in c.properties:
		% if c.properties[p].setter:
        .add_property("${snake_case(c.properties[p].name)}", &${c.name}::${c.properties[p].getter.name}, &${c.name}::${c.properties[p].setter.name})
		% else:
        .add_property("${snake_case(c.properties[p].name)}", &${c.name}::${c.properties[p].getter.name})
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
