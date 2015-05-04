#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class BoundingBoxComponent : public Component
{
	DECLARE_COMPONENT(BoundingBoxComponent)

private:
    sf::IntRect m_rectangle;
};

}
