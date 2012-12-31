#pragma once

#include "simulation/component.h"

namespace mcomm
{

class SpeedComponent : public Component
{
public:
	SpeedComponent();

	void init(const pugi::xml_node& xml);
	std::string toString() const;

	float x() const;
	float y() const;

	void setX(float value);
	void setY(float value);

private:
	float m_x, m_y;
};

}