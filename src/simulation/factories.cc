#include <iostream>

#include "jsonxx.h"
#include "glog/logging.h"

#include "component.h"
#include "factories.h"
#include "system.h"

using namespace jsonxx;

namespace mcomm
{

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
