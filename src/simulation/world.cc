#include <iostream>

#include "world.h"
#include "entity.h"
#include "pugixml.hpp"
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

void World::loadEntitiesXml(const std::string& fileName)
{
	using namespace pugi;

	xml_document doc;
	auto load_result = doc.load_file(fileName.c_str());
	if (load_result)
	{
		auto entities = doc.child("Entities");
		for (auto& e : entities.children())
		{
			auto entity = EntityFactory::instance().createNew(e.name(), e);
			std::cout << entity->toString() << std::endl;
			addEntity(entity);			
		}
	}
	else
	{
		std::cout << "Load result: " << load_result.description() << std::endl;
	}
}

}
