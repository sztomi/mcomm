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
#include "simulation/component.h"
#include "simulation/components/spritecomponent.h"
#include "simulation/components/transformcomponent.h"
#include "simulation/components/speedcomponent.h"
#include "media/animationframe.h"

namespace mcomm
{

Game::Game() : state(GameState::PRERUN)
{
	m_renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(800, 600), "mcomm");
	m_renderWindow->setFramerateLimit(60);
	m_renderWindow->setVerticalSyncEnabled(true);
}

std::shared_ptr<sf::RenderWindow> Game::renderWindow() const
{
	return m_renderWindow;
}

void Game::setup()
{
	TextureManager::instance().addTexture("res/sprites1.png", "sprite1");
	std::shared_ptr<void> af = ObjectFactory::instance().create<AnimationFrame>("AnimationFrame");
	auto player = EntityFactory::instance().createNew("Player");
	player->attachComponent("DrawableComponent");
	player->attachComponent("SpriteComponent");
	player->attachComponent("TransformComponent");
	player->attachComponent("SpeedComponent");

	player->COMPONENT(Sprite)->setTextureId("sprite1");

	auto transform = player->COMPONENT(Transform);
	transform->setScaleX(2.0f);
	transform->setScaleY(2.0f);
	transform->setOriginX(16.0f);
	transform->setOriginY(16.0f);
	transform->setPositionX(300.0f);
	transform->setPositionY(200.0f);

	auto speed = player->COMPONENT(Speed);
	speed->setX(60.0f);
	speed->setY(60.0f);

	player->attachSystem("RenderSystem");
	player->attachSystem("VelocitySystem");

	world.addEntity(player);

	world.saveJson("level1.json");
	//world.loadJson("res/start_entities.xml");
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
