#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "entity.h"
#include "component.h"
#include "system.h"

#define REGISTER_COMPONENT(c) static RegisterComponent<c> m___GENERATED___comp_reg_##c(#c);
#define REGISTER_SYSTEM(c) static RegisterSystem<c> m___GENERATED___sys_reg##c(#c);

namespace mcomm
{

class ComponentFactory
{
public:
    typedef std::function<std::shared_ptr<Component>(void)> CompFactoryFunc;

    static ComponentFactory& instance();
    void register_class(const std::string& name, CompFactoryFunc& create_func);
    std::shared_ptr<Component> create(const std::string& type);

private:
    std::unordered_map<std::string, CompFactoryFunc> m_functions;
};

template<class T>
class RegisterComponent
{
    RegisterComponent(const std::string& name)
    {
        ComponentFactory::instance().register_class(name, 
                []() -> std::shared_ptr<Component> { return std::make_shared<T>(); });
        // TODO: luabind?
    }
};

template<class T>
class RegisterSystem
{
    RegisterSystem(const std::string& name)
    {
        SystemFactory::instance().register_class(name, 
                []() -> std::shared_ptr<System> { return std::make_shared<T>(); });
        // TODO: luabind?
    }
};

class SystemFactory
{
public:
    typedef std::function<std::shared_ptr<System>(void)> SysFactoryFunc;

    static SystemFactory& instance();
    void register_class(const std::string& name, SysFactoryFunc& create_func);
    std::shared_ptr<System> create(const std::string& type);

private:
    std::unordered_map<std::string, SysFactoryFunc> m_functions;
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
