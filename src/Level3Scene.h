#pragma once
#ifndef __LEVEL3_SCENE__
#define __LEVEL3_SCENE__

#include "Scene.h"
#include "ship.h"
#include "Background.h"
#include "Bullet1.h"
#include "Enemy2.h"
#include "Label.h"
#include "EnemyBullet1.h"
#include "EnemyBoss.h"
#include "BossBullet.h"

class Level3Scene : public Scene
{
public:
	Level3Scene();
	~Level3Scene();

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
	void removeBossBulletElement(BossBullet* element);

private:
	glm::vec2 m_mousePosition;

	Background m_background;
	Ship* m_pShip;
	Label* m_pScoreLabel;
	Label* m_pScore;
	EnemyBoss* m_pEnemyBoss;

	std::vector<Enemy2*> m_pEnemy2;
	std::vector<Bullet1*> m_pBullet1;
	std::vector<EnemyBullet1*> m_pEnemyBullet1;
	std::vector<BossBullet*> m_pBossBullet;

	std::vector<Enemy2*>::iterator itrx;
	std::vector<Enemy2*>::reverse_iterator ritr;

	std::vector<Bullet1*>::iterator bulletItrx;
	std::vector<Bullet1*>::reverse_iterator bulletRitr;

	std::vector<EnemyBullet1*>::iterator eBulletItrx;
	std::vector<EnemyBullet1*>::reverse_iterator eBulletRitr;

	std::vector<BossBullet*>::iterator bBulletItrx;
	std::vector<BossBullet*>::reverse_iterator bBulletRitr;

	int rand1, rand2, enemyNum, bulletNum, eBulletNum, bBulletNum;
	float enemyDist, enemyProximity;
	bool isFired, enemySpawned, stopSpawning;

	int hitScore = 40;

	const SDL_Color blue = { 0, 0, 255, 255 };

};

#endif /* defined (__LEVEL3_SCENE__) */