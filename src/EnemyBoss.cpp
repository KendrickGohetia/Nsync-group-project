#include "EnemyBoss.h"
#include "TextureManager.h"
#include "Game.h"

EnemyBoss::EnemyBoss()
{
	TheTextureManager::Instance()->load("../Assets/textures/EnemyBoss.png",
		"enemyBoss", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("enemyBoss");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::ENEMYBOSS);
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("enemyBoss", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void EnemyBoss::update()
{
	bossMove();

	if (getIsColliding())
	{
		hits = hits + 1;

		if (hits == 1)
		{
			setIsKilled(true);
		}

		setIsColliding(false);
	}

	enemyFire();
}

void EnemyBoss::clean()
{
}

void EnemyBoss::enemyFire()
{
	rand1 = rand() % 100 + 1;

	if ((rand1 <= 10) && (heightReached))
	{
		setEnemyFire(true);
		hasFired = hasFired + 1;
	}
}

void EnemyBoss::bossMove()
{
	float enemyBossSpeed = 1.0f;

	if ((getPosition().y < Config::SCREEN_HEIGHT * 0.05f) && (!heightReached))
	{
		setPosition(glm::vec2(getPosition().x, getPosition().y + enemyBossSpeed));

		if (getPosition().y == Config::SCREEN_HEIGHT * 0.05f)
		{
			heightReached = true;
		}
	}

	if ((heightReached) && (!isSwaying))
	{
		setPosition(glm::vec2(getPosition().x + enemyBossSpeed, getPosition().y));
		wasSwayingLeft = false;
		wasSwayingRight = true;
		if (getPosition().x == Config::SCREEN_WIDTH * 0.55f)
		{
			isSwaying = true;
		}
	}

	if ((isSwaying) && (wasSwayingRight))
	{
		setPosition(glm::vec2(getPosition().x - enemyBossSpeed, getPosition().y));
		if (getPosition().x == Config::SCREEN_WIDTH * 0.05f)
		{
			wasSwayingLeft = true;
			wasSwayingRight = false;
		}
	}

	if ((isSwaying) && (wasSwayingLeft))
	{
		setPosition(glm::vec2(getPosition().x + enemyBossSpeed, getPosition().y));
		if (getPosition().x == Config::SCREEN_WIDTH * 0.55f)
		{
			wasSwayingLeft = false;
			wasSwayingRight = true;
		}
	}
}

void EnemyBoss::setIsKilled(bool isDead)
{
	isKilled = isDead;
}

void EnemyBoss::setEnemyFire(bool isFire)
{
	isEnemyFire = isFire;
}

bool EnemyBoss::getIsKilled()
{
	return isKilled;
}

bool EnemyBoss::getEnemyFire()
{
	return isEnemyFire;
}