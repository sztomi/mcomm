#pragma once

#include "SFML/Graphics/Transformable.hpp"

#include "../component.h"

namespace mcomm
{

class TransformComponent : public Component, public sf::Transformable
{
public:
    std::string name() const;
    void loadJson(const jsonxx::Object& o);
    jsonxx::Object toJson() const;

};

}
