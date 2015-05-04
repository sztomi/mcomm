#pragma once

#include "precompiled.h"

namespace mcomm
{

class Entity;

class World
{
public:
	void update(float dt);
	void addEntity(std::shared_ptr<Entity> entity);
	void loadJson(const std::string& fileName);
	void saveJson(std::string const& fileName);

private:
	std::vector<std::shared_ptr<Entity>> m_entities;
};

}
