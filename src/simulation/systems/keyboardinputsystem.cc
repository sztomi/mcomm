#include <SFML/Window/Keyboard.hpp>

#include "simulation/components/speedcomponent.h"
#include "simulation/components/transformcomponent.h"
#include "keyboardinputsystem.h"
#include "velocitysystem.h"

namespace mcomm
{

std::string KeyboardInputSystem::toString() const
{
	return "KeyboardInputSystem";
}

void KeyboardInputSystem::update(float dt)
{
	using namespace sf;
	float v_y = 0, v_x = 0;

	auto speed = m_parent->COMPONENT(Speed);
	auto transform = m_parent->COMPONENT(Transform);

	float speed_x = speed->x();
	float speed_y = speed->y();

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		v_x = -speed_x;

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			transform->setRotation(180 + 45);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			transform->setRotation(180 - 45);
		}
		else
		{
			transform->setRotation(180);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		v_x = speed_x;

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			transform->setRotation(-45);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			transform->setRotation(45);
		}
		else
		{
			transform->setRotation(0);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		v_y = -speed_y;

		if (!Keyboard::isKeyPressed(Keyboard::Right) &&
			!Keyboard::isKeyPressed(Keyboard::Left))
		{
			transform->setRotation(-90);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		v_y = speed_y;

		if (!Keyboard::isKeyPressed(Keyboard::Right) &&
			!Keyboard::isKeyPressed(Keyboard::Left))
		{
			transform->setRotation(90);
		}
	}

	// 

	// if (Keyboard::isKeyPressed(Keyboard::Up))
	// {
	// 	transform->rotate(90);

	// 	if (Keyboard::isKeyPressed(Keyboard::Right))
	// 		transform->rotate(-45);
	// }

	auto velocity = m_parent->SYSTEM(Velocity);

	if (velocity)
	{
		auto current_v = velocity->velocity();
		velocity->setVelocity(Vector2f(v_x, v_y));
	}
}

}
