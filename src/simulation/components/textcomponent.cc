#include <SFML/Graphics/Text.hpp>
#include "pugixml.hpp"
#include "drawablecomponent.h"
#include "textcomponent.h"

namespace mcomm
{

TextComponent::TextComponent()
{
    m_text = std::make_shared<sf::Text>();
}

std::string TextComponent::toString() const
{
    return "TextComponent";
}

void TextComponent::init(const pugi::xml_node& xml)
{
    auto font_node = xml.child("Font");
    m_font.loadFromFile(font_node.child("FileName").text().as_string());
    m_text->setFont(m_font);
    m_text->setCharacterSize(font_node.child("Size").text().as_int());
    m_text->setString(xml.child("Value").text().as_string());

    m_parent->COMPONENT(Drawable)->setDrawable(m_text);
}

std::string TextComponent::text() const
{
    return m_text->getString();
}

void TextComponent::setText(const std::string& value)
{
    m_text->setString(value);
}

}
