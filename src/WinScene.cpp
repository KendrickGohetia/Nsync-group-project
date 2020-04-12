#include "WinScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"

WinScene::WinScene()
{
	WinScene::start();
}

WinScene::~WinScene()
= default;

void WinScene::draw()
{
	m_pStartLabel->draw();
	m_pInstructionsLabel->draw();
	m_pInstructionsLabel2->draw();
}

void WinScene::update()
{
}

void WinScene::clean()
{
	std::cout << "Clean called on WinScene" << std::endl;

	delete m_pStartLabel;
	m_pStartLabel = nullptr;

	delete m_pInstructionsLabel;
	m_pInstructionsLabel = nullptr;

	/*delete m_pShip;
	m_pShip = nullptr;*/

	removeAllChildren();
}

void WinScene::handleEvents()
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

void WinScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("You WON!!!", "Dock51", 80, blue, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.20f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to continue...", "Consolas", 40, blue, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.40f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel2 = new Label("Press 2 to go back to start menu...", "Consolas", 30, blue, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.60f));
	m_pInstructionsLabel2->setParent(this);
	addChild(m_pInstructionsLabel2);
}

