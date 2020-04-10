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

	/*for (Bullet1* bullet : m_pBullet1)
	{
		bullet->draw();
	}*/
}

void Level1Scene::update()
{
	updateDisplayList();
	
	childrenNum = numberOfChildren();

	objectsOutOfBounds();

	checkCollisions();

	if (!stopSpawning)
	{
		spawnEnemies();
	}
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
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				TheGame::Instance()->changeSceneState(SceneState::START_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			case SDLK_w:
				m_pShip->moveForward();
				break;
			case SDLK_a:
				m_pShip->moveLeft();
				break;
			case SDLK_s:
				m_pShip->moveBack();
				break;
			case SDLK_d:
				m_pShip->moveRight();
				break;
			case SDLK_SPACE:
				if (!isFired)
				{
					m_pBullet1.push_back(new Bullet1());
					m_pBullet1[bulletNum]->setPosition(m_pShip->getPosition().x - 6.5f, m_pShip->getPosition().y - 55.0f);
					addChild(m_pBullet1[bulletNum]);
					m_pBullet1[bulletNum]->fireBullet();
					bulletNum = bulletNum + 1;

					/*m_pBullet1 = new Bullet1();
					m_pBullet1->setPosition(m_pShip->getPosition().x - 6.5f, m_pShip->getPosition().y - 55.0f);
					addChild(m_pBullet1);
					m_pBullet1->fireBullet();*/

					isFired = true;
				}
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
			case SDLK_SPACE:
				if (isFired)
				{
					isFired = false;
				}
				break;
			}

			break;
		}

	}
}

void Level1Scene::spawnEnemies()
{
	rand1 = rand() % 100 + 1;
	rand2 = rand() % 550 + 1;

	if ((rand1 < 8) && (rand2 >= 50) && (enemyNum < 20))
	{
		enemyProximity = enemyProximity + 50;
		enemyDist = enemyDist + 200;

		m_pEnemy1.push_back(new Enemy1());
		m_pEnemy1[enemyNum]->setPosition(rand2, 0 - enemyDist);
		//m_pEnemy1[enemyNum]->setPosition(Config::SCREEN_WIDTH * 0.5f, 0 - enemyDist);     //For testing collisions
		addChild(m_pEnemy1[enemyNum]);
		enemyNum = enemyNum + 1;
		enemySpawned = true;

		if (enemyNum == 20)
		{
			stopSpawning = true;
		}

		/*std::cout << "rand1: " << rand1 << std::endl;
		std::cout << "rand2: " << rand2 << std::endl;*/
	}
}

void Level1Scene::objectsOutOfBounds()
{
	for (int x = 0; x < enemyNum; x++)
	{
		if (m_pEnemy1[x]->getPosition().y > Config::SCREEN_HEIGHT * 1.05f)
		{
			removeChild(m_pEnemy1[x]);
			if (x == 19)
			{
				respawn();
				enemySpawned = false;
			}
		}
	}
	
}

void Level1Scene::respawn()
{
	enemyNum = 0;
	enemyProximity = 0;
	enemyDist = 0;
	stopSpawning = false;
}

void Level1Scene::checkCollisions()
{
	for (int x = 0; x < enemyNum; x++)
	{
		m_pShip->setIsColliding(CollisionManager::AABBCheck(m_pShip, m_pEnemy1[x]));

		if (m_pShip->getIsColliding())
		{
			//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
		}
	}
}


void Level1Scene::start()
{
	m_background = Background();

	m_pShip = new Ship();
	m_pShip->setPosition(Config::SCREEN_WIDTH * 0.5, Config::SCREEN_HEIGHT * 0.9);
	addChild(m_pShip);
}
