#include "precompiled.h"
#include "drawablecomponent.h"

using namespace jsonxx;
using namespace lualite;

namespace mcomm
{

BIND_COMPONENT(DrawableComponent)
BIND_END()


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
