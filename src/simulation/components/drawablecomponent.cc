#include <boost/format.hpp>

#include "jsonxx.h"

#include "simulation/components/drawablecomponent.h"
#include "simulation/factories.h"

extern "C" 
{
#include "lua5.1/lua.h"
}

#include <luabind/luabind.hpp>

using namespace jsonxx;
using namespace luabind;

namespace mcomm
{

DrawableComponent::DrawableComponent()
    : m_drawable(), m_kind("unset")
{
}

std::string DrawableComponent::name() const
{
    return boost::str(boost::format("DrawableComponent [%1%]") % m_kind);
}

void DrawableComponent::loadJson(const Object& o)
{
} 

Object DrawableComponent::toJson() const
{
    return Object();
}

std::shared_ptr<sf::Drawable> DrawableComponent::drawable() const
{
    return m_drawable;
}

void DrawableComponent::setDrawable(const std::shared_ptr<sf::Drawable> &value)
{
    m_drawable = value;
}

void DrawableComponent::luabind(lua_State* L)
{
    open(L);
    module(L)
    [
        class_<DrawableComponent>("DrawableComponent")
            .def("name", &DrawableComponent::name)
    ];
}

}
