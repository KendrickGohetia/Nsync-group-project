#include "ship.h"
#include "Game.h"
#include "Util.h"
#include "PlayScene.h"
#include "glm/gtx/string_cast.hpp"


Ship::Ship() : m_maxSpeed(8.0f)
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
}

void Ship::clean()
{
}


void Ship::moveForward()
{
	setVelocity(glm::vec2(getVelocity().x, getVelocity().y - m_maxSpeed));
}

void Ship::moveBack()
{
	setVelocity(glm::vec2(getVelocity().x, getVelocity().y + m_maxSpeed));
}

void Ship::moveLeft()
{
	setVelocity(glm::vec2(getVelocity().x - m_maxSpeed, getVelocity().y));
}

void Ship::moveRight()
{
	setVelocity(glm::vec2(getVelocity().x + m_maxSpeed, getVelocity().y));
}

void Ship::move()
{
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

	if (getVelocity().y < 0.0f && getPosition().y - getVelocity().y > m_maxSpeed)
	{
		setVelocity(glm::vec2(getVelocity().x, -m_maxSpeed));
	}

	if (((getPosition().x + getVelocity().x) > Config::SCREEN_WIDTH * 0.95f) || ((getPosition().x + getVelocity().x) < Config::SCREEN_WIDTH * 0.05))
	{
		setVelocity(glm::vec2(0.0f, getVelocity().y));
	}

	if (((getPosition().y + getVelocity().y) > Config::SCREEN_HEIGHT * 0.95f) || ((getPosition().y + getVelocity().y) < Config::SCREEN_HEIGHT * 0.05f))
	{
		setVelocity(glm::vec2(getVelocity().x, 0.0f));
	}

	setPosition(glm::vec2(getPosition().x + getVelocity().x, getPosition().y + getVelocity().y));

	std::cout << "getPositionY: " << getPosition().y << std::endl;

	std::cout << "Velocity: " << getVelocity().y << std::endl;

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

