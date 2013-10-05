#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

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

    std::string name() const;
    void loadJson(const jsonxx::Object& o);
    jsonxx::Object toJson() const;
    
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
