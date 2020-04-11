#include "BossBullet.h"
#include "TextureManager.h"
#include "Game.h"

BossBullet::BossBullet() :bulletSpeed(10.0f)
{
	TheTextureManager::Instance()->load("../Assets/textures/beam3.png",
		"bossBullet", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("bossBullet");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::BOSSBULLET);
}

BossBullet::~BossBullet()
{
}

void BossBullet::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("bossBullet", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void BossBullet::update()
{
	moveBullet();
}

void BossBullet::clean()
{
}

void BossBullet::fireBullet()
{
	setVelocity(glm::vec2(getVelocity().x, getVelocity().y + bulletSpeed));
}

void BossBullet::moveBullet()
{
	setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y));
}