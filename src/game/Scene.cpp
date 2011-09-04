#include "Scene.hpp"
#include "Game.hpp"
#include "../core/EventManager.hpp"

Scene::Scene()
{
	mCamera = new Camera(Game::getInstance()->ratio());
	EventManager::getInstance()->subscribe(mCamera);
	mPlanet = new Planet();
}

void Scene::render()
{
//	glClearColor(1.f, 1.f, 1.f, 1.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	mCamera->look();

	mPlanet->render();
}
