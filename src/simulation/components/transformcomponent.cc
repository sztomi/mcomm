#include "transformcomponent.h"
#include "jsonxx.h"

using namespace jsonxx;

namespace mcomm 
{

std::string TransformComponent::name() const
{
    return "TransformComponent";
}

void TransformComponent::loadJson(const Object& o)
{
    auto scale = o.get<Object>("scale");

    if (!scale.empty())
    {
        auto sx = scale.get<Number>("x");
        auto sy = scale.get<Number>("y");
        setScale(static_cast<float>(sx), static_cast<float>(sy));
    }

    auto origin = o.get<Object>("origin");
    if (!origin.empty())
    {
        auto sx = origin.get<Number>("x");
        auto sy = origin.get<Number>("y");
        setOrigin(static_cast<float>(sx), static_cast<float>(sy));
    }

    auto position = o.get<Object>("position");

    if (!position.empty())
    {
        auto sx = position.get<Number>("x");
        auto sy = position.get<Number>("y");
        setPosition(static_cast<float>(sx), static_cast<float>(sy));
    }
}

Object TransformComponent::toJson() const
{
    Object result;

    Object scale;
    scale << "x" << getScale().x;
    scale << "y" << getScale().y;
    result << "scale" << scale;

    Object position;
    position << "x" << getPosition().x;
    position << "y" << getPosition().y;
    result << "position" << position;

    Object origin;
    origin << "x" << getOrigin().x;
    origin << "y" << getOrigin().y;
    result << "origin" << origin;

    return result;
}

}
