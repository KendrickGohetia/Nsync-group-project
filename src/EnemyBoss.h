#pragma once
#ifndef __ENEMY_BOSS__
#define __ENEMY_BOSS__
#include "DisplayObject.h"
#include <sstream>
#include "ship.h"

class EnemyBoss : public DisplayObject
{
public:
	EnemyBoss();
	~EnemyBoss();

	void draw() override;
	void update() override;
	void clean() override;
	void enemyFire();
	void setIsKilled(bool isDead);
	void setEnemyFire(bool isFire);
	void bossMove();

	bool getIsKilled();
	bool getEnemyFire();

private:

	int hits, hasFired, rand1;
	bool isKilled, isEnemyFire, isSwaying, wasSwayingRight, wasSwayingLeft, heightReached;
};

#endif /* define (__ENEMY_BOSS__) */