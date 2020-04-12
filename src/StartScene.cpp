#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	m_pStartLabel->draw();
	m_pInstructionsLabel->draw();
}

void StartScene::update()
{
}

void StartScene::clean()
{
	std::cout << "Clean called on StartScene" << std::endl;
	
	delete m_pStartLabel;
	m_pStartLabel = nullptr;
	
	delete m_pInstructionsLabel;
	m_pInstructionsLabel = nullptr;

	removeAllChildren();
}

void StartScene::handleEvents()
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
				//TheGame::Instance()->changeSceneState(SceneState::GAME_OVER_SCENE);
				break;
			}
			break;

		default:
			break;
		}
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color black = { 0, 0, 0, 255 };

	m_pStartLabel = new Label("EARTH DEFENSE", "Dock51", 80, black, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.20f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Press 1 to Play", "Consolas", 40, black, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.40f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);
}

