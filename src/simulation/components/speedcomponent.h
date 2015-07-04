#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class SpeedComponent : public Component
{
    RTTI()
public:
    SpeedComponent();

    GET float x() const noexcept;
    SET void setX(float value) noexcept;
    GET float y() const noexcept;
    SET void setY(float value) noexcept;

private:
    float m_x, m_y;
};

}
REFLECT_TYPE(mcomm::SpeedComponent)
