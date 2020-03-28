#pragma once
#ifndef __SHIP__
#define __SHIP__

#include "PathFindingDisplayObject.h"
#include "TextureManager.h"

class Ship final : public PathFindingDisplayObject
{
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	glm::vec2 getShipPosition();
	void moveForward();
	void moveBack();
	void moveLeft();
	void moveRight();
	
	void move();

private:
	void m_checkBounds();
	void m_reset();

	// steering behaviours
	float m_maxSpeed;
	float m_turnRate;

	float m_playerMoveSpeed;
	float m_currX;
	float m_currY;

	void m_changeDirection();
	float m_currentHeading;
	glm::vec2 m_currentDirection;
};


#endif /* defined (__SHIP__) */

