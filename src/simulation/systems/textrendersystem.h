#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class TextRenderSystem : public System
{
	DECLARE_COMPONENT(TextRenderSystem)
public:
	void update(float dt) override;
};

}
