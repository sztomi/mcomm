#include "pugixml.hpp"
#include "fontcomponent.h"

namespace mcomm
{

FontComponent::FontComponent()
    : m_size(20)
{
    m_font = std::make_shared<sf::Font>();
}

std::string FontComponent::toString() const
{
    return "FontComponent";
}

void FontComponent::init(const pugi::xml_node& xml)
{
    m_font->loadFromFile(xml.child("FileName").text().as_string());
    m_size = xml.child("Size").text().as_int();
}

std::shared_ptr<sf::Font> FontComponent::font() const
{
    return m_font;
}

int FontComponent::size() const
{
    return m_size;
}


}
