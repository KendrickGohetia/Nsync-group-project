#include "Level1Scene.h"
#include "Game.h"

Level1Scene::Level1Scene()
{
	Level1Scene::start();
}

Level1Scene::~Level1Scene()
= default;

void Level1Scene::draw()
{
	m_background.draw();
	drawDisplayList();
}

void Level1Scene::update()
{
	updateDisplayList();
}

void Level1Scene::clean()
{

	removeAllChildren();
}

void Level1Scene::handleEvents()
{
	auto wheel = 0;
	
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEMOTION:
			m_mousePosition.x = event.motion.x;
			m_mousePosition.y = event.motion.y;
			break;
		case SDL_MOUSEWHEEL:
			wheel = event.wheel.y;
			break;
		case SDL_KEYDOWN:
			const auto keyPressed = event.key.keysym.sym;
			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				TheGame::Instance()->quit();
				break;
			case SDLK_1:
				//TheGame::Instance()->changeSceneState(SceneState::PLAY_SCENE);
				break;
			case SDLK_2:
				//TheGame::Instance()->changeSceneState(SceneState::END_SCENE);
				break;
			}
			// movement keys
			{
				if(keyPressed == SDLK_w)
				{
					std::cout << "move forward" << std::endl;
					m_pShip->moveForward();
				}

				if (keyPressed == SDLK_a)
				{
					std::cout << "move left" << std::endl;
					m_pShip->moveLeft();
				}

				if (keyPressed == SDLK_s)
				{
					std::cout << "move back" << std::endl;
					m_pShip->moveBack();
				}

				if (keyPressed == SDLK_d)
				{
					std::cout << "move right" << std::endl;
					m_pShip->moveRight();
				}

				if (keyPressed == SDLK_SPACE)
				{
					std::cout << "fire weapon" << std::endl;
					m_pShip->moveRight();
				}
			}
			
			break;
		}
	}
}

void Level1Scene::start()
{
	m_background = Background();

	m_pShip = new Ship();
	m_pShip->setPosition(Config::SCREEN_WIDTH * 0.5, Config::SCREEN_HEIGHT * 0.9);
	addChild(m_pShip);
}
