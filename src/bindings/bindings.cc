#include "precompiled.h"
#include "bindings.h"
#include "external_types.h"
#include "simulation/world.h"
#include "simulation/entity.h"
#include "simulation/components/animationframescomponent.h"

namespace mcomm
{

void initGeneratedBindings();

void initBindings()
{
    new camp::detail::ClassManager();

    camp::Class::declare<sf::Sprite>()
        .function("setPosition", static_cast<void (sf::Sprite::*)(float, float)>(&sf::Sprite::setPosition))
        ;

    camp::Class::declare<sf::Font>()
        .function("loadFromFile", &sf::Font::loadFromFile)
        ;

    camp::Class::declare<sf::Drawable>()
        .tag("sf::Drawable")
        ;

    camp::Class::declare<sf::Transformable>()
        .tag("sf::Transformable")
        ;

    World::bindClass();
    Entity::bindClass();

    initGeneratedBindings();

    AnimationFramesComponent::bindClass();
}


}
