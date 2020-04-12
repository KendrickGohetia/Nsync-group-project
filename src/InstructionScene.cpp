#include "InstructionScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"

InstructionScene::InstructionScene()
{
	InstructionScene::start();
}

InstructionScene::~InstructionScene()
= default;

void InstructionScene::draw()
{
	drawDisplayList();
}

void InstructionScene::update()
{
	updateDisplayList();
}

void InstructionScene::clean()
{
	std::cout << "Clean called on InstructionScene" << std::endl;

	delete m_pLabel1;
	m_pLabel1 = nullptr;

	delete m_pLabel2;
	m_pLabel2 = nullptr;

	delete m_pLabel3;
	m_pLabel3 = nullptr;

	delete m_pLabel4;
	m_pLabel4 = nullptr;

	delete m_pLabel5;
	m_pLabel5 = nullptr;

	delete m_pLabel6;
	m_pLabel6 = nullptr;

	delete m_pLabel7;
	m_pLabel7 = nullptr;

	delete m_pLabel8;
	m_pLabel8 = nullptr;

	delete m_pLabel9;
	m_pLabel9 = nullptr;

	removeAllChildren();
}

void InstructionScene::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				if (m_prevSceneState == START_SCENE)
				{
					TheGame::Instance()->changeSceneState(SceneState::LEVEL1_SCENE);
				}
				
				if ((m_prevSceneState == LEVEL1_SCENE) && (TheGame::Instance()->getWinState()))
				{
					TheGame::Instance()->changeSceneState(SceneState::LEVEL2_SCENE);
				}
				else if ((m_prevSceneState == LEVEL1_SCENE) && (!TheGame::Instance()->getWinState()))
				{
					TheGame::Instance()->changeSceneState(SceneState::LEVEL1_SCENE);
				}

				if ((m_prevSceneState == LEVEL2_SCENE) && (TheGame::Instance()->getWinState()))
				{
					TheGame::Instance()->changeSceneState(SceneState::LEVEL3_SCENE);
				}
				else if ((m_prevSceneState == LEVEL2_SCENE) && (!TheGame::Instance()->getWinState()))
				{
					TheGame::Instance()->changeSceneState(SceneState::LEVEL2_SCENE);
				}

				if ((m_prevSceneState == LEVEL3_SCENE) && (!TheGame::Instance()->getWinState()))
				{
					TheGame::Instance()->changeSceneState(SceneState::LEVEL3_SCENE);
				}
				break;
			case SDLK_2:
				TheGame::Instance()->changeSceneState(SceneState::START_SCENE);
				break;
			}
			break;

		default:
			break;
		}
	}
}

void InstructionScene::start()
{
	const SDL_Color red = { 255, 0, 0, 255 };
	const SDL_Color black = { 0, 0, 0, 255 };

	m_pLabel1 = new Label("Instructions:", "Consolas", 40, black, glm::vec2(Config::SCREEN_WIDTH * 0.25f, Config::SCREEN_HEIGHT * 0.05f));
	m_pLabel1->setParent(this);
	addChild(m_pLabel1);

	m_pLabel4 = new Label("Controls:", "Consolas", 40, black, glm::vec2(Config::SCREEN_WIDTH * 0.18f, Config::SCREEN_HEIGHT * 0.35f));
	m_pLabel4->setParent(this);
	addChild(m_pLabel4);

	m_pLabel5 = new Label("W - UP", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.075f, Config::SCREEN_HEIGHT * 0.40f));
	m_pLabel5->setParent(this);
	addChild(m_pLabel5);

	m_pLabel6 = new Label("S - DOWN", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.09f, Config::SCREEN_HEIGHT * 0.45f));
	m_pLabel6->setParent(this);
	addChild(m_pLabel6);

	m_pLabel7 = new Label("A - LEFT", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.09f, Config::SCREEN_HEIGHT * 0.50f));
	m_pLabel7->setParent(this);
	addChild(m_pLabel7);

	m_pLabel8 = new Label("D - RIGHT", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.10f, Config::SCREEN_HEIGHT * 0.55f));
	m_pLabel8->setParent(this);
	addChild(m_pLabel8);

	m_pLabel9 = new Label("SPACE - FIRE WEAPON", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.195f, Config::SCREEN_HEIGHT * 0.60f));
	m_pLabel9->setParent(this);
	addChild(m_pLabel9);

	m_pLabel10 = new Label("Press 1 to continue...", "Consolas", 40, black, glm::vec2(Config::SCREEN_WIDTH * 0.5f, Config::SCREEN_HEIGHT * 0.80f));
	m_pLabel10->setParent(this);
	addChild(m_pLabel10);

	m_prevSceneState = TheGame::Instance()->getPrevSceneState();

	if (m_prevSceneState == START_SCENE)
	{
		m_pLabel2 = new Label("You must kill the specified number", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.325f, Config::SCREEN_HEIGHT * 0.10f));
		m_pLabel2->setParent(this);
		addChild(m_pLabel2);

		m_pLabel3 = new Label("of enemies to proceed!", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.22f, Config::SCREEN_HEIGHT * 0.15f));
		m_pLabel3->setParent(this);
		addChild(m_pLabel3);
	}

	if ((m_prevSceneState == LEVEL1_SCENE) && (TheGame::Instance()->getWinState()))
	{
		m_pLabel2 = new Label("You must kill the specified number", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.32f, Config::SCREEN_HEIGHT * 0.10f));
		m_pLabel2->setParent(this);
		addChild(m_pLabel2);

		m_pLabel3 = new Label("of enemies to proceed!", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.22f, Config::SCREEN_HEIGHT * 0.15f));
		m_pLabel3->setParent(this);
		addChild(m_pLabel3);

		m_pLabel11 = new Label("Enemies are now shielded (two hits to die).", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.41f, Config::SCREEN_HEIGHT * 0.20f));
		m_pLabel11->setParent(this);
		addChild(m_pLabel11);

		m_pLabel12 = new Label("Enemies now also shoot bullets.", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.30f, Config::SCREEN_HEIGHT * 0.25f));
		m_pLabel12->setParent(this);
		addChild(m_pLabel12);
	}
	else if ((m_prevSceneState == LEVEL1_SCENE) && (!TheGame::Instance()->getWinState()))
	{
		m_pLabel2 = new Label("You must kill the specified number", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.325f, Config::SCREEN_HEIGHT * 0.10f));
		m_pLabel2->setParent(this);
		addChild(m_pLabel2);

		m_pLabel3 = new Label("of enemies to proceed!", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.22f, Config::SCREEN_HEIGHT * 0.15f));
		m_pLabel3->setParent(this);
		addChild(m_pLabel3);
	}

	if ((m_prevSceneState == LEVEL2_SCENE) && (TheGame::Instance()->getWinState()))
	{
		m_pLabel2 = new Label("Boss battle! You need to hit the boss", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.355f, Config::SCREEN_HEIGHT * 0.10f));
		m_pLabel2->setParent(this);
		addChild(m_pLabel2);

		m_pLabel3 = new Label("a specified number of times to kill it", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.365f, Config::SCREEN_HEIGHT * 0.15f));
		m_pLabel3->setParent(this);
		addChild(m_pLabel3);
	}
	else if ((m_prevSceneState == LEVEL2_SCENE) && (!TheGame::Instance()->getWinState()))
	{
		m_pLabel2 = new Label("You must kill the specified number", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.32f, Config::SCREEN_HEIGHT * 0.10f));
		m_pLabel2->setParent(this);
		addChild(m_pLabel2);

		m_pLabel3 = new Label("of enemies to proceed!", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.22f, Config::SCREEN_HEIGHT * 0.15f));
		m_pLabel3->setParent(this);
		addChild(m_pLabel3);

		m_pLabel11 = new Label("Enemies are now shielded (two hits to die).", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.41f, Config::SCREEN_HEIGHT * 0.20f));
		m_pLabel11->setParent(this);
		addChild(m_pLabel11);

		m_pLabel12 = new Label("Enemies now also shoot bullets.", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.30f, Config::SCREEN_HEIGHT * 0.25f));
		m_pLabel12->setParent(this);
		addChild(m_pLabel12);
	}

	if ((m_prevSceneState == LEVEL3_SCENE) && (!TheGame::Instance()->getWinState()))
	{
		m_pLabel2 = new Label("Boss battle! You need to hit the boss", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.355f, Config::SCREEN_HEIGHT * 0.10f));
		m_pLabel2->setParent(this);
		addChild(m_pLabel2);

		m_pLabel3 = new Label("a specified number of times to kill it", "Consolas", 20, black, glm::vec2(Config::SCREEN_WIDTH * 0.365f, Config::SCREEN_HEIGHT * 0.15f));
		m_pLabel3->setParent(this);
		addChild(m_pLabel3);
	}
}

