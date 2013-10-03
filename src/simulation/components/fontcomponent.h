#pragma once

#include <memory>

#include <SFML/Graphics/Font.hpp>

#include "simulation/component.h"

namespace mcomm
{

class FontComponent : public Component
{
public:
    FontComponent();
    std::string toString() const;
    void init(const pugi::xml_node& xml);

    std::shared_ptr<sf::Font> font() const;
    int size() const;
    void setSize(int value);

private:
    std::shared_ptr<sf::Font> m_font;
    int m_size;
};

}
