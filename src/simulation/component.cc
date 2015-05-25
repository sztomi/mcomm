#include "precompiled.h"

namespace mcomm
{

void Component::setParent(std::shared_ptr<Entity> const& parent)
{
    m_parent = parent;
}


jsonxx::Object Component::toJson()
{
    jsonxx::Object result;

    return result;
}

void Component::loadJson(const jsonxx::Object& o)
{
    using namespace jsonxx;
}

}

