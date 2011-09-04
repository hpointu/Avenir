#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <SDL/SDL.h>

#include "../core/EventListener.hpp"

class Camera : public EventListener
{
public:
	Camera(float ratio);

	void look();

	void updatePerspective();

	void onEvent(const SDL_Event &event);

private:
	float mFovy;
	float mNear;
	float mFar;
	float mRatio;

	double mTheta;
	double mPhi;
	double mZoom;

	bool mHold;

};

#endif // CAMERA_HPP
