#include "Bullet1.h"
#include "TextureManager.h"
#include "Game.h"

Bullet1::Bullet1()
{
	TheTextureManager::Instance()->load("../Assets/textures/laserBullet.png",
		"bullet1", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("bullet1");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::BULLET1);
}

Bullet1::~Bullet1()
{
}

void Bullet1::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("bullet1", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void Bullet1::update()
{
	float bulletSpeed = 10.0f;

	setPosition(glm::vec2(getPosition().x, getPosition().y - bulletSpeed));
}

void Bullet1::clean()
{
}
