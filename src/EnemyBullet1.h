#pragma once
#ifndef __ENEMY_BULLET_1__
#define __ENEMY_BULLET_1__
#include "DisplayObject.h"
#include <sstream>

class EnemyBullet1 : public DisplayObject
{
public:
	EnemyBullet1();
	~EnemyBullet1();

	void draw() override;
	void update() override;
	void clean() override;

	void fireBullet();
	void moveBullet();

private:
	float bulletSpeed;
};

#endif /* define (__ENEMY_BULLET_1__) */