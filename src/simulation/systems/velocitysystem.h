#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class VelocitySystem : public System
{
	DECLARE_COMPONENT(VelocitySystem)
public:
	sf::Vector2f velocity() const;

	void update(float dt) override;
	void setVelocity(const sf::Vector2f& value);

private:
	sf::Vector2f m_velocity;
};

}
