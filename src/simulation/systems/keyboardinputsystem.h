#pragma once

#include "../system.h"

namespace mcomm
{

class KeyboardInputSystem : public System
{
public:
	std::string toString() const;
	void update(float dt);
};

}