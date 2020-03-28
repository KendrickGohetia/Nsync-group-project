#pragma once
#ifndef __BULLET_1__
#define __BULLET_1__
#include "DisplayObject.h"
#include <sstream>
#include "ship.h"

class Bullet1 : public DisplayObject
{
public:
	Bullet1();
	~Bullet1();

	void draw() override;
	void update() override;
	void clean() override;
};

#endif /* define (__BULLET_1__) */