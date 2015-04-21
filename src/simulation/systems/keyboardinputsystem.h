#pragma once

#include "../system.h"

namespace mcomm
{

class KeyboardInputSystem : public System
{
	DECLARE_COMPONENT(KeyboardInputSystem)

public:
	void update(float dt) override;
};

}
