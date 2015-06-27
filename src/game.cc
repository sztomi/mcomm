#include "precompiled.h"

#include "game.h"
#include "media/texturemanager.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "simulation/factories.h"
#include "simulation/components/drawablecomponent.h"
#include "simulation/components/spritecomponent.h"
#include "simulation/components/transformcomponent.h"
#include "simulation/components/speedcomponent.h"
#include "simulation/components/animationframescomponent.h"

namespace Im = ImGui::SFML;

namespace mcomm
{

Game::Game() : state(GameState::PRERUN)
{
    m_renderWindow = std::make_shared<sf::RenderWindow>(sf::VideoMode(1024, 768), "mcomm");
    m_renderWindow->setFramerateLimit(60);
    m_renderWindow->setVerticalSyncEnabled(true);

    Im::SetWindow(*m_renderWindow);
    Im::InitImGui();
}

std::shared_ptr<sf::RenderWindow> Game::renderWindow() const
{
    return m_renderWindow;
}

void Game::setup()
{
    TextureManager::instance().addTexture("res/sprites1.png", "sprite1");

    //auto player = EntityFactory::instance().createNew("Player");
    //player->attachComponent("mcomm::DrawableComponent");
    //player->attachComponent("mcomm::SpriteComponent");
    //player->attachComponent("mcomm::TransformComponent");
    //player->attachComponent("mcomm::SpeedComponent");
    //player->attachComponent("mcomm::AnimationFramesComponent");

    //player->COMPONENT(Sprite)->setTextureId("sprite1");

    //auto transform = player->COMPONENT(Transform);
    //transform->setScaleX(2.0f);
    //transform->setScaleY(2.0f); //transform->setOriginX(16.0f);
    //transform->setOriginY(16.0f);
    //transform->setPositionX(300.0f);
    //transform->setPositionY(200.0f);

    //auto speed = player->COMPONENT(Speed);
    //speed->setX(60.0f);
    //speed->setY(60.0f);

    //auto a = player->COMPONENT(AnimationFrames);
    //a->addFrame({1, 0, 130});
    //a->addFrame({0, 0, 100});
    //a->addFrame({2, 0, 130});

    //player->attachSystem("mcomm::RenderSystem");
    //player->attachSystem("mcomm::VelocitySystem");
    //player->attachSystem("mcomm::SpriteAnimationSystem");
    //player->attachSystem("mcomm::KeyboardInputSystem");

    //world.addEntity(player);

    ////world.loadJson("res/start_entities.xml");
    //world.save("level1_saved.xml");
    world.load("level1_saved.xml");
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
        //Im::ProcessEvent(event);

        switch (event.type)
        {
        case sf::Event::Closed:
            LOG(INFO) << "Closed event received";
            state = GameState::EXITING;
            break;
        case sf::Event::Resized:
            m_renderWindow->setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
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

    while (frameTime > 0.0f)
    {
        float dt = std::min(frameTime, timeStep);
        world.update(dt);
        Im::UpdateImGui();
        drawGui();

        frameTime -= dt;
    }
}

void Game::drawGui()
{
    static bool ui=true;
    if(ImGui::Begin("Test!", &ui, ImVec2(10, 10)))
    {
        ImGui::Text("Hello, world!");
        ImGui::ShowTestWindow();
        //ImGui::ShowUserGuide();
    }
    ImGui::End();
    ImGui::Render();
}

}
