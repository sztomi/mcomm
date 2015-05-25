#include <boost/python.hpp>
#include "../src/simulation/components/transformcomponent.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(mcomm)
{
    class_<TransformComponent, bases<mcomm::Component,sf::Transformable>>("TransformComponent")
		.property("position_x", &TransformComponent::positionX, &TransformComponent::setPositionX)
		.property("position_y", &TransformComponent::positionY, &TransformComponent::setPositionY)
		.property("scale_x", &TransformComponent::scaleX, &TransformComponent::setScaleX)
		.property("origin_y", &TransformComponent::originY, &TransformComponent::setOriginY)
		.property("scale_y", &TransformComponent::scaleY, &TransformComponent::setScaleY)
		.property("origin_x", &TransformComponent::originX, &TransformComponent::setOriginX)
    ;
}

void bind_camp_reflection()
{
    camp::Class::declare<TransformComponent>("TransformComponent")
		.property("position_x", &TransformComponent::positionX, &TransformComponent::setPositionX)
		.property("position_y", &TransformComponent::positionY, &TransformComponent::setPositionY)
		.property("scale_x", &TransformComponent::scaleX, &TransformComponent::setScaleX)
		.property("origin_y", &TransformComponent::originY, &TransformComponent::setOriginY)
		.property("scale_y", &TransformComponent::scaleY, &TransformComponent::setScaleY)
		.property("origin_x", &TransformComponent::originX, &TransformComponent::setOriginX)
    ;
}
