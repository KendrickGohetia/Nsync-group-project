#include "Level3Scene.h"
#include "Game.h"

Level3Scene::Level3Scene()
{
	Level3Scene::start();
}

Level3Scene::~Level3Scene()
= default;

void Level3Scene::draw()
{
	m_background.draw();
	drawDisplayList();
}

void Level3Scene::update()
{
	updateDisplayList();

	objectsOutOfBounds();

	enemyFire();

	checkCollisions();

	spawnEnemies();
}

void Level3Scene::clean()
{

	removeAllChildren();
}

void Level3Scene::handleEvents()
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

void Level3Scene::spawnEnemies()
{
	rand1 = rand() % 100 + 1;
	rand2 = rand() % 550 + 1;

	if ((rand1 < 8) && (rand2 >= 50) && (m_pEnemy2.size() < 20))
	{
		enemyProximity = enemyProximity + 50;
		enemyDist = enemyDist + 200;

		m_pEnemy2.push_back(new Enemy2());
		m_pEnemy2[enemyNum]->setPosition(rand2, 0 - enemyDist);
		addChild(m_pEnemy2[enemyNum]);
		enemyNum = enemyNum + 1;
	}
}

void Level3Scene::objectsOutOfBounds()
{
	for (itrx = m_pEnemy2.begin(); itrx != m_pEnemy2.end(); itrx++)
	{
		if ((*itrx)->getPosition().y > Config::SCREEN_HEIGHT * 1.05f)
		{
			removeChild((*itrx));
			removeEnemy2Element((*itrx));
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

	for (eBulletItrx = m_pEnemyBullet1.begin(); eBulletItrx != m_pEnemyBullet1.end(); eBulletItrx++)
	{
		if ((*eBulletItrx)->getPosition().y > Config::SCREEN_HEIGHT)
		{
			removeChild((*eBulletItrx));
			removeEnemyBullet1Element((*eBulletItrx));
			return;
		}
	}

	for (bBulletItrx = m_pBossBullet.begin(); bBulletItrx != m_pBossBullet.end(); bBulletItrx++)
	{
		if ((*bBulletItrx)->getPosition().y > Config::SCREEN_HEIGHT)
		{
			removeChild((*bBulletItrx));
			removeBossBulletElement((*bBulletItrx));
			return;
		}
	}
}

void Level3Scene::checkCollisions()
{
	if ((m_pBullet1.size() > 0) && (m_pEnemy2.size() > 0))
	{
		for (int x = 0; x < m_pBullet1.size(); x++)
		{
			for (int y = 0; y < m_pEnemy2.size(); y++)
			{
				m_pBullet1[x]->setIsColliding(CollisionManager::AABBCheck(m_pBullet1[x], m_pEnemy2[y]));

				if (m_pBullet1[x]->getIsColliding())
				{
					m_pEnemy2[y]->setIsColliding(true);
					removeChild((m_pBullet1[x]));
					removeBullet1Element((m_pBullet1[x]));

					if (m_pEnemy2[y]->getIsKilled())
					{
						removeChild((m_pEnemy2[y]));
						removeEnemy2Element((m_pEnemy2[y]));
					}
					return;
				}
			}
		}
	}

	if (m_pBullet1.size() > 0)
	{
		for (int x = 0; x < m_pBullet1.size(); x++)
		{
			m_pBullet1[x]->setIsColliding(CollisionManager::AABBCheck(m_pBullet1[x], m_pEnemyBoss));

			if ((m_pBullet1[x]->getIsColliding()) && (m_pEnemyBoss->getPosition().y == Config::SCREEN_HEIGHT * 0.05f))
			{
				m_pEnemyBoss->setIsColliding(true);
				removeChild((m_pBullet1[x]));
				removeBullet1Element((m_pBullet1[x]));
				hitScore = hitScore - 1;
				removeChild(m_pScore);
				const SDL_Color black = { 0, 0, 0, 255 };
				m_pScore = new Label(std::to_string(hitScore), "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.31f, Config::SCREEN_HEIGHT * 0.04f));
				m_pScore->setParent(this);
				addChild(m_pScore);

				if (m_pEnemyBoss->getIsKilled())
				{
					TheGame::Instance()->changeSceneState(SceneState::GAME_OVER_SCENE);
				}
			
				return;
			}
		
		}
	}

	if ((m_pBullet1.size() > 0) && (m_pEnemyBullet1.size() > 0))
	{
		for (int x = 0; x < m_pBullet1.size(); x++)
		{
			for (int y = 0; y < m_pEnemyBullet1.size(); y++)
			{
				m_pBullet1[x]->setIsColliding(CollisionManager::AABBCheck(m_pBullet1[x], m_pEnemyBullet1[y]));

				if (m_pBullet1[x]->getIsColliding())
				{
					removeChild((m_pBullet1[x]));
					removeBullet1Element((m_pBullet1[x]));
					removeChild((m_pEnemyBullet1[y]));
					removeEnemyBullet1Element((m_pEnemyBullet1[y]));
					return;
				}
			}
		}
	}

	if ((m_pBullet1.size() > 0) && (m_pBossBullet.size() > 0))
	{
		for (int x = 0; x < m_pBullet1.size(); x++)
		{
			for (int y = 0; y < m_pBossBullet.size(); y++)
			{
				m_pBullet1[x]->setIsColliding(CollisionManager::AABBCheck(m_pBullet1[x], m_pBossBullet[y]));

				if (m_pBullet1[x]->getIsColliding())
				{
					removeChild((m_pBullet1[x]));
					removeBullet1Element((m_pBullet1[x]));
					removeChild((m_pBossBullet[y]));
					removeBossBulletElement((m_pBossBullet[y]));
					return;
				}
			}
		}
	}

	if (m_pEnemy2.size() > 0)
	{
		for (int x = 0; x < m_pEnemy2.size(); x++)
		{
			if (!m_pShip->getIsColliding())
			{
				m_pShip->setIsColliding(CollisionManager::AABBCheck(m_pShip, m_pEnemy2[x]));
			}
		}

		for (int x = 0; x < m_pEnemyBullet1.size(); x++)
		{
			if (!m_pShip->getIsColliding())
			{
				m_pShip->setIsColliding(CollisionManager::AABBCheck(m_pShip, m_pEnemyBullet1[x]));
			}
		}
	}

	for (int x = 0; x < m_pBossBullet.size(); x++)
	{
		if (!m_pShip->getIsColliding())
		{
			m_pShip->setIsColliding(CollisionManager::AABBCheck(m_pShip, m_pBossBullet[x]));
		}
	}

	if (!m_pShip->getIsColliding())
	{
		m_pShip->setIsColliding(CollisionManager::AABBCheck(m_pShip, m_pEnemyBoss));
	}

	if (m_pShip->getIsColliding())
	{
		TheGame::Instance()->changeSceneState(SceneState::LOSE_SCENE);
	}
}

void Level3Scene::removeEnemy2Element(Enemy2* element)
{
	for (ritr = m_pEnemy2.rbegin(); ritr < m_pEnemy2.rend(); ritr++)
	{
		if (*ritr == element)
		{
			m_pEnemy2.erase((ritr + 1).base());
			enemyNum = enemyNum - 1;
			return;
		}
	}
}

void Level3Scene::removeBullet1Element(Bullet1* element)
{
	for (bulletRitr = m_pBullet1.rbegin(); bulletRitr < m_pBullet1.rend(); bulletRitr++)
	{
		if (*bulletRitr == element)
		{
			m_pBullet1.erase((bulletRitr + 1).base());
			bulletNum = bulletNum - 1;
			return;
		}
	}
}

void Level3Scene::removeEnemyBullet1Element(EnemyBullet1* element)
{
	for (eBulletRitr = m_pEnemyBullet1.rbegin(); eBulletRitr < m_pEnemyBullet1.rend(); eBulletRitr++)
	{
		if (*eBulletRitr == element)
		{
			m_pEnemyBullet1.erase((eBulletRitr + 1).base());
			eBulletNum = eBulletNum - 1;
			return;
		}
	}
}

void Level3Scene::removeBossBulletElement(BossBullet* element)
{
	for (bBulletRitr = m_pBossBullet.rbegin(); bBulletRitr < m_pBossBullet.rend(); bBulletRitr++)
	{
		if (*bBulletRitr == element)
		{
			m_pBossBullet.erase((bBulletRitr + 1).base());
			bBulletNum = bBulletNum - 1;
			return;
		}
	}
}

void Level3Scene::enemyFire()
{
	if (m_pEnemy2.size() > 0)
	{
		for (int x = 0; x < m_pEnemy2.size(); x++)
		{
			if ((m_pEnemy2[x]->getPosition().y > Config::SCREEN_HEIGHT * 0.05f))
			{
				if (m_pEnemy2[x]->getEnemyFire())
				{
					m_pEnemyBullet1.push_back(new EnemyBullet1());
					m_pEnemyBullet1[eBulletNum]->setPosition(m_pEnemy2[x]->getPosition().x + 15.0f, m_pEnemy2[x]->getPosition().y + 55.0f);
					addChild(m_pEnemyBullet1[eBulletNum]);
					m_pEnemyBullet1[eBulletNum]->fireBullet();
					eBulletNum = eBulletNum + 1;
					m_pEnemy2[x]->setEnemyFire(false);
				}
			}
		}
	}

	if (m_pEnemyBoss->getEnemyFire())
	{
		m_pBossBullet.push_back(new BossBullet());
		m_pBossBullet[bBulletNum]->setPosition(m_pEnemyBoss->getPosition().x + 110.0f, m_pEnemyBoss->getPosition().y + 150.0f);
		addChild(m_pBossBullet[bBulletNum]);
		m_pBossBullet[bBulletNum]->fireBullet();
		bBulletNum = bBulletNum + 1;
		m_pEnemyBoss->setEnemyFire(false);
	}
}


void Level3Scene::start()
{
	const SDL_Color red = { 255, 0, 0, 255 };
	const SDL_Color green = { 0, 255, 0, 255 };
	const SDL_Color black = { 0, 0, 0, 255 };

	m_background = Background();

	m_pShip = new Ship();
	m_pShip->setPosition(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.90f);
	addChild(m_pShip);

	m_pScoreLabel = new Label("BOSS HITS LEFT:", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.15f, Config::SCREEN_HEIGHT * 0.04f));
	m_pScoreLabel->setParent(this);
	addChild(m_pScoreLabel);

	m_pScore = new Label(std::to_string(hitScore), "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.31f, Config::SCREEN_HEIGHT * 0.04f));
	m_pScore->setParent(this);
	addChild(m_pScore);

	m_pEnemyBoss = new EnemyBoss();
	m_pEnemyBoss->setPosition(Config::SCREEN_WIDTH * 0.3f, 0 - 300);
	addChild(m_pEnemyBoss);
}
