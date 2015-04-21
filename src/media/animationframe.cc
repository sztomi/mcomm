#include "animationframe.h"

namespace mcomm
{

AnimationFrame::AnimationFrame(int x, int y, int length)
	: m_texCoordX(x), m_texCoordY(y), m_frameLength(length)
{

}

int AnimationFrame::texCoordX() const { return m_texCoordX; }
int AnimationFrame::texCoordY() const { return m_texCoordY; }
int AnimationFrame::frameLength() const { return m_frameLength; }

}
