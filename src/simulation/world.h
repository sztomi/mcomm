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

    static void bindClass();

private:
    std::vector<Entity*> m_entities;
};

}

CAMP_TYPE(mcomm::World)
