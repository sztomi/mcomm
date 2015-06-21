#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class DrawableComponent : public Component
{
    RTTI()
public:
    DrawableComponent();
    HIDDEN void setDrawable(const std::shared_ptr<sf::Drawable> &value);
    HIDDEN std::shared_ptr<sf::Drawable> drawable() const;

private:
    std::shared_ptr<sf::Drawable> m_drawable;
    std::string m_kind;
};

}
REFLECT_TYPE(mcomm::DrawableComponent)
