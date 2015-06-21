#include "precompiled.h"
#include <camp/detail/classmanager.hpp>
#include <camp/type.hpp>

namespace mcomm
{

void Component::setParent(Entity* parent)
{
    m_parent = parent;
}

}

