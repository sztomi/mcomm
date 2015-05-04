#pragma once

#include <memory>
#include <string>

#include "reflection/metaobjectmanager.h"
#include "simulation/factories.h"

#define COMPONENT(c) component<c##Component>(#c"Component")
#define SYSTEM(s) system<s##System>(#s"System")

#define DECLARE_COMPONENT(c) public:                                   \
	DECLARE_BINDABLE2(c)                                               \
    c();                                                               \
    private:

#define BIND_COMPONENT(THECLASS)                                       \
	REGISTER_CLASS(THECLASS)                                           \
	BIND_CLASS(THECLASS)

#define BIND_SYSTEM(THECLASS)                                          \
	REGISTER_CLASS(THECLASS)                                           \
	BIND_CLASS(THECLASS)                                               \
		   .def("update", &THECLASS::update)

namespace jsonxx
{
    class Object;
}

namespace mcomm
{

class MetaObject;
class Entity;

/**
 * Represents a generic Component.
 */
class Component
{
public:
    virtual void setParent(std::shared_ptr<Entity> const& parent);
    virtual std::string name() const = 0;

    virtual void loadJson(const jsonxx::Object& o);
    virtual jsonxx::Object toJson();

    virtual std::shared_ptr<MetaObject> metaObject() const = 0;

protected:
    std::shared_ptr<Entity> m_parent;
};

class System : public Component
{
public:
	virtual void update(float dt) = 0;
};

}
