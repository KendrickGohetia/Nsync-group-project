#pragma once
#ifndef __LEVEL1_SCENE__
#define __LEVEL1_SCENE__

#include "Scene.h"
#include "ship.h"
#include "Background.h"
#include "Bullet1.h"
#include "Enemy1.h"
#include "Label.h"

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
	
	void spawnEnemies();
	void objectsOutOfBounds();
	void checkCollisions();
	void removeEnemy1Element(Enemy1* element);
	void removeBullet1Element(Bullet1* element);
	
private:
	glm::vec2 m_mousePosition;

	Background m_background;
	Ship* m_pShip;
	Label* m_pScoreLabel;
	Label* m_pScore;

	std::vector<Enemy1*> m_pEnemy1;
	std::vector<Bullet1*> m_pBullet1;

	std::vector<Enemy1*>::iterator itrx;
	std::vector<Enemy1*>::reverse_iterator ritr;

	std::vector<Bullet1*>::iterator bulletItrx;
	std::vector<Bullet1*>::reverse_iterator bulletRitr;

	int rand1, rand2, enemyNum, bulletNum, hitScore;
	float enemyDist, enemyProximity;
	bool isFired, enemySpawned, stopSpawning;

	const SDL_Color blue = { 0, 0, 255, 255 };

};

#endif /* defined (__LEVEL1_SCENE__) */