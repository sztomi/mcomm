#include <lualite.hpp>

#include "transformcomponent.h"

using namespace lualite;

namespace mcomm
{

REGISTER_COMPONENT(TransformComponent);

BIND_BEGIN(TransformComponent)
	.property("scale_x",
			  &TransformComponent::scaleX,
			  &TransformComponent::setScaleX)
	.property("scale_y",
			  &TransformComponent::scaleY,
			  &TransformComponent::setScaleY)
	.property("origin_x",
			  &TransformComponent::originX,
			  &TransformComponent::setOriginX)
	.property("origin_y",
			  &TransformComponent::originY,
			  &TransformComponent::setOriginY)
	.property("position_x",
			  &TransformComponent::positionX,
			  &TransformComponent::setPositionX)
	.property("position_y",
			  &TransformComponent::positionY,
			  &TransformComponent::setPositionY)
BIND_END()

TransformComponent::TransformComponent() : sf::Transformable() {}


}
