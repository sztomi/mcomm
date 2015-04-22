#pragma once

#include <memory>
#include <string>

#include "glog/logging.h"

#include "entity.h"
#include "factories.h"
#include "reflection/metaobjectmanager.h"
#include "reflection/typeids.h"
#include "scripting/scriptmanager.h"
#include "util/constexpr_crc.h"
#include "util/bind_meta.h"

#include "lua.hpp"
#include "lualite.hpp"

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

}
