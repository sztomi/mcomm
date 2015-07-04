#include "precompiled.h"
#include "speedcomponent.h"

namespace mcomm
{

SpeedComponent::SpeedComponent()
	: m_x(0), m_y(0)
{ }

float SpeedComponent::x() const noexcept { return m_x; }
float SpeedComponent::y() const noexcept { return m_y; }
void SpeedComponent::setX(float value) noexcept { m_x = value; }
void SpeedComponent::setY(float value) noexcept { m_y = value; }


}
