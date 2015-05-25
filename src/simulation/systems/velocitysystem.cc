#include "precompiled.h"

#include "velocitysystem.h"
#include "spriteanimationsystem.h"
#include "simulation/components/transformcomponent.h"

namespace mcomm
{

VelocitySystem::VelocitySystem() {}

void VelocitySystem::update(float dt)
{
	auto transform = m_parent->COMPONENT(Transform);
	auto s = m_velocity * dt;
	const float epsilon = 0.01f;

	if (fabs(m_velocity.x) > epsilon ||
		fabs(m_velocity.y) > epsilon)
	{
		transform->move(s.x, s.y);
		auto anim = m_parent->SYSTEM(SpriteAnimation);
		if (anim && !anim->isRunning()) anim->startFrom(0);
	}
	else
	{
		auto anim = m_parent->SYSTEM(SpriteAnimation);
		if (anim) anim->stopAt(1);
	}
}

sf::Vector2f VelocitySystem::velocity() const
{
	return m_velocity;
}

void VelocitySystem::setVelocity(const sf::Vector2f& value)
{
	m_velocity = value;
}

}
