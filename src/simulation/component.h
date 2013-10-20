#pragma once

#include <memory>
#include <string>

#include "glog/logging.h"

#include "entity.h"
#include "factories.h"
#include "reflection/metaclassmanager.h"
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
    std::shared_ptr<MetaClass> metaClass() const {                   \
        return MetaClassManager::instance().getMetaClass(ClassName); \
    }                                                                \
    static void bind();                                              \
    private:                                                        

namespace jsonxx
{
    class Object;
}

namespace mcomm
{

class MetaClass;

/**
 * Represents a generic Component.
 */
class Component
{
public:
    void setParent(std::shared_ptr<Entity> parent);
    virtual std::string name() const = 0;

    virtual void loadJson(const jsonxx::Object& o);
    virtual jsonxx::Object toJson();

    virtual std::shared_ptr<MetaClass> metaClass() const = 0;

protected:
    std::shared_ptr<Entity> m_parent;
};

}
