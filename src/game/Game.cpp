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
	srand(1234);
//	srand(time(0));
	EventManager::getInstance()->subscribe(this);

}

/**
  initialisation de la fenêtre de jeu
  ainsi que du contexte OpenGL
  */
void Game::init()
{
	window = new sf::Window(sf::VideoMode(mWidth,mHeight,32), "Avenir");

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
//	lastTime = SDL_GetTicks();
	currentTime = lastTime;
	int frames = 0;
	while(mRunning)
	{
		EventManager::getInstance()->captureEvent(window);

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// rendu de la scene :
		mScene->render();

//		currentTime = SDL_GetTicks();
//		std::stringstream ss;
//		ss << frames << " FPS";
//		baseLogger()->infoLine(ss.str());
//		if(currentTime - lastTime > 600)
//		{
//			std::stringstream ss;
//			ss << frames << " FPS";
//			baseLogger()->infoLine(ss.str());
//			lastTime = currentTime;
//			frames = 0;
//		}

		frames++;

//		glFlush();
		window->Display();
	}
}

/**
  Gestion des événements Jeu
  */
void Game::onEvent(const sf::Event &event)
{
	switch(event.Type)
	{
	case sf::Event::Closed:
		mRunning = false;
		break;
	default:
		break;
	}
}
