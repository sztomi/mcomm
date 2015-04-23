#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "glog/logging.h"
#include "jsonxx.h"

#include "entity.h"
#include "reflection/metaobjectmanager.h"

#define REGISTER_CLASS(CLASS) static const RegisterClass<CLASS> FactoryRegister{CLASS::ClassName};

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

	template<typename T>
    std::shared_ptr<T> create(const std::string& type, jsonxx::Object& obj)
	{
		auto func = m_functions.find(type);

		if (func == std::end(m_functions))
		{
			LOG(ERROR) << "Unregistered class: " << type << std::endl;
			return std::shared_ptr<T>();
		}

		auto result = std::shared_ptr<T>(reinterpret_cast<T*>(func->second()));
		auto meta = MetaObjectManager::instance().getMetaObject(type);

		for (auto const& kv : obj.kv_map())
		{
			meta->setProperty(result.get(), kv.first, kv.second->get<std::string>());
		}

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
                []() -> void*
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
