#include "Background1.h"
#include "TextureManager.h"
#include "Game.h"

Background1::Background1()
{
	TheTextureManager::Instance()->load("../Assets/textures/ocean.gif",
		"background1", TheGame::Instance()->getRenderer());

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("background1");
	setWidth(size.x);
	setHeight(size.y);

	setPosition(glm::vec2(0, 0));
	setIsColliding(false);
	setType(GameObjectType::BACKGROUND1);
}

Background1::~Background1()
{
}

void Background1::draw()
{
	int xComponent = getPosition().x;
	int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("background1", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), 0, 255, false);
}

void Background1::update()
{
}

void Background1::clean()
{
}
