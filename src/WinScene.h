#pragma once
#ifndef __WIN_SCENE__
#define __WIN_SCENE__

#include "Scene.h"
#include "Label.h"

class WinScene final : public Scene
{
public:
	WinScene();
	~WinScene();

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

#endif /* defined (__WIN_SCENE__) */