#pragma once

#include "precompiled.h"
#include "simulation/world.h"

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
	World world;
	GameState state;
	std::shared_ptr<sf::RenderWindow> m_renderWindow;

};

}
