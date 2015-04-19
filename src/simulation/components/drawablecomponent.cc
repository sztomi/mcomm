#include <boost/format.hpp>

#include "jsonxx.h"

#include "simulation/components/drawablecomponent.h"
#include "simulation/factories.h"

#include <lualite.hpp>

using namespace jsonxx;
using namespace lualite;

namespace mcomm
{

REGISTER_COMPONENT(DrawableComponent)

BIND_BEGIN(DrawableComponent)
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
