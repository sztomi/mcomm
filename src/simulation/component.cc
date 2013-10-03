#include "component.h"

namespace mcomm
{

void Component::setParent(std::shared_ptr<Entity> parent)
{
	m_parent = parent;
}

}