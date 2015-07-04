#include "precompiled.h"
#include "fontcomponent.h"

namespace mcomm
{

FontComponent::FontComponent()
	: m_size(0), m_font(), m_filename("unset") {}

std::string FontComponent::fileName() const noexcept
{
    return m_filename;
}

void FontComponent::setFileName(std::string const& value) noexcept
{
    m_filename = value;
}

int FontComponent::size() const noexcept { return m_size; }
void FontComponent::setSize(int value) noexcept { m_size = value; }

std::shared_ptr<sf::Font> FontComponent::font() const { return m_font; }

}
