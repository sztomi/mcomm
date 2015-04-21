#pragma once

#include "util/bind_meta.h"
#include "simulation/factories.h"

namespace mcomm
{

class AnimationFrame
{
	DECLARE_DYNCLASS(AnimationFrame)
public:
	AnimationFrame(int x, int y, int lengthMs);

	int texCoordX() const;
	int texCoordY() const;
	int frameLength() const;

	void setTexCoordX(int value);
	void setTexCoordY(int value);
    void setFrameLength(int value);

private:
	int m_texCoordX, m_texCoordY;
	int m_frameLength;
};

}
