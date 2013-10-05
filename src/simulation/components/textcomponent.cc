#include "jsonxx.h"
#include <SFML/Graphics/Text.hpp>

#include "drawablecomponent.h"
#include "textcomponent.h"

using namespace jsonxx;

namespace mcomm
{

TextComponent::TextComponent()
{
    m_text = std::make_shared<sf::Text>();
}

std::string TextComponent::name() const
{
    return "TextComponent";
}

void TextComponent::loadJson(const Object& o)
{
    auto font = o.get<Object>("font");

    setFontFileName(font.get<String>("filename"));

    m_text->setFont(m_font);
    m_text->setCharacterSize(font.get<Number>("size"));
    m_text->setString(o.get<String>("text"));

    //m_parent->COMPONENT(Drawable)->setDrawable(m_text);
}

Object TextComponent::toJson() const
{
    Object result;

    Object font;
    font << "filename" << m_fontFilename;
    font << "size" << m_text->getCharacterSize();
    result << "font" << font;

    result << "text" << text();

    return result;
}

std::string TextComponent::text() const
{
    return m_text->getString();
}

void TextComponent::setText(const std::string& value)
{
    m_text->setString(value);
}

unsigned int TextComponent::size() const
{
    return m_text->getCharacterSize();
}

void TextComponent::setSize(unsigned int value)
{
    m_text->setCharacterSize(value);
}

std::string TextComponent::fontFileName() const
{
    return m_fontFilename;
}

void TextComponent::setFontFileName(const std::string& value)
{
    m_fontFilename = value;
    m_font.loadFromFile(value);
    m_text->setFont(m_font);
}

}
