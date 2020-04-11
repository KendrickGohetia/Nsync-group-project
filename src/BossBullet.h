#pragma once
#ifndef __BOSS_BULLET__
#define __BOSS_BULLET__
#include "DisplayObject.h"
#include <sstream>

class BossBullet : public DisplayObject
{
public:
	BossBullet();
	~BossBullet();

	void draw() override;
	void update() override;
	void clean() override;

	void fireBullet();
	void moveBullet();

private:
	float bulletSpeed;
};

#endif /* define (__BOSS_BULLET__) */