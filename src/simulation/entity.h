#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include <string>

namespace mcomm
{

class Component;
class System;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity(int aId, const std::string& aName);

	std::shared_ptr<Component> attachComponent(const std::string& type);
	std::shared_ptr<System> attachSystem(const std::string& type);

	int id() const;
	std::string toString() const;

	void update(float dt);

	template<typename T>
	std::shared_ptr<T> component(const std::string& type)
	{
		if (m_components.count(type) == 0)
			return std::shared_ptr<T>();
		else
			return std::static_pointer_cast<T>(m_components[type]);
	}

	template<typename T>
	std::shared_ptr<T> system(const std::string& type)
	{
		if (m_systems.count(type) == 0)
			return std::shared_ptr<T>();
		else
			return std::static_pointer_cast<T>(m_systems[type]);
	}

	std::string toJson() const;

private:
	int m_id;
	std::string m_name;
	std::unordered_map<std::string, std::shared_ptr<Component>> m_components;
	std::unordered_map<std::string, std::shared_ptr<System>> m_systems;
};

}
