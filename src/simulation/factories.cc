#include <iostream>

#include "jsonxx.h"
#include "glog/logging.h"

#include "component.h"
#include "factories.h"
#include "system.h"

using namespace jsonxx;

namespace mcomm
{

ComponentFactory& ComponentFactory::instance()
{
    static ComponentFactory inst;
    return inst;
}

void ComponentFactory::registerClass(const std::string& name, const CompFactoryFunc& create_func)
{
    m_functions.emplace(name, create_func);
}

std::shared_ptr<Component> ComponentFactory::create(const std::string& type)
{
    auto func = m_functions.find(type);

    if (func == std::end(m_functions))
    {
        LOG(ERROR) << "Unregistered component: " << type << std::endl; 
        return std::shared_ptr<Component>();
    }

    return func->second();
}

SystemFactory& SystemFactory::instance()
{
    static SystemFactory inst;
    return inst;
}

void SystemFactory::registerClass(const std::string& name, SysFactoryFunc& create_func)
{
    m_functions.emplace(name, create_func);
}

std::shared_ptr<System> SystemFactory::create(const std::string& type)
{
    auto func = m_functions.find(type);

    if (func == std::end(m_functions))
    {
        LOG(ERROR) << "Unregistered system: " << type << std::endl; 
        return std::shared_ptr<System>();
    }

    return func->second();
}

std::shared_ptr<Entity> EntityFactory::createNew(const std::string& name)
{
    return std::make_shared<Entity>(m_ids++, name);
}

EntityFactory& EntityFactory::instance()
{
    static EntityFactory inst;
    return inst;
}

std::shared_ptr<Entity> EntityFactory::createNew(const std::string& name, const Object& o)
{
    auto entity = createNew(name);
    auto components = o.get<Array>("components");

    for (size_t i = 0; 
         i < components.size();
         ++i)
    {
        auto c = components.get<Object>(i);
        auto name = c.get<String>("name");
        entity->attachComponent(name)->loadJson(c);
    }

    auto systems = o.get<Array>("systems");
    
    for (size_t i = 0; 
         i < systems.size();
         ++i)
    {
        auto s = systems.get<Object>(i);
        auto name = s.get<String>("name");
        entity->attachSystem(name)->loadJson(s);
    }

    return entity;
}

}
