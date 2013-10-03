#pragma once

#include <SFML/System/Vector2.hpp>

#include "../system.h"

namespace mcomm
{

class VelocitySystem : public System
{
public:
	std::string toString() const;
	sf::Vector2f velocity() const;

	void update(float dt);	
	void setVelocity(const sf::Vector2f& value);
	
private:
	sf::Vector2f m_velocity;
};

}