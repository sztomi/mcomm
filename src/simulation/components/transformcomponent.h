#pragma once

#include "SFML/Graphics/Transformable.hpp"

#include "../component.h"

namespace mcomm
{

class TransformComponent : public Component, public sf::Transformable
{
    DECLARE_COMPONENT(TransformComponent)

public:
    float scaleX() const { return getScale().x; }
    void setScaleX(float value) { setScale(value, scaleY()); }
    float scaleY() const { return getScale().x; }
    void setScaleY(float value) { setScale(scaleX(), value); }

    float originX() const { return getOrigin().x; }
    void setOriginX(float value) { setOrigin(value, originY()); }
    float originY() const { return getOrigin().x; }
    void setOriginY(float value) { setOrigin(originX(), value); }

    float positionX() const { return getPosition().x; }
    void setPositionX(float value) { setPosition(value, positionY()); }
    float positionY() const { return getPosition().x; }
    void setPositionY(float value) { setPosition(positionX(), value); }

};

}
