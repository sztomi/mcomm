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

    GET float x() const;
    SET void setX(float value);
    GET float y() const;
    SET void setY(float value);

private:
    float m_x, m_y;
};

}
REFLECT_TYPE(mcomm::SpeedComponent)
