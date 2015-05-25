#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class TransformComponent : public Component, public sf::Transformable
{
public:
    TransformComponent();

    GET float scaleX() const { return getScale().x; }
    SET void setScaleX(float value) { setScale(value, scaleY()); }
    GET float scaleY() const { return getScale().y; }
    SET void setScaleY(float value) { setScale(scaleX(), value); }

    GET float originX() const { return getOrigin().x; }
    SET void setOriginX(float value) { setOrigin(value, originY()); }
    GET float originY() const { return getOrigin().y; }
    SET void setOriginY(float value) { setOrigin(originX(), value); }

    GET float positionX() const { return getPosition().x; }
    SET void setPositionX(float value) { setPosition(value, positionY()); }
    GET float positionY() const { return getPosition().y; }
    SET void setPositionY(float value) { setPosition(positionX(), value); }
};

}
REFLECT_TYPE(mcomm::TransformComponent)
