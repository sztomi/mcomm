#pragma once

#include <memory>
#include <vector>

namespace mcomm
{

class Entity;

class World
{
public:
	void update(float dt);
	void addEntity(std::shared_ptr<Entity> entity);
	void loadEntitiesXml(const std::string& fileName);

private:
	std::vector<std::shared_ptr<Entity>> m_entities;
};

}