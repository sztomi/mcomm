#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class FontComponent : public Component
{
public:
    FontComponent();

    std::shared_ptr<sf::Font> font() const;

    GET int size() const;
    SET void setSize(int value);

    GET std::string fileName() const;
    SET void setFileName(std::string const& value);

private:
    std::shared_ptr<sf::Font> m_font;
    std::string m_filename;
    int m_size;
};

}
REFLECT_TYPE(mcomm::FontComponent)
