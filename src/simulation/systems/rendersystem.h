#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class RenderSystem : public System
{
	DECLARE_COMPONENT(RenderSystem)
public:
	void update(float dt) override;
};

}
