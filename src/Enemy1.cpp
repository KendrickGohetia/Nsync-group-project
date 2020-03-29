#include "Enemy1.h"
#include "TextureManager.h"
#include "Game.h"

Enemy1::Enemy1()
{
	TheTextureManager::Instance()->load("../Assets/textures/Enemy1.png",
		"enemy1", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("enemy1");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::ENEMY1);
}

Enemy1::~Enemy1()
{
}

void Enemy1::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("enemy1", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void Enemy1::update()
{
	float enemy1Speed = 5.0f;

	setPosition(glm::vec2(getPosition().x, getPosition().y + enemy1Speed));
}

void Enemy1::clean()
{
}
