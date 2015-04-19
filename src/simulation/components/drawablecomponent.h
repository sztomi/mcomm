#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>

#include "simulation/component.h"


namespace mcomm
{

class DrawableComponent : public Component
{
	DECLARE_COMPONENT(DrawableComponent)

public:
    void setDrawable(const std::shared_ptr<sf::Drawable> &value);
    std::shared_ptr<sf::Drawable> drawable() const;

private:
    std::shared_ptr<sf::Drawable> m_drawable;
    std::string m_kind;
};

}
