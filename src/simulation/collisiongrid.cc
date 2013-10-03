#include <utility>
#include "collisiongrid.h"
#include "components/boundingboxcomponent.h"
#include "components/transformcomponent.h"

namespace mcomm
{

void CollisionGrid::registerEntity(std::shared_ptr<Entity> &entity)
{
    m_map.insert(std::make_pair(gridPositionOf(entity), entity));
}

std::pair<int, int> CollisionGrid::gridPositionOf(std::shared_ptr<Entity> &entity) const
{
    auto pos = entity->COMPONENT(Transform)->getPosition();
    int x = pos.x > 0 ? m_grid_size / pos.x : 0;
    int y = pos.y > 0 ? m_grid_size / pos.y : 0;
    return std::make_pair(x, y);
}

void CollisionGrid::clearAll()
{
    m_map.clear();
}

std::pair<CollisionGrid::map_it, CollisionGrid::map_it> CollisionGrid::neighbors(std::shared_ptr<Entity> &entity) const
{
    auto coords = gridPositionOf(entity);
    return m_map.equal_range(coords);
}


}
