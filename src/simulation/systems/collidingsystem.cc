#include "collidingsystem.h"
#include "../collisiongrid.h"

namespace mcomm
{

BIND_SYSTEM(CollidingSystem)
BIND_END()

CollidingSystem::CollidingSystem() {}

void CollidingSystem::update(float dt)
{
    CollisionGrid::instance().registerEntity(m_parent);
}

}
