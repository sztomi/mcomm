#include <boost/format.hpp>

#include "pugixml.hpp"
#include "simulation/components/drawablecomponent.h"
#include "simulation/factories.h"

namespace mcomm
{

DrawableComponent::DrawableComponent()
    : m_drawable(), m_kind("unset")
{
}

std::string DrawableComponent::toString() const
{
    return boost::str(boost::format("DrawableComponent [%1%]") % m_kind);
}

void DrawableComponent::init(const pugi::xml_node &xml)
{
    m_parent->attachComponent(xml.first_child().name())->init(xml.first_child());
} 

std::shared_ptr<sf::Drawable> DrawableComponent::drawable() const
{
    return m_drawable;
}

void DrawableComponent::setDrawable(const std::shared_ptr<sf::Drawable> &value)
{
    m_drawable = value;
}

}
