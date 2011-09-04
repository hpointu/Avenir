#ifndef SCENE_HPP
#define SCENE_HPP

#include "Camera.hpp"
#include "Planet.hpp"

class Scene
{
public:
    Scene();
	void render();

private:
	Camera *mCamera;
	Planet *mPlanet;
};

#endif // SCENE_HPP
