#pragma once

#include <SFML/System/Vector2.hpp>

#include "../system.h"

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
