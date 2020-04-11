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
};

#endif /* define (__ENEMY_2__) */