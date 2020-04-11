#pragma once
#ifndef __GAME_OBJECT_TYPE__
#define __GAME_OBJECT_TYPE__
enum GameObjectType {
	NONE = -1,
	SHIP,
	BACKGROUND,
	BULLET1,
	ENEMYBULLET1,
	ENEMY1,
	ENEMY2,
	TARGET,
	OBSTACLE,
	PLANET,
	PLAYER,
	MINE,
	TILE,
	NUM_OF_TYPES
};
#endif /* defined (__GAME_OBJECT_TYPE__) */