#include "CollisionManager.h"



int CollisionManager::squaredDistance(glm::vec2 P1, glm::vec2 P2)
{
	int diffOfXs = P2.x - P1.x;
	int diffOfYs = P2.y - P1.y;
	int result = diffOfXs * diffOfXs + diffOfYs * diffOfYs;

	return result;
}
bool CollisionManager::AABBCheck(GameObject* object1, GameObject* object2)
{
	// prepare relevant variables
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	float P1width = object1->getWidth();
	float P1height = object1->getHeight();
	float P2width = object2->getWidth();
	float P2height = object2->getHeight();

	if (
		P1.x < P2.x + P2width &&
		P1.x + P1width > P2.x&&
		P1.y < P2.y + P2height &&
		P1.y + P1height > P2.y
		)
	{
		if (!object2->getIsColliding()) {

			object2->setIsColliding(true);

			switch (object2->getType()) {
			case ENEMY:
				std::cout << "Collision with ENEMY!" << std::endl;
				TheSoundManager::Instance()->playSound("thunder", 0);
				break;
			case KEY:
				std::cout << "Collision with Key!" << std::endl;
				TheSoundManager::Instance()->playSound("yay", 0);
				break;
			default:
				//std::cout << "Collision with unknown type!" << std::endl;
				break;
			}

			return true;
		}
		return false;
	}
	else
	{
		object2->setIsColliding(false);
		return false;
	}

	return false;
}

bool CollisionManager::squaredRadiusCheck(GameObject * object1, GameObject * object2)
{
	glm::vec2 P1 = object1->getPosition();
	glm::vec2 P2 = object2->getPosition();
	int halfHeights = (object1->getHeight() + object2->getHeight()) * 0.5;

	//if (glm::distance(P1, P2) < halfHeights) {

	if (CollisionManager::squaredDistance(P1, P2) < (halfHeights * halfHeights)) {
		if (!object2->getIsColliding()) {
			
			object2->setIsColliding(true);

			switch (object2->getType()) {
			
			case ENEMY:
				std::cout << "Collision with Enemy" << std::endl;
				TheSoundManager::Instance()->playSound("thunder", 0);
				break;
			case KEY:
				std::cout << "Collision with Key!" << std::endl;
				TheSoundManager::Instance()->playSound("yay", 0);
				break;
			default:
				std::cout << "Collision with unknown type!" << std::endl;
					break;
			}

			return true;
		}
		return false;
	}

	
}

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}
