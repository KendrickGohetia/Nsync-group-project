#include "EnemyBullet1.h"
#include "TextureManager.h"
#include "Game.h"

EnemyBullet1::EnemyBullet1() :bulletSpeed(10.0f)
{
	TheTextureManager::Instance()->load("../Assets/textures/beam2.png",
		"enemyBullet1", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("enemyBullet1");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::ENEMYBULLET1);
}

EnemyBullet1::~EnemyBullet1()
{
}

void EnemyBullet1::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("enemyBullet1", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void EnemyBullet1::update()
{
	moveBullet();
}

void EnemyBullet1::clean()
{
}

void EnemyBullet1::fireBullet()
{
	setVelocity(glm::vec2(getVelocity().x, getVelocity().y + bulletSpeed));
}

void EnemyBullet1::moveBullet()
{
	setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y));
}