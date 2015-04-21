#include <boost/format.hpp>
#include "jsonxx.h"

#include "entity.h"
#include "factories.h"
#include "system.h"

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

std::shared_ptr<Component> Entity::attachComponent(const std::string& type)
{
    auto c = ComponentFactory::instance().create(type);
    m_components[type] = c;
    c->setParent(shared_from_this());
    return c;
}

std::shared_ptr<System> Entity::attachSystem(const std::string& type)
{
    auto s = SystemFactory::instance().create(type);
    m_systems[type] = s;
    s->setParent(shared_from_this());
    return s;
}

jsonxx::Object Entity::toJson() const
{
	jsonxx::Object result;
	jsonxx::Array components, systems;

	for (auto& c : m_components)
	{
		components << jsonxx::Object(c.second->name(), c.second->toJson());
	}

	for (auto& s : m_systems)
	{
		systems << jsonxx::Object(s.second->name(), s.second->toJson());
	}

	result << "name" << m_name;
	result << "components" << components;
	result << "systems" << systems;

	return result;
}

}
