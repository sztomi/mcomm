#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class KeyboardInputSystem : public System
{
	DECLARE_COMPONENT(KeyboardInputSystem)

public:
	void update(float dt) override;
};

}
