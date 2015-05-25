#include "precompiled.h"
#include "drawablecomponent.h"

using namespace jsonxx;

namespace mcomm
{

DrawableComponent::DrawableComponent()
    : m_drawable(), m_kind("unset")
{
}

std::shared_ptr<sf::Drawable> DrawableComponent::drawable() const
{
    return m_drawable;
}

void DrawableComponent::setDrawable(const std::shared_ptr<sf::Drawable> &value)
{
    m_drawable = value;
}

}
