#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class VelocitySystem : public System
{
    RTTI()
public:
    VelocitySystem();
    void update(float dt) override;

    HIDDEN sf::Vector2f velocity() const;
    HIDDEN void setVelocity(const sf::Vector2f& value);

    GET float x() const { return m_velocity.x; }
    SET void setX(float value) { m_velocity.x = value; }
    GET float y() const { return m_velocity.y; }
    SET void setY(float value) { m_velocity.y = value; }

private:
    sf::Vector2f m_velocity;
};

}
REFLECT_TYPE(mcomm::VelocitySystem)
