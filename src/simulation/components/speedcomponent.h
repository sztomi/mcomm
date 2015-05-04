#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class SpeedComponent : public Component
{
	DECLARE_COMPONENT(SpeedComponent)

public:
    float x() const;
    void setX(float value);
    float y() const;
    void setY(float value);

private:
    float m_x, m_y;
};

}
