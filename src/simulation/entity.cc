#include "precompiled.h"
#include "entity.h"
#include "factories.h"

namespace mcomm
{

Entity::Entity(int aId, const std::string& aName)
    : m_id(aId), m_name(aName),
    m_components(), m_systems()
{

}

int Entity::id() const { return m_id; }

std::string Entity::toString() const
{
    return boost::str(boost::format("%1% [%2%]") % m_name % m_id);
}

std::string Entity::name() const { return m_name; }

void Entity::update(float dt)
{
    for (auto& s : m_systems)
    {
        s.second->update(dt);
    }
}

Component* Entity::attachComponent(const std::string& type)
{
    auto c = ObjectFactory::instance().create<Component>(type);
    m_components[type] = c;
    m_all_components.push_back(c);
    LOG(INFO) << "Adding component:" << type;
    c->setParent(this);
    return c;
}

System* Entity::attachSystem(const std::string& type)
{
    auto s = ObjectFactory::instance().create<System>(type);
    m_systems[type] = s;
    m_all_systems.push_back(s);
    s->setParent(this);
    LOG(INFO) << "Adding system:" << type;
    return s;
}

void Entity::bindClass()
{
    camp::Class::declare<Entity>()
        .property("id", &mcomm::Entity::id)
        .property("components", &mcomm::Entity::m_all_components)
        .property("system", &Entity::m_all_systems)
        .function("toString", &mcomm::Entity::toString)
    ;
}

}
