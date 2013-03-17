#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "SFML/System/Vector2.hpp"

namespace mcomm
{

class Entity;

class CollisionGrid
{
    typedef std::multimap<std::pair<int, int>, std::shared_ptr<Entity>> map_type;
    typedef map_type::const_iterator map_it;
public:
    static CollisionGrid& instance()
    {
        static CollisionGrid inst;
        return inst;
    }

    void registerEntity(std::shared_ptr<Entity>&);
    std::pair<int, int> gridPositionOf(std::shared_ptr<Entity>&) const;
    void clearAll();
    std::pair<map_it, map_it> neighbors(std::shared_ptr<Entity>&) const;

private:
    CollisionGrid() : m_grid_size(128) {}

private:
    map_type m_map;
    int m_grid_size;
};

}
