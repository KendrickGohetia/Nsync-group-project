#pragma once
#ifndef __ENEMY_2__
#define __ENEMY_2__
#include "DisplayObject.h"
#include <sstream>
#include "ship.h"

class Enemy2 : public DisplayObject
{
public:
	Enemy2();
	~Enemy2();

	void draw() override;
	void update() override;
	void clean() override;
	void enemyFire();
	void setIsKilled(bool isDead);
	void setEnemyFire(bool isFire);

	bool getIsKilled();
	bool getEnemyFire();
	/*bool enemyStopFiring();*/

private:

	int hits, hasFired, rand1;
	bool isKilled, isEnemyFire;
};

#endif /* define (__ENEMY_2__) */