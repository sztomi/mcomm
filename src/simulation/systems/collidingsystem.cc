#include "collidingsystem.h"
#include "../collisiongrid.h"

namespace mcomm
{

std::string CollidingSystem::toString() const
{
    return "CollidingSystem";
}

void CollidingSystem::update(float dt)
{
    CollisionGrid::instance().registerEntity(m_parent);
}

}
