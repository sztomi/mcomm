#include "speedcomponent.h"
#include "jsonxx.h"

#include "lua.hpp"
#include "lualite.hpp"

using namespace jsonxx;
using namespace lualite;

namespace mcomm
{

SpeedComponent::SpeedComponent()
	: m_x(0), m_y(0)
{

}

std::string SpeedComponent::name() const
{
    return "SpeedComponent";
}

void SpeedComponent::loadJson(const Object& o)
{
    m_x = static_cast<float>(o.get<Number>("x"));
    m_y = static_cast<float>(o.get<Number>("y"));
}

Object SpeedComponent::toJson() const
{
    Object result;
    result << "x" << m_x;
    result << "y" << m_y;

    return result;
}

float SpeedComponent::x() const
{
    return m_x;
}

float SpeedComponent::y() const
{
    return m_y;
}

void SpeedComponent::setX(float value)
{
    m_x = value;
}

void SpeedComponent::setY(float value)
{
    m_y = value;
}

void SpeedComponent::luabind(lua_State* L)
{
    module(L,
        class_<SpeedComponent>("SpeedComponent")
            .constructor("new")
            .def("name", &SpeedComponent::name)
            .property("x", &SpeedComponent::x, &SpeedComponent::setX)
            .property("y", &SpeedComponent::y, &SpeedComponent::setY)
    );
}

}
