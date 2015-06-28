#pragma once

#include "precompiled.h"
#include "macros.h"

namespace mcomm
{

class Entity;

class World
{
    RTTI()
public:
    void update(float dt);
    void addEntity(Entity* entity);
    void load(const std::string& fileName);
    void save(std::string const& fileName);

    /*!
     * \brief Removes all entities from the world.
     */
    void clear();

    static void bindClass();

private:
    std::vector<Entity*> m_entities;

    friend class Editor;
};

}

CAMP_TYPE(mcomm::World)
