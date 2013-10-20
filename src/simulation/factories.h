#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "glog/logging.h"
#include "jsonxx.h"

#include "entity.h"
#include "reflection/metaclassmanager.h"

#define REGISTER_COMPONENT(CLASS) static const RegisterComponent<CLASS> FactoryRegister{CLASS::ClassName};
#define REGISTER_SYSTEM(CLASS) static const RegisterSystem<CLASS> FactoryRegister{CLASS::ClassName};

namespace mcomm
{

class Component;
class System;
class Entity;

class ComponentFactory
{
public:
    typedef std::function<std::shared_ptr<Component> ()> CompFactoryFunc;

    static ComponentFactory& instance();
    void registerClass(const std::string& name, const CompFactoryFunc& create_func);
    std::shared_ptr<Component> create(const std::string& type);

private:
    std::unordered_map<std::string, CompFactoryFunc> m_functions;
};

template<class T>
class RegisterComponent
{
public:
    RegisterComponent(const std::string& name)
    {
        ComponentFactory::instance().registerClass(name,
                []() -> std::shared_ptr<Component> 
                {
                    return std::make_shared<T>(); 
                });

        MetaClassManager::instance().registerBindFunction(&T::bind);
    }
};

class SystemFactory
{
public:
    typedef std::function<std::shared_ptr<System>(void)> SysFactoryFunc;

    static SystemFactory& instance();
    void registerClass(const std::string& name, SysFactoryFunc& create_func);
    std::shared_ptr<System> create(const std::string& type);

private:
    std::unordered_map<std::string, SysFactoryFunc> m_functions;
};

template<class T>
class RegisterSystem
{
    RegisterSystem(const std::string& name)
    {
        SystemFactory::instance().registerClass(name,
                []() -> std::shared_ptr<Component> 
                {
                    return std::make_shared<T>(); 
                });

        MetaClassManager::instance().registerBindFunction(&T::bind);
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
