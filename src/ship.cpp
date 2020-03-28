#include "ship.h"
#include "Game.h"
#include "Util.h"
#include "PlayScene.h"
#include "glm/gtx/string_cast.hpp"


Ship::Ship() : m_maxSpeed(5.0f)
{
	TheTextureManager::Instance()->load("../Assets/textures/Player.png",
		"ship", TheGame::Instance()->getRenderer());

	auto size = TheTextureManager::Instance()->getTextureSize("ship");
	setWidth(size.x);
	setHeight(size.y);
	setPosition(glm::vec2(400.0f, 550.0f));
	setVelocity(glm::vec2(0.0f, 0.0f));
	setAcceleration(glm::vec2(0.0f, 0.0f));
	setIsColliding(false);
	setType(SHIP);
	setState(IDLE);
	
	m_currentHeading = 0.0f; // current facing angle
	m_currentDirection = glm::vec2(1.0f, 0.0f); // facing right
	m_turnRate = 5.0f; // 5 degrees per frame
}


Ship::~Ship()
= default;

void Ship::draw()
{
	const int xComponent = getPosition().x;
	const int yComponent = getPosition().y;

	TheTextureManager::Instance()->draw("ship", xComponent, yComponent,
		TheGame::Instance()->getRenderer(), m_currentHeading, 255, true);
}


void Ship::update()
{
	move();
	//m_checkBounds();
}

void Ship::clean()
{
}


void Ship::moveForward()
{
	if ((getPosition().y + getVelocity().y) > Config::SCREEN_HEIGHT * 0.05f)
	{
		/*setPosition(glm::vec2(getPosition().x, getPosition().y - m_maxSpeed));*/
		setVelocity(glm::vec2(getVelocity().x, getVelocity().y - m_maxSpeed));
		/*setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y));*/
	}
}

void Ship::moveBack()
{
	if ((getPosition().y + getVelocity().y) < Config::SCREEN_HEIGHT * 0.95f)
	{
		//setPosition(glm::vec2(getPosition().x, getPosition().y + m_maxSpeed));
		setVelocity(glm::vec2(getVelocity().x, getVelocity().y + m_maxSpeed));
		/*setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y - getVelocity().y));*/
	}
}

void Ship::moveLeft()
{
	if (getPosition().x > Config::SCREEN_WIDTH * 0.05f)
	{
		setPosition(glm::vec2(getPosition().x - m_maxSpeed, getPosition().y));
	}
}

void Ship::moveRight()
{
	if (getPosition().x < Config::SCREEN_WIDTH * 0.95f)
	{
		setPosition(glm::vec2(getPosition().x + m_maxSpeed, getPosition().y));
	}
}

void Ship::move()
{
	//setPosition(getPosition() + getVelocity());
	//setVelocity(getVelocity() * 0.9f);
	if (getVelocity().x > 0.0f && getVelocity().x - getPosition().x < m_maxSpeed)
	{
		setVelocity(glm::vec2(m_maxSpeed, getVelocity().y));
	}

	if (getVelocity().x < 0.0f && getPosition().x - getVelocity().x > m_maxSpeed)
	{
		setVelocity(glm::vec2(-m_maxSpeed, getVelocity().y));
	}

	if (getVelocity().y > 0.0f && getVelocity().y - getPosition().y < m_maxSpeed)
	{
		setVelocity(glm::vec2(getVelocity().x, m_maxSpeed));
	}
	/*else 
	{
		setVelocity(glm::vec2(getVelocity().x, 0.0f));
	}*/

	if (getVelocity().y < 0.0f && getPosition().y - getVelocity().y > m_maxSpeed)
	{
		setVelocity(glm::vec2(getVelocity().x, -m_maxSpeed));
	}
	/*else
	{
		setVelocity(glm::vec2(getVelocity().x, 0.0f));
	}*/

	setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y));

}



void Ship::m_checkBounds()
{

	if (getPosition().x > Config::SCREEN_WIDTH)
	{
		setPosition(glm::vec2(0.0f, getPosition().y));
	}

	if (getPosition().x < 0)
	{
		setPosition(glm::vec2(800.0f, getPosition().y));
	}

	if (getPosition().y > Config::SCREEN_HEIGHT)
	{
		setPosition(glm::vec2(getPosition().x, 0.0f));
	}

	if (getPosition().y < 0)
	{
		setPosition(glm::vec2(getPosition().x, 600.0f));
	}

}

void Ship::m_reset()
{
	setIsColliding(false);
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	setPosition(glm::vec2(xComponent, yComponent));
}

void Ship::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);

	glm::vec2 size = TheTextureManager::Instance()->getTextureSize("ship");
}

glm::vec2 Ship::getShipPosition()
{
	return getPosition();
}

