#include "pugixml.hpp"
#include "textcomponent.h"

namespace mcomm
{

std::string TextComponent::toString() const
{
    return "TextComponent";
}

void TextComponent::init(const pugi::xml_node& xml)
{
    m_text = xml.text().as_string();
}

std::string TextComponent::text() const
{
    return m_text;
}

void TextComponent::setText(const std::string& value)
{
    m_text = value;
}

}
