#pragma once
#ifndef __LEVEL2_SCENE__
#define __LEVEL2_SCENE__

#include "Scene.h"
#include "ship.h"
#include "Background1.h"
#include "Bullet1.h"
#include "Enemy2.h"
#include "Label.h"
#include "EnemyBullet1.h"

class Level2Scene : public Scene
{
public:
	Level2Scene();
	~Level2Scene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void spawnEnemies();
	void objectsOutOfBounds();
	void checkCollisions();
	void enemyFire();
	void removeEnemy2Element(Enemy2* element);
	void removeBullet1Element(Bullet1* element);
	void removeEnemyBullet1Element(EnemyBullet1* element);

private:
	glm::vec2 m_mousePosition;

	Background1 m_background1;
	Ship* m_pShip;
	Label* m_pScoreLabel;
	Label* m_pScore;

	std::vector<Enemy2*> m_pEnemy2;
	std::vector<Bullet1*> m_pBullet1;
	std::vector<EnemyBullet1*> m_pEnemyBullet1;

	std::vector<Enemy2*>::iterator itrx;
	std::vector<Enemy2*>::reverse_iterator ritr;

	std::vector<Bullet1*>::iterator bulletItrx;
	std::vector<Bullet1*>::reverse_iterator bulletRitr;

	std::vector<EnemyBullet1*>::iterator eBulletItrx;
	std::vector<EnemyBullet1*>::reverse_iterator eBulletRitr;

	int rand1, rand2, enemyNum, bulletNum, eBulletNum;
	float enemyDist, enemyProximity;
	bool isFired, enemySpawned, stopSpawning;

	int hitScore = 20;

	const SDL_Color blue = { 0, 0, 255, 255 };

};

#endif /* defined (__LEVEL2_SCENE__) */