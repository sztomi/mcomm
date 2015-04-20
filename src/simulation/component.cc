#include "component.h"
#include "reflection/metaobject.h"
#include "jsonxx.h"
#include "reflection/typeids.h"

namespace mcomm
{

void Component::setParent(std::shared_ptr<Entity> const& parent)
{
    m_parent = parent;
}

#define HANDLE_CASE(TYPE)                                      \
            case _CRC32(#TYPE):                                \
            {                                                  \
                auto value = M->getProperty<TYPE>(this, prop); \
                result << prop << value;                       \
            }                                                  \
            break;

jsonxx::Object Component::toJson()
{
    jsonxx::Object result;
    auto M = metaObject();
    auto property_names = M->propertyNames();
    for (auto& prop : property_names)
    {
        auto t_id = M->propertyTypeID(prop);
        switch (t_id)
        {
        HANDLE_CASE(int)
        HANDLE_CASE(unsigned int)
        HANDLE_CASE(double)
        HANDLE_CASE(float)
        HANDLE_CASE(bool)
        HANDLE_CASE(std::string)
        default:
            LOG(ERROR) << "Can't serialize type " << t_id << "(" << prop << ")";
            break;
        }
    }

    return result;
}

#define HANDLE_NUMBER_CASE(TYPE)                                 \
        case TYPE_ID(TYPE):                                      \
        {                                                        \
            auto value = static_cast<TYPE>(o.get<Number>(prop)); \
            M->setProperty(this, prop, value);                   \
        }                                                        \
        break;

void Component::loadJson(const jsonxx::Object& o)
{
    using namespace jsonxx;
    auto M = metaObject();
    auto property_names = M->propertyNames();
    for (auto& prop : property_names)
    {
        auto t_id = M->propertyTypeID(prop);
        switch (t_id)
        {
        HANDLE_NUMBER_CASE(int)
        HANDLE_NUMBER_CASE(unsigned int)
        HANDLE_NUMBER_CASE(float)
        HANDLE_NUMBER_CASE(double)
        case TYPE_ID(std::string):
            {
                auto value = static_cast<std::string>(o.get<String>(prop));
                M->setProperty(this, prop, value);
            }
            break;
        default:
            LOG(ERROR) << "Could not deserialize type " << t_id
                       << "(" << prop << ")";
            break;
        }
    }
}


}
