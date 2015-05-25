#pragma once

#include <memory>
#include <string>

#include <camp/camptype.hpp>
#include "macros.h"

#define COMPONENT(c) component<c##Component>(#c"Component")
#define SYSTEM(s) system<s##System>(#s"System")

namespace jsonxx
{
    class Object;
}

namespace mcomm
{

class Entity;

/**
 * Represents a generic Component.
 */
class Component
{
public:
    virtual void setParent(std::shared_ptr<Entity> const& parent);
    virtual std::string name() const { return "unset"; }

    virtual void loadJson(const jsonxx::Object& o);
    virtual jsonxx::Object toJson();

protected:
    std::shared_ptr<Entity> m_parent;
};

class System : public Component
{
public:
	virtual void update(float dt) = 0;
};

}
