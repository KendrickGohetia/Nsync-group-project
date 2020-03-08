#include "Game.h"
#include "Player.h"

#include<iostream>
Game* Game::s_pInstance = 0;

SDL_Renderer * Game::getRenderer()
{
	return m_pRenderer;
}

char Game::getPlayerPosition()
{
	return curKey;
}





Game::Game()
{
}

Game::~Game()
{
}

void Game::createGameObjects()
{	
	
	m_pPlayer = new Player();
	m_pEnemyv = new Enemy();
	m_pKey = new Key();
	for (size_t i = 0; i < m_cloudNum; i++)
	{
		//m_pClouds.push_back(new Cloud());
	}
}

bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		std::cout << "SDL Init success" << std::endl;

		// if succeeded create our window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		// if window creation successful create our renderer
		if (m_pWindow != 0)
		{
			std::cout << "window creation success" << std::endl;
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) // render init success
			{
				std::cout << "renderer creation success" << std::endl;
				SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
			}
			else
			{
				std::cout << "renderer init failure" << std::endl;
				return false; // render int fail
			}

			//TheTextureManager::Instance()->load("../../Assets/textures/animate-alpha.png", "animate", m_pRenderer);
			createGameObjects();
		}
		else 
		{
			std::cout << "window init failure" << std::endl;
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init failure" << std::endl;
		return false; //SDL could not intialize
	}

	std::cout << "init success" << std::endl;
	m_bRunning = true; // everything initialized successfully - start the main loop

	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw colour

	
	m_pPlayer->draw();
	m_pEnemyv->draw();
	m_pKey->draw();
	
	/*for (Cloud* cloud : m_pClouds) {
		cloud->draw();
	}*/

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}

void Game::update()
{
	m_pPlayer->update();
	m_pEnemyv->update();
	m_pKey->update();
	Collision::AABBCheck(m_pPlayer, m_pKey);
	Collision::AABBCheck(m_pPlayer, m_pEnemyv);
	
	/*for (Cloud* cloud : m_pClouds) {
		cloud->update();
		Collision::squaredRadiusCheck(m_pPlayer, cloud);
	}*/

}

void Game::clean()
{
	std::cout << "cleaning game" << std::endl;

	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	SDL_Quit();
}



void Game::handleEvents()
{
	
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		
		
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_w) {
				curKey = 'w';	
			}
			else if (event.key.keysym.sym == SDLK_a) {
				curKey = 'a';
			}
			else if (event.key.keysym.sym == SDLK_s) {
				curKey = 's';
			}
			else if (event.key.keysym.sym == SDLK_d) {
				curKey = 'd';
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym != SDLK_w) {
				curKey = '-';
			}
			else if (event.key.keysym.sym != SDLK_a) {
				curKey = '-';
			}
			else if (event.key.keysym.sym != SDLK_s) {
				curKey = '-';
			}
			else if (event.key.keysym.sym != SDLK_d) {
				curKey = '-';
			}
			
		default:
			break;
		}
	}
}