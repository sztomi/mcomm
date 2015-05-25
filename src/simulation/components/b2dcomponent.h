#pragma once

#include "precompiled.h"
#include "simulation/component.h"

namespace mcomm
{

class B2DComponent : public Component
{
public:
    B2DComponent();
    //void setPosition(float x, float y);
    //void setAngle(float alpha);

private:
    b2BodyDef m_bodydef;
    b2Body *m_body;
    b2PolygonShape m_shape;
    b2FixtureDef m_fixturedef;
};

}

REFLECT_TYPE(mcomm::B2DComponent)
