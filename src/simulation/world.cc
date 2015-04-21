#include <iostream>
#include <fstream>
#include "jsonxx.h"

#include "world.h"
#include "entity.h"
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
		LOG(INFO) << "saving " << e->toString();
		entities << e->toJson();
		LOG(INFO) << e->toJson().json();
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

	//for (auto& e : entities.children())
	//{
		//auto entity = EntityFactory::instance().createNew(e.name(), e);
		//std::cout << entity->toString() << std::endl;
		//addEntity(entity);
	//}
}

}
