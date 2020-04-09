#pragma once
#ifndef __ENEMY_1__
#define __ENEMY_1__
#include "DisplayObject.h"
#include <sstream>
#include "ship.h"

class Enemy1 : public DisplayObject
{
public:
	Enemy1();
	~Enemy1();

	void draw() override;
	void update() override;
	void clean() override;
};

#endif /* define (__ENEMY_1__) */