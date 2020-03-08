#include "Key.h"
#include "Game.h"

Key::Key() {
	TheTextureManager::Instance()->load("../Assets/textures/key.png", "Key", TheGame::Instance()->getRenderer());
	glm::vec2 sizev = TheTextureManager::Instance()->getTextureSize("Key");
	setWidth(32.f);
	setHeight(32.f);
	setPosition(glm::vec2(25.f, 360.f));
	setIsColliding(false);
	setType(GameObjectType::KEY);
	TheSoundManager::Instance()->load("../Assets/audio/yay.ogg",
		"yay", sound_type::SOUND_SFX);

}
Key::~Key() {
}
void Key::draw() {
	TheTextureManager::Instance()->draw("Key", getPosition().x, getPosition().y, TheGame::Instance()->getRenderer(), true);
}
void Key::update()
{
	
}
void Key::clean()
{

}

