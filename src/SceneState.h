#pragma once
#ifndef __SCENE_STATE__
#define __SCENE_STATE__
enum SceneState
{
	NO_SCENE = -1,
	START_SCENE,
	INSTRUCTION_SCENE,
	GAME_OVER_SCENE,
	WIN_SCENE,
	LOSE_SCENE,
	LEVEL1_SCENE,
	LEVEL2_SCENE,
	LEVEL3_SCENE,
	PLAY_SCENE,
	END_SCENE,
	NUM_OF_SCENES
};
#endif /* defined (__SCENE_STATE__) */