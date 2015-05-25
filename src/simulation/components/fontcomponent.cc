#include "precompiled.h"
#include "fontcomponent.h"

namespace mcomm
{

FontComponent::FontComponent()
	: m_size(0), m_font(), m_filename("unset") {}

std::string FontComponent::fileName() const { return m_filename; }
void FontComponent::setFileName(std::string const& value) { m_filename = value; }

int FontComponent::size() const { return m_size; }
void FontComponent::setSize(int value) { m_size = value; }

std::shared_ptr<sf::Font> FontComponent::font() const { return m_font; }

}
