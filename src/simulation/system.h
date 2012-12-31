#pragma once

#include "component.h"

namespace mcomm
{

class System : public Component
{
public:
	virtual void update(float dt) = 0;
};

}