#pragma once

#include "simulation/component.h"
#include "util/bind_meta.h"

namespace mcomm
{

class AnimationFrame
{
	DECLARE_DYNCLASS(AnimationFrame)
public:
	AnimationFrame(int x, int y, int lengthMs);

	int texCoordX() const { return m_texCoordX; }
	int texCoordY() const { return m_texCoordY; }
	int frameLength() const { return m_frameLength; }

	void setTexCoordX(int value) { LOG(INFO) << "setTexCoordX " << value; m_texCoordX = value; }
	void setTexCoordY(int value) { m_texCoordY = value; }
	void setFrameLength(int value) { m_frameLength = value; }

private:
	int m_texCoordX, m_texCoordY;
	int m_frameLength;
};

}
