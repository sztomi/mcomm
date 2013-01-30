#pragma once

#include "SFML/Graphics/Sprite.hpp"

#include "../system.h"


namespace mcomm
{

class RenderSystem : public System
{
public:
	std::string toString() const;
	void update(float dt);
};

}
