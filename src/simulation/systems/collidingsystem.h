#pragma once

#include "../system.h"

namespace mcomm
{

class CollidingSystem : public System
{
	DECLARE_COMPONENT(CollidingSystem)

public:
	void update(float dt) override;
};

}
