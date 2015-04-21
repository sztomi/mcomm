#pragma once

namespace mcomm
{

class AnimationFrame
{
public:
	AnimationFrame(int x, int y, int lengthMs);
	//AnimationFrame(const pugi::xml_node& xml);

	int texCoordX() const;
	int texCoordY() const;
	int frameLength() const;

private:
	int m_texCoordX, m_texCoordY;
	int m_frameLength;
};

}
