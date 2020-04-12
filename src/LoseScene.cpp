#include "LoseScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"

LoseScene::LoseScene()
{
	LoseScene::start();
}

LoseScene::~LoseScene()
= default;

void LoseScene::draw()
{
	m_pStartLabel->draw();
	m_pInstructionsLabel->draw();
	m_pInstructionsLabel2->draw();
}

void LoseScene::update()
{
}

void LoseScene::clean()
{
	std::cout << "Clean called on LoseScene" << std::endl;

	delete m_pStartLabel;
	m_pStartLabel = nullptr;

	delete m_pInstructionsLabel;
	m_pInstructionsLabel = nullptr;

	/*delete m_pShip;
	m_pShip = nullptr;*/

	removeAllChildren();
}

void LoseScene::handleEvents()
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
				TheGame::Instance()->changeSceneState(SceneState::INSTRUCTION_SCENE);
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

void LoseScene::start()
{
	const SDL_Color red = { 255, 0, 0, 255 };
	m_pStartLabel = new Label("You LOST!!!", "Dock51", 80, red, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.20f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 continue...", "Consolas", 40, red, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.40f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel2 = new Label("Press 2 to go back to start menu...", "Consolas", 30, red, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.60f));
	m_pInstructionsLabel2->setParent(this);
	addChild(m_pInstructionsLabel2);
}

