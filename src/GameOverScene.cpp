#include "GameOverScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"

GameOverScene::GameOverScene()
{
	GameOverScene::start();
}

GameOverScene::~GameOverScene()
= default;

void GameOverScene::draw()
{
	m_pStartLabel->draw();
	m_pInstructionsLabel->draw();
	m_pInstructionsLabel2->draw();
}

void GameOverScene::update()
{
}

void GameOverScene::clean()
{
	std::cout << "Clean called on GameOverScene" << std::endl;

	delete m_pStartLabel;
	m_pStartLabel = nullptr;

	delete m_pInstructionsLabel;
	m_pInstructionsLabel = nullptr;

	removeAllChildren();
}

void GameOverScene::handleEvents()
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
				TheGame::Instance()->changeSceneState(SceneState::START_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::START_SCENE);
				break;
			}
			break;

		default:
			break;
		}
	}
}

void GameOverScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	const SDL_Color black = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("CONGRATULATIONS!!!", "Dock51", 60, black, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.20f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("You beat the game!!!", "Consolas", 40, black, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.40f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel2 = new Label("Press 1 to go back to start menu...", "Consolas", 30, black, glm::vec2(Config::SCREEN_WIDTH * 0.50f, Config::SCREEN_HEIGHT * 0.60f));
	m_pInstructionsLabel2->setParent(this);
	addChild(m_pInstructionsLabel2);
}

