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

    std::string toString() const;
    void init(const pugi::xml_node& xml);
    
    std::string text() const;
    void setText(const std::string& value);

private:
    std::shared_ptr<sf::Text> m_text;
    sf::Font m_font;
};

}
