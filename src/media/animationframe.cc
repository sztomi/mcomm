#include "precompiled.h"
#include "animationframe.h"

namespace mcomm
{

AnimationFrame::AnimationFrame()
	: m_texCoordX(0), m_texCoordY(0), m_frameLength(0)
{
}

AnimationFrame::AnimationFrame(int x, int y, int length)
	: m_texCoordX(x), m_texCoordY(y), m_frameLength(length)
{

}

}
