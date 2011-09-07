#include "Camera.hpp"
#include <cmath>

Camera::Camera(float ratio):
	mFovy(70),
	mNear(1),
	mFar(10000),
	mRatio(ratio),
	mTheta(0),
	mPhi(0),
	mZoom(1.f),
	mHold(false)
{
	updatePerspective();
}


void Camera::updatePerspective()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(mFovy, mRatio, mNear, mFar);
}

void Camera::look()
{
	double posX = (4000.f*cos(mTheta)*cos(mPhi))/(mZoom*mZoom);
	double posY = (4000.f*sin(mTheta)*cos(mPhi))/(mZoom*mZoom);
	double posZ = (4000.f*sin(mPhi))/(mZoom*mZoom);

	gluLookAt(posX,posY,posZ, 0,0,0, 0,0,1);
}

void Camera::onEvent(const sf::Event &event)
{
	if(event.Type == sf::Event::MouseButtonPressed && event.MouseButton.Button == sf::Mouse::Left)
	{
		mouseClick = sf::Vector2f(event.MouseButton.X, event.MouseButton.Y);
		mHold = true;
	}
	else if(event.Type == sf::Event::MouseButtonReleased && event.MouseButton.Button == sf::Mouse::Left)
	{
		mHold = false;
	}
	else if(event.Type == sf::Event::MouseMoved && mHold)
	{
		double dX = event.MouseMove.X - mouseClick.x;
		double dY = event.MouseMove.Y - mouseClick.y;
		mTheta -= (dX*0.01)/(mZoom*mZoom);
		mPhi += (dY*0.01)/(mZoom*mZoom);

		if(mPhi>(M_PI/2.f))
			mPhi = (M_PI/2.f);
		if(mPhi<-(M_PI/2.f))
			mPhi = -(M_PI/2.f);

		mouseClick = sf::Vector2f(event.MouseMove.X, event.MouseMove.Y);
	}

	else if(event.Type == sf::Event::MouseWheelMoved)
	{
		int delta = event.MouseWheel.Delta;
		if(delta>0)
			mZoom += 0.05;
		else
			mZoom -= 0.05;
	}
	//	if(event.type == SDL_MOUSEMOTION && mHold)
	//	{
	//		mTheta -= (event.motion.xrel*0.01)/(mZoom*mZoom);
	//		mPhi += (event.motion.yrel*0.01)/(mZoom*mZoom);

	//		if(mPhi>(M_PI/2.f))
	//			mPhi = (M_PI/2.f);
	//		if(mPhi<-(M_PI/2.f))
	//			mPhi = -(M_PI/2.f);

	//	}

	//	else if(event.type == SDL_MOUSEBUTTONDOWN ||
	//			event.type == SDL_MOUSEBUTTONUP)
	//	{
	//		if(event.button.button == SDL_BUTTON_LEFT)
	//		{
	//			mHold = (event.type == SDL_MOUSEBUTTONDOWN);
	//		}
	//		else if(event.button.button == SDL_BUTTON_WHEELUP)
	//		{
	//			if(mZoom < 1.8f)
	//				mZoom += 0.05;
	//		}
	//		else if(event.button.button == SDL_BUTTON_WHEELDOWN)
	//		{

	//			mZoom -= 0.05;
	//		}
	//	}
}
