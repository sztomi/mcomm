#include "precompiled.h"
#include "animationframe.h"
#include "simulation/factories.h"
#include "util/bind_meta.h"

namespace mcomm
{

BIND_GENERIC(AnimationFrame)
	.property("texcoord_x",
			  &AnimationFrame::texCoordX,
			  &AnimationFrame::setTexCoordX)
	.property("texcoord_y",
			  &AnimationFrame::texCoordY,
			  &AnimationFrame::setTexCoordY)
	.property("frameLength",
			  &AnimationFrame::frameLength,
			  &AnimationFrame::setFrameLength)
BIND_END()

AnimationFrame::AnimationFrame()
	: m_texCoordX(0), m_texCoordY(0), m_frameLength(0)
{
}

AnimationFrame::AnimationFrame(int x, int y, int length)
	: m_texCoordX(x), m_texCoordY(y), m_frameLength(length)
{

}

}
