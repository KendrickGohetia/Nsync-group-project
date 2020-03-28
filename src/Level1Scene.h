#pragma once
#ifndef __LEVEL1_SCENE__
#define __LEVEL1_SCENE__

#include "Scene.h"
#include "ship.h"
#include "Background.h"

class Level1Scene : public Scene
{
public:
	Level1Scene();
	~Level1Scene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
private:
	glm::vec2 m_mousePosition;

	Background m_background;
	Ship* m_pShip;
};

#endif /* defined (__LEVEL1_SCENE__) */