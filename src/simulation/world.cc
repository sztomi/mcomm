#include "precompiled.h"

#include "world.h"
#include "simulation/components/transformcomponent.h"
#include "factories.h"

namespace mcomm
{

void World::update(float dt)
{
	for (auto& entity : m_entities)
	{
		entity->update(dt);
	}
}

void World::addEntity(std::shared_ptr<Entity> entity)
{
	m_entities.push_back(entity);
}

void World::saveJson(std::string const& fileName)
{
	jsonxx::Object output;
	jsonxx::Array entities;
	for (auto& e : m_entities)
	{
		entities << jsonxx::Object(e->name(), e->toJson());
	}
	output << "entities" << entities;

	std::fstream outfile(fileName, std::ios::out);
	outfile << output.json();
}

void World::loadJson(const std::string& fileName)
{
	std::fstream f(fileName, std::ios::in);
	jsonxx::Object worldjson;
	worldjson.parse(f);

	auto entities = worldjson.get<jsonxx::Array>("entities");

	for (std::size_t i = 0; i < entities.size(); ++i)
	{
		auto e = entities.get<jsonxx::Object>(i);
		auto name = begin(e.kv_map())->first;
		auto obj = begin(e.kv_map())->second->get<jsonxx::Object>();
		auto entity = EntityFactory::instance().createNew(name, obj);
		addEntity(entity);
	}

}

}
