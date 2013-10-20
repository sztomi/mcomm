#include "component.h"
#include "reflection/metaclass.h"
#include "jsonxx.h"

namespace mcomm
{

void Component::setParent(std::shared_ptr<Entity> parent)
{
	m_parent = parent;
}

jsonxx::Object Component::toJson()
{
    auto const& M = metaClass();
}

}
