#pragma once

#include "precompiled.h"

namespace jsonxx { class Object; }

namespace mcomm
{

class Component;
class System;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity(int aId, const std::string& aName);

    std::shared_ptr<Component> attachComponent(const std::string& type);
    std::shared_ptr<System> attachSystem(const std::string& type);

    int id() const;
    std::string toString() const;
    std::string name() const;

    void update(float dt);

    template<typename T>
    std::shared_ptr<T> component(const std::string& typeStr)
    {
        if (m_components.count(typeStr) == 0)
        {
            LOG(ERROR) << typeStr << " not found in entity.";
            return std::shared_ptr<T>();
        }
        else
            return std::static_pointer_cast<T>(m_components[typeStr]);
    }

    template<typename T>
    std::shared_ptr<T> system(const std::string& type)
    {
        if (m_systems.count(type) == 0)
        {
            LOG(ERROR) << type << " not found in entity.";
            return std::shared_ptr<T>();
        }
        else
            return std::static_pointer_cast<T>(m_systems[type]);
    }

    jsonxx::Object toJson() const;

private:
    int m_id;
    std::string m_name;
    std::map<std::string, std::shared_ptr<Component>> m_components;
    std::map<std::string, std::shared_ptr<System>> m_systems;
};

}
