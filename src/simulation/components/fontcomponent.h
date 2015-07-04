#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class FontComponent : public Component
{
    RTTI()
public:
    FontComponent();

    std::shared_ptr<sf::Font> font() const;

    GET int size() const noexcept;
    SET void setSize(int value) noexcept;

    GET std::string fileName() const noexcept;
    SET void setFileName(std::string const& value) noexcept;

private:
    std::shared_ptr<sf::Font> m_font;
    std::string m_filename;
    int m_size;
};

}
REFLECT_TYPE(mcomm::FontComponent)
