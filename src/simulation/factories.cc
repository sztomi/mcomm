#include "precompiled.h"
#include "factories.h"

using namespace jsonxx;

namespace mcomm
{

Entity* EntityFactory::createNew(const std::string& name)
{
    return new Entity(m_ids++, name);
}

EntityFactory& EntityFactory::instance()
{
    static EntityFactory inst;
    return inst;
}

}
