#pragma once

#include "simulation/system.h"

namespace mcomm
{

class TextRenderSystem : public System
{
public:
	std::string toString() const;
	void update(float dt);
};

}
