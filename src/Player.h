#pragma once
#ifndef __Player__
#define __Player__

#include "GameObject.h"
#include "TextureManager.h"
#include "SoundManager.h"

//class Player : public GameObject {
class Player final : public GameObject {
public:
	Player();
	~Player();

	// Draw the object
	void draw();

	// Update the object
	void update();

	// remove anything that needs to be deleted
	void clean();
private:
	char currKey;
	float curx = 560.f;
	float cury = 360.f;
};


#endif /* defined (__Player__) */