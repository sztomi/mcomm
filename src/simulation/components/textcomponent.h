#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace sf
{
    class Text;
}

namespace mcomm
{

class TextComponent : public Component
{
public:
    TextComponent();

    GET std::string text() const;
    SET void setText(const std::string& value);

    GET unsigned int size() const;
    SET void setSize(unsigned int value);

    GET std::string fontFileName() const;
    SET void setFontFileName(const std::string& value);

private:
    std::shared_ptr<sf::Text> m_text;
    sf::Font m_font;
    std::string m_fontFilename;
};

}
REFLECT_TYPE(mcomm::TextComponent)
