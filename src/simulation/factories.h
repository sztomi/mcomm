#pragma once

#include <memory>
#include <string>

#include "entity.h"
#include "component.h"
#include "system.h"

#include "components/transformcomponent.h"
#include "components/spritecomponent.h"
#include "components/speedcomponent.h"
#include "components/animationframescomponent.h"
#include "components/textcomponent.h"
#include "components/fontcomponent.h"
#include "components/drawablecomponent.h"

#include "systems/velocitysystem.h"
#include "systems/keyboardinputsystem.h"
#include "systems/rendersystem.h"
#include "systems/spriteanimationsystem.h"

namespace pugi
{
	class xml_node;
}

namespace mcomm
{
	namespace ComponentFactory
	{
		std::shared_ptr<Component> create(const std::string& type);
	}

	namespace SystemFactory
	{
		std::shared_ptr<System> create(const std::string& type);
	}

	class EntityFactory
	{
	public:
		static EntityFactory& instance()
		{
			static EntityFactory inst;
			return inst;
		}

		std::shared_ptr<Entity> createNew(const std::string& name);
		std::shared_ptr<Entity> createNew(const std::string& name, const pugi::xml_node& xml);

	private:
		EntityFactory() : m_ids(0) {}
		int m_ids;
	};
}
