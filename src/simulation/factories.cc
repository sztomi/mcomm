#include "precompiled.h"
#include "factories.h"

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
		auto oo = begin(c.kv_map());
        auto name = oo->first;
        entity->attachComponent(name)->loadJson(oo->second->get<Object>());
    }

    auto systems = o.get<Array>("systems");

    for (size_t i = 0;
         i < systems.size();
         ++i)
    {
        auto s = systems.get<Object>(i);
		auto oo = begin(s.kv_map());
        auto name = oo->first;
        entity->attachSystem(name)->loadJson(oo->second->get<Object>());
    }

    return entity;
}

}
