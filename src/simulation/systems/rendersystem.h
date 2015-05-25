#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class RenderSystem : public System
{
public:
    RenderSystem();
    void update(float dt) override;
};

}
REFLECT_TYPE(mcomm::RenderSystem)
