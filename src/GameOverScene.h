#pragma once
#ifndef __GAME_OVER_SCENE__
#define __GAME_OVER_SCENE__

#include "Scene.h"
#include "Label.h"

class GameOverScene final : public Scene
{
public:
	GameOverScene();
	~GameOverScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};
	Label* m_pInstructionsLabel2{};

};

#endif /* defined (__GAME_OVER_SCENE__) */