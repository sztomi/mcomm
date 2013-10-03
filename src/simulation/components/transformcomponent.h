#pragma once

#include "SFML/Graphics/Transformable.hpp"

#include "../component.h"

namespace mcomm
{

class TransformComponent : public Component,
						   public sf::Transformable
{
public:
	std::string toString() const;
	void init(const pugi::xml_node& xml);	
};

}
