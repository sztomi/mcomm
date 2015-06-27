#pragma once

#include "precompiled.h"
#include "macros.h"
#include <memory>

namespace mcomm
{

class Component;
class System;

// World owns all entities. This might change in the future
typedef Entity* EntityPtr;

class Entity
{
    RTTI()
public:
    Entity();
    Entity(int aId, const std::string& aName);
    ~Entity();

    Component* attachComponent(const std::string& type);
    System* attachSystem(const std::string& type);

    int id() const;
    std::string toString() const;
    std::string name() const;

    void update(float dt);

    /*!
     * \brief Revives the object after deserialization.
     */
    void revive();

    template<typename T>
    HIDDEN T* component(const std::string& typeStr)
    {
        if (m_components.count(typeStr) == 0)
        {
            LOG(ERROR) << typeStr << " not found in entity.";
            return nullptr;
        }
        else
        {
            return static_cast<T*>(m_components[typeStr]);
        }
    }

    template<typename T>
    HIDDEN T* system(const std::string& type)
    {
        if (m_systems.count(type) == 0)
        {
            LOG(ERROR) << type << " not found in entity.";
            return nullptr;
        }
        else
        {
            return static_cast<T*>(m_systems[type]);
        }
    }

    static void bindClass();

private:
    int m_id;
    std::string m_name;
    std::map<std::string, Component*> m_components;
    std::map<std::string, System*> m_systems;

    std::vector<Component*> m_all_components;
    std::vector<System*> m_all_systems;
};

}

CAMP_TYPE(mcomm::Entity)
