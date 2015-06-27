#pragma once

#include "precompiled.h"

namespace mcomm
{

class AnimationFrame
{
    RTTI()
public:
    AnimationFrame();
    AnimationFrame(int x, int y, int lengthMs);

    GET int texCoordX() const { return m_texCoordX; }
    GET int texCoordY() const { return m_texCoordY; }
    GET int frameLength() const { return m_frameLength; }

    SET void setTexCoordX(int value) { m_texCoordX = value; }
    SET void setTexCoordY(int value) { m_texCoordY = value; }
    SET void setFrameLength(int value) { m_frameLength = value; }

private:
    int m_texCoordX, m_texCoordY;
    int m_frameLength;
};

}

REFLECT_TYPE(mcomm::AnimationFrame)
