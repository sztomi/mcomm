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

#include "lua.hpp"
#include "lualite.hpp"

#define COMPONENT(c) component<c##Component>(#c)
#define SYSTEM(s) system<s##System>(#s)
#define DECLARE_COMPONENT(c) public:                                 \
    c();                                                             \
    static constexpr char const* ClassName = #c;                     \
    static constexpr uint32_t const ClassTypeID = TYPE_ID(ClassName);\
    std::string name() const { return ClassName; }                   \
    std::shared_ptr<MetaObject> metaObject() const {                   \
        return MetaObjectManager::instance().getMetaObject(ClassName); \
    }                                                                \
    static void bind();                                              \
    private:


#define BIND_BEGIN(THECLASS)                                         \
	void THECLASS::bind()                                            \
	{																 \
		static bool bound = false;                                   \
		if (bound) return;                                           \
		auto c = lualite::class_<THECLASS>(ClassName)                \
		           .constructor()                                    \
				   .property("name", &THECLASS::name)                \

#define BIND_END()                                                   \
    ;auto m = mcomm::MetaObject::create(ClassName, c);                \
    MetaObjectManager::instance().registerClass(m);                   \
    ScriptManager::instance().registerClass(c);                      \
	bound = true; }

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
    void setParent(std::shared_ptr<Entity> const& parent);
    virtual std::string name() const = 0;

    virtual void loadJson(const jsonxx::Object& o);
    virtual jsonxx::Object toJson();

    virtual std::shared_ptr<MetaObject> metaObject() const = 0;

protected:
    std::shared_ptr<Entity> m_parent;
};

}
