#include "Enemy.h"
#include "Game.h"

Enemy::Enemy() {
	TheTextureManager::Instance()->load("../Assets/textures/flash.png", "enemyv", TheGame::Instance()->getRenderer());
	glm::vec2 sizev = TheTextureManager::Instance()->getTextureSize("enemyv");
	setWidth(32.f);
	setHeight(32.f);
	setPosition(glm::vec2(100.f, 100.f));
	setIsColliding(false);
	setType(GameObjectType::ENEMY);
	TheSoundManager::Instance()->load("../Assets/audio/thunder.ogg",
		"thunder", sound_type::SOUND_SFX);
	
}
Enemy::~Enemy(){
}
void Enemy::draw() {

	TheTextureManager::Instance()->draw("enemyv", 108, getPosition().y, TheGame::Instance()->getRenderer(), true);
	TheTextureManager::Instance()->draw("enemyv", 324, getPosition().y, TheGame::Instance()->getRenderer(), true);
	TheTextureManager::Instance()->draw("enemyv", 540, getPosition().y, TheGame::Instance()->getRenderer(), true);
	TheTextureManager::Instance()->draw("enemyv", 756, getPosition().y, TheGame::Instance()->getRenderer(), true);
	TheTextureManager::Instance()->draw("enemyv", 972, getPosition().y, TheGame::Instance()->getRenderer(), true);

}
void Enemy::update()
{
	_movev();
}
void Enemy::clean()
{

}

void Enemy::_movev()
{
	
	_checkbouds();
	cur = getPosition().y + speed;

	setPosition(glm::vec2(100.f, cur));
	
}

void Enemy::_checkbouds()
{
	if (getPosition().y == 720.f || cur == 0) {
		speed*=-1;
	}
	else {
		speed *=1;
	}

}
