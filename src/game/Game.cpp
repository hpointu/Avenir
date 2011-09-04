#include "Game.hpp"
#include "../core/EventManager.hpp"
#include <iostream>

Game::Game() :
	mRunning(false),
	mWidth(800),
	mHeight(600)
{
	srand(time(0));
	EventManager::getInstance()->subscribe(this);
}

/**
  initialisation de la fenêtre de jeu
  ainsi que du contexte OpenGL
  */
void Game::init()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("Avenir...", NULL);
	SDL_SetVideoMode(mWidth, mHeight, 32, SDL_OPENGL);

	atexit(SDL_Quit);

	mRunning = true;

	initOpenGL();

	mScene = new Scene();
}

/**
  initialisation OpenGL
  */
void Game::initOpenGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	// initialisation de GLEW
	GLenum code = glewInit();
	if(code != GLEW_OK)
	{
		baseLogger()->errorLine("Error while initializing GLEW :");
		baseLogger()->errorLine((char*)glewGetErrorString(code));
	}
	else
	{
		baseLogger()->debugLine("GLEW is ready");
	}
}

/**
  boucle principale
  */
void Game::run()
{
	while(mRunning)
	{
		EventManager::getInstance()->captureEvent();

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// rendu de la scene :
		mScene->render();

		glFlush();
		SDL_GL_SwapBuffers();
	}
}

/**
  Gestion des événements Jeu
  */
void Game::onEvent(const SDL_Event &event)
{
	switch(event.type)
	{
	case SDL_QUIT:
		mRunning = false;
		break;
	}
}
