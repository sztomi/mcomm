#pragma once

#include <functional>
#include "reflection/metaobjectmanager.h"
#include "reflection/metaobject.h"


namespace mcomm
{

class Component;
class System;
class Entity;

class ObjectFactory
{
public:
    typedef std::function<void* ()> FactoryFunc;

    static ObjectFactory& instance()
	{
		static ObjectFactory inst;
		return inst;
	}

    void registerClass(const std::string& name, const FactoryFunc& create_func)
	{
		m_functions.emplace(name, create_func);
	}

	template<typename T>
    std::shared_ptr<T> create(const std::string& type)
	{
		auto func = m_functions.find(type);

		if (func == std::end(m_functions))
		{
			LOG(ERROR) << "Unregistered class: " << type << std::endl;
			return std::shared_ptr<T>();
		}

		return std::shared_ptr<T>(reinterpret_cast<T*>(func->second()));
	}

#define _SWITCH(V) auto VAR = V; if (false) {}
#define _CASE(TYPE)                                              \
		else if (VAR == TYPE_ID(TYPE))                           \
        {                                                        \
            auto value = static_cast<TYPE>(o.get<Number>(prop)); \
            M->setProperty(this, prop, value);                   \
        }

	template<typename T>
    std::shared_ptr<T> create(const std::string& type, jsonxx::Object& o)
	{
		using namespace jsonxx;
		auto func = m_functions.find(type);

		if (func == std::end(m_functions))
		{
			LOG(ERROR) << "Unregistered class: " << type << std::endl;
			return std::shared_ptr<T>();
		}

		auto result = create<T>(type);

		auto meta = MetaObjectManager::instance().getMetaObject(type);

		for (auto const& kv : o.kv_map())
		{
			std::stringstream ss;
			ss << *(kv.second);
			auto prop_str_value = ss.str();
			meta->setPropertyStr(result.get(), kv.first, prop_str_value);
		}

		/*
		auto M = MetaObjectManager::instance().getMetaObject(type);
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
                _CASE(bool)
				else if(t_id == TYPE_ID(std::string))
				{
					auto value = static_cast<std::string>(o.get<String>(prop));
					M->setProperty(result.get(), prop, value);
				}
				else
				{
					LOG(ERROR) << "Could not deserialize type " << t_id
							   << "(" << prop << ")";
				}
		}
		*/

		return result;
	}

private:
    std::unordered_map<std::string, FactoryFunc> m_functions;
};

template<class T>
class RegisterClass
{
public:
    RegisterClass(const std::string& name)
    {
        ObjectFactory::instance().registerClass(name,
                [name]() -> void*
                {
                    return reinterpret_cast<void*>(new T);
                });

        MetaObjectManager::instance().registerBindFunction(&T::bind);
    }
};

class EntityFactory
{
public:
    static EntityFactory& instance();

    std::shared_ptr<Entity> createNew(const std::string& name);
    std::shared_ptr<Entity> createNew(const std::string& name, const jsonxx::Object& o);

private:
    EntityFactory() : m_ids(0) {}
    int m_ids;
};

}

#undef _SWITCH
#undef _CASE
