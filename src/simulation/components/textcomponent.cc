#include "jsonxx.h"
#include <SFML/Graphics/Text.hpp>

#include "drawablecomponent.h"
#include "textcomponent.h"


using namespace lualite;

namespace mcomm
{

REGISTER_COMPONENT(TextComponent);

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

void TextComponent::bind()
{
    static bool bound = false;
    if (bound) return; 

    auto c = class_<TextComponent>(ClassName)
                .constructor("new")
                .def("name", &TextComponent::name)
                .property("text", &TextComponent::text, &TextComponent::setText)
                .property("size", &TextComponent::size, &TextComponent::setSize)
                .property("fontFileName", &TextComponent::fontFileName, &TextComponent::setFontFileName);

    auto m = mcomm::MetaClass::create(ClassName, c);

    MetaClassManager::instance().registerClass(m);
    ScriptManager::instance().registerClass(c);

    bound = true;
}

}
