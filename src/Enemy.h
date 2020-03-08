#pragma once
#ifndef __ENEMY__
#define __ENEMY__
#include "DisplayObject.h"
class Enemy: public DisplayObject
{
	
public:
	Enemy();
	~Enemy();
	// Inherited via GameObject
	void draw();

	void update();

	void clean();
private:
	
	void _movev();
	void _checkbouds();
	float speed = 5.f;
	float cur;

}
;
#endif 