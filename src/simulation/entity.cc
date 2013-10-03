#include <boost/format.hpp>

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

void Entity::update(float dt)
{
	for (auto& s : m_systems)
	{
		s.second->update(dt);
	}
}

std::shared_ptr<Component> Entity::attachComponent(const std::string& type)
{
	auto c = ComponentFactory::create(type);
	m_components[type] = c;
	c->setParent(shared_from_this());
	return c;
}

std::shared_ptr<System> Entity::attachSystem(const std::string& type)
{
	auto s = SystemFactory::create(type);
	m_systems[type] = s;
	s->setParent(shared_from_this());
	return s;
}

}