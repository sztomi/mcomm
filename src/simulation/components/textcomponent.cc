#include "jsonxx.h"
#include <SFML/Graphics/Text.hpp>

#include "drawablecomponent.h"
#include "textcomponent.h"

#include "reflection/metaclassmanager.h"
#include "scripting/scriptmanager.h"

#include "lua.hpp"
#include "lualite.hpp"

using namespace jsonxx;
using namespace lualite;

namespace mcomm
{

REGISTER_COMPONENT(TextComponent);

TextComponent::TextComponent()
{
    m_text = std::make_shared<sf::Text>();
}

//void TextComponent::loadJson(const Object& o)
//{
    //auto font = o.get<Object>("font");

    //setFontFileName(font.get<String>("filename"));

    //m_text->setFont(m_font);
    //m_text->setCharacterSize(font.get<Number>("size"));
    //m_text->setString(o.get<String>("text"));

    ////m_parent->COMPONENT(Drawable)->setDrawable(m_text);
//}

//Object TextComponent::toJson() const
//{
    //Object result;

    //Object font;
    //font << "filename" << m_fontFilename;
    //font << "size" << m_text->getCharacterSize();
    //result << "font" << font;

    //result << "text" << text();

    //return result;
//}

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
    auto c = class_<TextComponent>(ClassName)
                .def("name", &TextComponent::name)
                .property("text", &TextComponent::text, &TextComponent::setText)
                .property("size", &TextComponent::size, &TextComponent::setSize)
                .property("fontFileName", &TextComponent::fontFileName, &TextComponent::setFontFileName);

    auto m = mcomm::MetaClass::create(ClassName, c);

    MetaClassManager::instance().registerClass(m);
    ScriptManager::instance().registerClass(c);
}

}
