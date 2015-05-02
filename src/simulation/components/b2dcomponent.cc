#include "precompiled.h"
#include "b2dcomponent.h"

using namespace lualite;

namespace mcomm
{

BIND_COMPONENT(B2DComponent)
	.enum_("b2_dynamicBody", b2_dynamicBody)
	.enum_("b2_staticBody", b2_staticBody)
	//.def("set_position", &B2DComponent::setPosition)
	//.def("set_angle", &B2DComponent::setAngle)
BIND_END()

B2DComponent::B2DComponent()
{
}

}
