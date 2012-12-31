#include <iostream>

#include "factories.h"
#include "pugixml.hpp"

#define BEGIN_MAP if (false) {}
#define REGISTER_COMPONENT(tname) else if (type == #tname) { return std::make_shared<tname##Component>(); }
#define REGISTER_SYSTEM(tname) else if (type == #tname) { return std::make_shared<tname##System>(); }
#define END_MAP // just for completeness' sake :)

namespace mcomm
{

namespace ComponentFactory
{
	std::shared_ptr<Component> create(const std::string& type)
	{
		BEGIN_MAP
			REGISTER_COMPONENT(Transform)
			REGISTER_COMPONENT(Sprite)
			REGISTER_COMPONENT(Speed)
			REGISTER_COMPONENT(AnimationFrames)
            REGISTER_COMPONENT(Text)
            REGISTER_COMPONENT(Font)
		END_MAP
		
        std::cerr << "Unregistered component: " << type << std::endl;
        return std::shared_ptr<Component>();
	}
}

namespace SystemFactory
{
	std::shared_ptr<System> create(const std::string& type)
	{
		BEGIN_MAP
			REGISTER_SYSTEM(Velocity)
			REGISTER_SYSTEM(KeyboardInput)
			REGISTER_SYSTEM(Renderable)
			REGISTER_SYSTEM(SpriteAnimation)
            REGISTER_SYSTEM(TextRender)
		END_MAP
		
        std::cerr << "Unregistered system: " << type << std::endl;
        return std::shared_ptr<System>();
	}
}

std::shared_ptr<Entity> EntityFactory::createNew(const std::string& name)
{
	return std::make_shared<Entity>(m_ids++, name);
}

std::shared_ptr<Entity> EntityFactory::createNew(const std::string& name, const pugi::xml_node& xml)
{
	auto entity = createNew(name);
	auto components = xml.child("Components");

	for (auto& c : components.children())
	{
		entity->attachComponent(c.name())->init(c);
	}

	auto systems = xml.child("Systems");

	for (auto& s : systems.children())
	{
		entity->attachSystem(s.name())->init(s);
	}

	return entity;
}

}
