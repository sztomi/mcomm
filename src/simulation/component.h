#pragma once

#include <memory>
#include <string>

#include <camp/camptype.hpp>
#include "macros.h"

#define COMPONENT(c) component<c##Component>("mcomm::" #c "Component")
#define SYSTEM(s) system<s##System>("mcomm::" #s "System")

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
    RTTI()
public:
    HIDDEN virtual void setParent(Entity* parent);
    virtual std::string name() const { return "unset"; }

    virtual void revive() {}

protected:
    Entity* m_parent;
};

class System : public Component
{
    RTTI()
public:
    virtual void update(float dt) {}

};

}

REFLECT_TYPE(mcomm::Component)
REFLECT_TYPE(mcomm::System)
