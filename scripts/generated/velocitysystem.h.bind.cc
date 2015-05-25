#include <boost/python.hpp>
#include "../src/simulation/systems/velocitysystem.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(mcomm)
{
    class_<VelocitySystem, bases<mcomm::System>>("VelocitySystem")
        .def("update", &VelocitySystem::update)
		.property("y", &VelocitySystem::y, &VelocitySystem::setY)
		.property("x", &VelocitySystem::x, &VelocitySystem::setX)
    ;
}

void init_bindings()
{
    Py_Initialize();
    initmcomm();
}
