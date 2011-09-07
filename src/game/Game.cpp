#include "Game.hpp"
#include "../core/EventManager.hpp"
#include <iostream>
#include <sstream>

#include <GL/glut.h>

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
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
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

//	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

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
	lastTime = SDL_GetTicks();
	currentTime = lastTime;
	int frames = 0;
	while(mRunning)
	{
		EventManager::getInstance()->captureEvent();

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// rendu de la scene :
		mScene->render();

//		currentTime = SDL_GetTicks();
//		std::stringstream ss;
//		ss << frames << " FPS";
//		baseLogger()->debugLine(ss.str());
//		if(currentTime % 60 == 0)
//		{
//			std::stringstream ss;
//			ss << frames << " FPS";
//			baseLogger()->debugLine(ss.str());
//			lastTime = currentTime;
//			frames = 0;
//		}

//		frames++;

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
