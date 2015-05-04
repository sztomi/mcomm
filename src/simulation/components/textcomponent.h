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
    DECLARE_COMPONENT(TextComponent)

public:
    std::string text() const;
    void setText(const std::string& value);

    unsigned int size() const;
    void setSize(unsigned int value);

    std::string fontFileName() const;
    void setFontFileName(const std::string& value);

private:
    std::shared_ptr<sf::Text> m_text;
    sf::Font m_font;
    std::string m_fontFilename;
};

}
