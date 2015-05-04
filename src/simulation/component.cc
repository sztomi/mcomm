#include "precompiled.h"

#include "reflection/metaobjectmanager.h"

#define _SWITCH(V) auto VAR = V; if (false) {}

namespace mcomm
{

void Component::setParent(std::shared_ptr<Entity> const& parent)
{
    m_parent = parent;
}

#define _CASE(TYPE)                                        \
		else if (VAR == TYPE_ID(TYPE))                     \
		{                                                  \
			auto value = M->getProperty<TYPE>(this, prop); \
			result << prop << value;                       \
		}

jsonxx::Object Component::toJson()
{
    jsonxx::Object result;
    auto M = metaObject();
    auto property_names = M->propertyNames();
    for (auto& prop : property_names)
    {
		if (prop == "name") { continue; }

        auto t_id = M->propertyTypeID(prop);
        _SWITCH(t_id)
            _CASE(int)
            _CASE(unsigned int)
            _CASE(double)
            _CASE(float)
            _CASE(bool)
            _CASE(std::string)
		else
		{
            LOG(ERROR) << "Can't serialize type " << t_id << "(" << prop << ")";
            break;
		}
    }

    return result;
}
#undef _CASE

#define _CASE(TYPE)                                              \
		else if (VAR == TYPE_ID(TYPE))                           \
        {                                                        \
            auto value = static_cast<TYPE>(o.get<Number>(prop)); \
            M->setProperty(this, prop, value);                   \
        }                                                        \

void Component::loadJson(const jsonxx::Object& o)
{
    using namespace jsonxx;
    auto M = metaObject();
    auto property_names = M->propertyNames();
    for (auto& prop : property_names)
    {
		if (prop == "name") { continue; }
        auto t_id = M->propertyTypeID(prop);
        _SWITCH(t_id)
            _CASE(int)
            _CASE(unsigned int)
            _CASE(float)
            _CASE(double)
			else if(t_id == TYPE_ID(std::string))
            {
                auto value = static_cast<std::string>(o.get<String>(prop));
                M->setProperty(this, prop, value);
            }
			else
			{
				LOG(ERROR) << "Could not deserialize type " << t_id
						   << "(" << prop << ")";
			}
    }
}
#undef _CASE

}

#undef _SWITCH
