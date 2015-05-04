#include "precompiled.h"
#include "speedcomponent.h"

using namespace jsonxx;
using namespace lualite;

namespace mcomm
{

BIND_COMPONENT(SpeedComponent)
	.property("x", &SpeedComponent::x, &SpeedComponent::setX)
	.property("y", &SpeedComponent::y, &SpeedComponent::setY)
BIND_END()

SpeedComponent::SpeedComponent()
	: m_x(0), m_y(0)
{ }

float SpeedComponent::x() const { return m_x; }
float SpeedComponent::y() const { return m_y; }
void SpeedComponent::setX(float value) { m_x = value; }
void SpeedComponent::setY(float value) { m_y = value; }


}
