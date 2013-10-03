#include "speedcomponent.h"
#include "pugixml.hpp"

namespace mcomm
{

SpeedComponent::SpeedComponent()
	: m_x(0), m_y(0)
{

}

std::string SpeedComponent::toString() const
{
	return "SpeedComponent";
}

void SpeedComponent::init(const pugi::xml_node& xml)
{
	m_x = xml.child("X").text().as_float();
	m_y = xml.child("Y").text().as_float();
}

float SpeedComponent::x() const
{
	return m_x;
}

float SpeedComponent::y() const
{
	return m_y;
}

void SpeedComponent::setX(float value)
{
	m_x = value;
}

void SpeedComponent::setY(float value)
{
	m_y = value;
}

}