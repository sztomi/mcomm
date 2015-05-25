#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class TextRenderSystem : public System
{
public:
    TextRenderSystem();
	void update(float dt) override;
};

}
REFLECT_TYPE(mcomm::TextRenderSystem)
