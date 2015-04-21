#pragma once

#include "SFML/Graphics/Sprite.hpp"

#include "../system.h"


namespace mcomm
{

class RenderSystem : public System
{
	DECLARE_COMPONENT(RenderSystem)
public:
	void update(float dt) override;
};

}
