#include "precompiled.h"
#include "bindings.h"
#include "external_types.h"

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

    initGeneratedBindings();
}


}
