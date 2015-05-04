#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class FontComponent : public Component
{
	DECLARE_COMPONENT(FontComponent)

public:
    std::shared_ptr<sf::Font> font() const;

    int size() const;
    void setSize(int value);

	std::string fileName() const;
	void setFileName(std::string const& value);

private:
    std::shared_ptr<sf::Font> m_font;
	std::string m_filename;
    int m_size;
};

}
