#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <SFML/Graphics.hpp>

#include "../core/EventListener.hpp"

class Camera : public EventListener
{
public:
	Camera(float ratio);

	void look();

	void updatePerspective();

	void onEvent(const sf::Event &event);

private:
	float mFovy;
	float mNear;
	float mFar;
	float mRatio;

	double mTheta;
	double mPhi;
	double mZoom;

	bool mHold;
	sf::Vector2f mouseClick;

};

#endif // CAMERA_HPP
