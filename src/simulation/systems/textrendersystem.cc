#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "game.h"
#include "simulation/components/fontcomponent.h"
#include "simulation/components/textcomponent.h"
#include "simulation/components/transformcomponent.h"
#include "textrendersystem.h"

namespace mcomm
{

BIND_SYSTEM(TextRenderSystem)
BIND_END()

TextRenderSystem::TextRenderSystem() {}

void TextRenderSystem::update(float dt)
{
    auto font = m_parent->COMPONENT(Font);
    auto text = m_parent->COMPONENT(Text)->text();
    auto transform = m_parent->COMPONENT(Transform)->getTransform();

    sf::Text t;
    t.setString(text);
    t.setFont(*font->font().get());
    t.setCharacterSize(font->size());

    Game::instance().renderWindow()->draw(t, transform);
}

}
