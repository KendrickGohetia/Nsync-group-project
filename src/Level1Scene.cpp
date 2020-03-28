#include "Level1Scene.h"
#include "Game.h"
#include <chrono>
#include <thread>

using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.

Level1Scene::Level1Scene()
{
	Level1Scene::start();
}

Level1Scene::~Level1Scene()
= default;

void Level1Scene::draw()
{
	m_background.draw();
	drawDisplayList();
}

void Level1Scene::update()
{
	updateDisplayList();
}

void Level1Scene::clean()
{

	removeAllChildren();
}

void Level1Scene::handleEvents()
{
	auto wheel = 0;
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_KEYDOWN:
			//const auto keyPressed = event.key.keysym.sym;
			//switch (keyPressed)
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				//TheGame::Instance()->changeSceneState(SceneState::PLAY_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			case SDLK_w:
				std::cout << "move forward" << std::endl;
				m_pShip->moveForward();
				break;
			case SDLK_a:
				std::cout << "move left" << std::endl;
				m_pShip->moveLeft();
				break;
			case SDLK_s:
				std::cout << "move back" << std::endl;
				m_pShip->moveBack();
				break;
			case SDLK_d:
				std::cout << "move right" << std::endl;
				m_pShip->moveRight();
				break;
			case SDLK_SPACE:
				std::cout << "fire weapon" << std::endl;
				m_pBullet1 = new Bullet1();
				m_pBullet1->setPosition(m_pShip->getShipPosition().x * 0.94f, m_pShip->getShipPosition().y * 0.90f);
				addChild(m_pBullet1);
				break;
			}
			
			break;

		case SDL_KEYUP:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				m_pShip->setVelocity(glm::vec2(m_pShip->getVelocity().x, 0));

				break;
			case SDLK_s:
				m_pShip->setVelocity(glm::vec2(m_pShip->getVelocity().x, 0));

				break;
			case SDLK_a:
				m_pShip->setVelocity(glm::vec2(0, m_pShip->getVelocity().y));

				break;
			case SDLK_d:
				m_pShip->setVelocity(glm::vec2(0, m_pShip->getVelocity().y));

				break;
			}

			break;
		}

	}
}

void Level1Scene::start()
{
	m_background = Background();

	m_pShip = new Ship();
	m_pShip->setPosition(Config::SCREEN_WIDTH * 0.5, Config::SCREEN_HEIGHT * 0.9);
	addChild(m_pShip);

	/*m_pBullet1 = new Bullet1();
	m_pBullet1->setPosition(m_pShip->getShipPosition().x, m_pShip->getShipPosition().y);
	addChild(m_pBullet1);*/
}
