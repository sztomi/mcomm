#pragma once

#include "precompiled.h"
#include "simulation/world.h"
#include "gui/editor.h"

namespace sf
{
    class RenderWindow;
}

namespace mcomm
{

enum class GameState
{
    PRERUN,
    MENU,
    RUNNING,
    EXITING,
    POSTEXIT
};

class Game
{
public:
    void setup();
    void run();
    void drawGui();

    std::shared_ptr<sf::RenderWindow> renderWindow() const;

    static Game& instance()
    {
        static Game inst;
        return inst;
    }

private:
    Game();

    void runStep(float frameTime);

private:
    bool m_designMode = false;
    std::shared_ptr<World> m_world;
    GameState state;
    std::shared_ptr<sf::RenderWindow> m_renderWindow;
    Editor m_editor;
};

}
