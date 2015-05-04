#include "precompiled.h"

#include "drawablecomponent.h"
#include "textcomponent.h"


using namespace lualite;

namespace mcomm
{

BIND_COMPONENT(TextComponent)
	.property("text",
			  &TextComponent::text,
			  &TextComponent::setText)
	.property("size",
			  &TextComponent::size,
			  &TextComponent::setSize)
	.property("fontFileName",
			  &TextComponent::fontFileName,
			  &TextComponent::setFontFileName)
BIND_END()

TextComponent::TextComponent()
{
    m_text = std::make_shared<sf::Text>();
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
