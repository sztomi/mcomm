#include <SFML/Graphics/RenderWindow.hpp>

#include "renderablesystem.h"
#include "simulation/components/spritecomponent.h"
#include "simulation/components/transformcomponent.h"
#include "game.h"

namespace mcomm
{

std::string RenderableSystem::toString() const
{
	return "RenderableSystem";
}

void RenderableSystem::update(float dt) 
{
	auto sprite = m_parent->COMPONENT(Sprite)->sprite();	
	auto transform = m_parent->COMPONENT(Transform)->getTransform();
	Game::instance().renderWindow()->draw(sprite, transform);
}

}