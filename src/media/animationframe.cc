#include "animationframe.h"
#include "pugixml.hpp"

namespace mcomm
{

AnimationFrame::AnimationFrame(int x, int y, int length)
	: m_texCoordX(x), m_texCoordY(y), m_frameLength(length)
{

}

AnimationFrame::AnimationFrame(const pugi::xml_node& xml)
{
	m_texCoordX = xml.child("TexCoordX").text().as_int();
	m_texCoordY = xml.child("TexCoordY").text().as_int();
	m_frameLength = xml.child("Length").text().as_int();
}

int AnimationFrame::texCoordX() const { return m_texCoordX; }
int AnimationFrame::texCoordY() const { return m_texCoordY; }
int AnimationFrame::frameLength() const { return m_frameLength; }

}