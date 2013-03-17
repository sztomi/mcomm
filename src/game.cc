#include <algorithm>
#include <memory>

#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "game.h"
#include "media/texturemanager.h"
#include "simulation/collisiongrid.h"
#include "simulation/entity.h"
#include "simulation/factories.h"

namespace mcomm
{

Game::Game() : state(GameState::PRERUN) 
{
	m_renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "mcomm");
}

std::shared_ptr<sf::RenderWindow> Game::renderWindow() const
{
	return m_renderWindow;
}

void Game::setup()
{
	TextureManager::instance().addTexture("res/sprites1.png", "sprite1");
	world.loadEntitiesXml("res/start_entities.xml");
}

void Game::run()
{
	state = GameState::RUNNING;
	sf::Clock clock;

	while (state == GameState::RUNNING)
	{
		float elapsed = clock.restart().asSeconds();

		sf::Event event;
		m_renderWindow->pollEvent(event);

		switch (event.type)
		{
		case sf::Event::Closed:
			state = GameState::EXITING;
			break;
		default:
			break;
		}

		m_renderWindow->clear(sf::Color(150, 150, 150, 255));
		runStep(elapsed);
		m_renderWindow->display();
	}
}

void Game::runStep(float frameTime)
{
	const float timeStep = 0.1f;

    CollisionGrid::instance().clearAll();

	while (frameTime > 0.0f)
	{
		float dt = std::min(frameTime, timeStep);
		world.update(dt);
		frameTime -= dt;
	}
}

}
