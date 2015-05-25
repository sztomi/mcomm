#pragma once

#include "precompiled.h"
#include <functional>


namespace mcomm
{

class Component;
class System;
class Entity;

class ObjectFactory
{
public:
    typedef std::function<void* ()> FactoryFunc;

    static ObjectFactory& instance()
    {
            static ObjectFactory inst;
            return inst;
    }

    template<typename T>
    std::shared_ptr<T> create(const std::string& type)
    {
        auto& metaclass = camp::classById(camp::StringId(type.c_str()));
        auto userobj = metaclass.construct(camp::Args());

        return std::shared_ptr<T>(userobj.get<T*>());
    }
};

class EntityFactory
{
public:
    static EntityFactory& instance();

    std::shared_ptr<Entity> createNew(const std::string& name);
    std::shared_ptr<Entity> createNew(const std::string& name, const jsonxx::Object& o);

private:
    EntityFactory() : m_ids(0) {}
    int m_ids;
};

}
