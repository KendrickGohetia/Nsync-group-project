#pragma once
#ifndef __BACKGROUND1__
#define __BACKGROUND1__
#include "DisplayObject.h"
#include <sstream>

class Background1 : public DisplayObject
{
public:
	Background1();
	~Background1();

	void draw() override;
	void update() override;
	void clean() override;
};

#endif /* define (__BACKGROUND1__) */