#include "precompiled.h"

#include "rendersystem.h"
#include "simulation/components/drawablecomponent.h"
#include "simulation/components/transformcomponent.h"
#include "game.h"

namespace mcomm
{

BIND_SYSTEM(RenderSystem)
BIND_END()

RenderSystem::RenderSystem() {}

void RenderSystem::update(float dt)
{
	auto drawable = m_parent->COMPONENT(Drawable)->drawable();
	auto transform = m_parent->COMPONENT(Transform)->getTransform();
	Game::instance().renderWindow()->draw(*drawable, transform);
}

}
