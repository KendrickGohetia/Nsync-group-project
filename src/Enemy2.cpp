#include "Enemy2.h"
#include "TextureManager.h"
#include "Game.h"

Enemy2::Enemy2()
{
	TheTextureManager::Instance()->load("../Assets/textures/Enemy2.png",
		"enemy2", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("enemy2");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::ENEMY2);
}

Enemy2::~Enemy2()
{
}

void Enemy2::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("enemy2", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void Enemy2::update()
{
	float enemy2Speed = 5.0f;

	setPosition(glm::vec2(getPosition().x, getPosition().y + enemy2Speed));
}

void Enemy2::clean()
{
}
