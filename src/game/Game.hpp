#ifndef GAME_HPP
#define GAME_HPP

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <time.h>
#include <stdlib.h>

#include "../core/AbstractClass.hpp"
#include "../core/EventListener.hpp"
#include "../core/Singleton.cpp"

#include "Scene.hpp"

class Game :
		public AbstractClass,
		public EventListener,
		public Singleton<Game>
{
public:
	friend class Singleton<Game>;

	void run();
	void init();

	int width(){return mWidth;}
	int height(){return mHeight;}
	double ratio(){return (double)mWidth/mHeight;}

	virtual void onEvent(const SDL_Event &event);

private:
	Game();
	void initOpenGL();

	bool mRunning;
	int mWidth, mHeight;

	Scene *mScene;

};

#endif // GAME_HPP
