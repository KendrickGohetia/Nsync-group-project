#pragma once
#ifndef __Key__
#define __Key__
#include "DisplayObject.h"
class Key : public GameObject
{

public:
	Key();
	~Key();
	// Inherited via GameObject
	void draw();

	void update();

	void clean();
private:

}
;
#endif 