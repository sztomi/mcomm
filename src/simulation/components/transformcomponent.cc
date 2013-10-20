#include <lualite.hpp>

#include "transformcomponent.h"

using namespace lualite;

namespace mcomm 
{

REGISTER_COMPONENT(TransformComponent);

TransformComponent::TransformComponent() : sf::Transformable() {}

void TransformComponent::bind()
{
    static bool bound = false;
    if (bound) return; 

    auto c = class_<TransformComponent>(ClassName)
                .constructor()
                .property("scale_x", &TransformComponent::scaleX, &TransformComponent::setScaleX)
                .property("scale_y", &TransformComponent::scaleY, &TransformComponent::setScaleY)
                .property("origin_x", &TransformComponent::originX, &TransformComponent::setOriginX)
                .property("origin_y", &TransformComponent::originY, &TransformComponent::setOriginY)
                .property("position_x", &TransformComponent::positionX, &TransformComponent::setPositionX)
                .property("position_y", &TransformComponent::positionY, &TransformComponent::setPositionY);

    auto m = mcomm::MetaClass::create(ClassName, c);

    MetaClassManager::instance().registerClass(m);
    ScriptManager::instance().registerClass(c);

    bound = true;
}

}
