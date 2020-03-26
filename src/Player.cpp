#include "Player.h"
#include "Game.h"



Player::Player()
{
	TheTextureManager::Instance()->load("../Assets/textures/plane.png", "player", TheGame::Instance()->getRenderer());


	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("player");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(540.f, 360.f));
	setIsColliding(false);
	setType(GameObjectType::PLAYER);


}

Player::~Player()
{
}

void Player::draw()
{
	TheTextureManager::Instance()->draw("player", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true);
}

void Player::update()
{

	char current = TheGame::Instance()->getPlayerPosition();
	float speed = 5.f;

	if (current == 'w') {
		cury = getPosition().y - speed;
	}
	if (current == 's') {
		cury = getPosition().y + speed;
	}
	if (current == 'a') {
		curx = getPosition().x - speed;
	}
	if (current == 'd') {
		curx = getPosition().x + speed;
	}
	if (current == '-') {
		curx = getPosition().x;
		cury = getPosition().y;
	}


	setPosition(glm::vec2(curx, cury));


}

void Player::clean()
{
}
