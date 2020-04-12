#pragma once
#ifndef __INSTRUCTION_SCENE__
#define __INSTRUCTION_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Background1.h"
#include "SceneState.h"

class InstructionScene final : public Scene
{
public:
	InstructionScene();
	~InstructionScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Label* m_pLabel1{};
	Label* m_pLabel2{};
	Label* m_pLabel3{};
	Label* m_pLabel4{};
	Label* m_pLabel5{};
	Label* m_pLabel6{};
	Label* m_pLabel7{};
	Label* m_pLabel8{};
	Label* m_pLabel9{};
	Label* m_pLabel10{};
	Label* m_pLabel11{};
	Label* m_pLabel12{};
	Background1 m_pBackground1;
	SceneState m_prevSceneState;

};

#endif /* defined (__INSTRUCTION_SCENE__) */