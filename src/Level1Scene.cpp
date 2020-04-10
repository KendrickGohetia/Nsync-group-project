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

	objectsOutOfBounds();

	checkCollisions();

	spawnEnemies();
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

	if ((rand1 < 8) && (rand2 >= 50) && (m_pEnemy1.size() < 20))
	{
		enemyProximity = enemyProximity + 50;
		enemyDist = enemyDist + 200;

		m_pEnemy1.push_back(new Enemy1());
		m_pEnemy1[enemyNum]->setPosition(rand2, 0 - enemyDist);
		addChild(m_pEnemy1[enemyNum]);
		enemyNum = enemyNum + 1;
	}
}

void Level1Scene::objectsOutOfBounds()
{
	for (itrx = m_pEnemy1.begin(); itrx != m_pEnemy1.end(); itrx++)
	{
		if ((*itrx)->getPosition().y > Config::SCREEN_HEIGHT * 1.05f)
		{
			removeChild((*itrx));
			removeEnemy1Element((*itrx));
			return;
		}
	}	

	for (bulletItrx = m_pBullet1.begin(); bulletItrx != m_pBullet1.end(); bulletItrx++)
	{
		if ((*bulletItrx)->getPosition().y < 0)
		{
			removeChild((*bulletItrx));
			removeBullet1Element((*bulletItrx));
			return;
		}
	}
}

//void Level1Scene::respawn()
//{
//	enemyNum = 0;
//	enemyProximity = 0;
//	enemyDist = 0;
//	stopSpawning = false;
//}

void Level1Scene::checkCollisions()
{
	if (m_pEnemy1.size() > 0)
	{
		for (int x = 0; x < m_pEnemy1.size(); x++)
		{
			m_pShip->setIsColliding(CollisionManager::AABBCheck(m_pShip, m_pEnemy1[x]));

			if (m_pShip->getIsColliding())
			{
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
			}
		}
	}
}

void Level1Scene::removeEnemy1Element(Enemy1* element)
{
	for (ritr = m_pEnemy1.rbegin(); ritr < m_pEnemy1.rend(); ritr++)
	{
		if (*ritr == element)
		{
			/*std::cout << "Enemy list before erase:";
			for (itrx = m_pEnemy1.begin(); itrx != m_pEnemy1.end(); itrx++)  
			{
				std::cout << ' ' << *itrx;
				std::cout << '\n';
			}*/

			m_pEnemy1.erase((ritr + 1).base());
			enemyNum = enemyNum - 1;

			/*std::cout << "Enemy list after erase:";
			for (itrx = m_pEnemy1.begin(); itrx != m_pEnemy1.end(); itrx++)  
			{
				std::cout << ' ' << *itrx;
				std::cout << '\n';
				std::cout << "Size: " << m_pEnemy1.size();
			}*/

			return;
		}
	}
}

void Level1Scene::removeBullet1Element(Bullet1* element)
{
	for (bulletRitr = m_pBullet1.rbegin(); bulletRitr < m_pBullet1.rend(); bulletRitr++)
	{
		if (*bulletRitr == element)
		{
			/*std::cout << "Bullet1 list before erase:";
			std::cout << '\n';
			for (bulletItrx = m_pBullet1.begin(); bulletItrx != m_pBullet1.end(); bulletItrx++)
			{
				std::cout << ' ' << *bulletItrx;
				std::cout << '\n';
			}*/

			m_pBullet1.erase((bulletRitr + 1).base());
			bulletNum = bulletNum - 1;

			/*std::cout << "Bullet1 list after erase:";
			std::cout << '\n';
			for (bulletItrx = m_pBullet1.begin(); bulletItrx != m_pBullet1.end(); bulletItrx++)
			{
				std::cout << ' ' << *bulletItrx;
				std::cout << '\n';
			}

			std::cout << "Size: " << m_pBullet1.size();
			std::cout << '\n';*/
			return;
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
