#pragma once

#include "simulation/system.h"

namespace mcomm
{

class TextRenderSystem : public System
{
	DECLARE_COMPONENT(TextRenderSystem)
public:
	void update(float dt) override;
};

}
