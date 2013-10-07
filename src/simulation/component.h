#pragma once

#include <memory>
#include <string>

#include "glog/logging.h"

#include "entity.h"

#define COMPONENT(c) component<c##Component>(#c)
#define SYSTEM(s) system<s##System>(#s)

namespace jsonxx
{
    class Object;
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
    virtual std::string name() const = 0;
    virtual void loadJson(const jsonxx::Object& o) {}
    virtual jsonxx::Object toJson() const = 0;

protected:
	std::shared_ptr<Entity> m_parent;
};

}
