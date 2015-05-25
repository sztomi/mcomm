#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class KeyboardInputSystem : public System
{
public:
    KeyboardInputSystem();

    void update(float dt) override;
};

}
REFLECT_TYPE(mcomm::KeyboardInputSystem)
