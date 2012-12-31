#pragma once

#include "entity.h"

#include <memory>
#include <string>

#define COMPONENT(c) component<c##Component>(#c)
#define SYSTEM(s) system<s##System>(#s)

namespace pugi
{
	class xml_node;
}

namespace mcomm
{

/**
 * Represents a generic Component.
 */
class Component
{
public:
	void setParent(std::shared_ptr<Entity> parent);
	virtual std::string toString() const = 0;
	virtual void init(const pugi::xml_node& xml) {}

protected:
	std::shared_ptr<Entity> m_parent;
};

}