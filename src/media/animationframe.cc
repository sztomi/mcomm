#include "animationframe.h"
#include "util/constexpr_crc.h"
#include "util/bind_meta.h"
#include "glog/logging.h"

#include "simulation/factories.h"

namespace mcomm
{

REGISTER_CLASS(AnimationFrame)

BIND_CLASS(AnimationFrame)
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

int AnimationFrame::texCoordX() const { return m_texCoordX; }
int AnimationFrame::texCoordY() const { return m_texCoordY; }
int AnimationFrame::frameLength() const { return m_frameLength; }

void AnimationFrame::setTexCoordX(int value) { m_texCoordX = value; }
void AnimationFrame::setTexCoordY(int value) { m_texCoordY = value; }
void AnimationFrame::setFrameLength(int value) { m_frameLength = value; }

}
