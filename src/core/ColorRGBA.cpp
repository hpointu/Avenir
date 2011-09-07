#include "ColorRGBA.hpp"

ColorRGBA::ColorRGBA()
{
	mRed = 0;
	mGreen = 0;
	mBlue = 0;
	mAlpha = 0;
}

ColorRGBA::ColorRGBA(const ColorRGBA &c)
{
	mRed = c.red();
	mGreen = c.green();
	mBlue = c.blue();
	mAlpha = c.alpha();
}

ColorRGBA::ColorRGBA(double r, double g, double b, double a)
{
	mRed = r;
	mGreen = g;
	mBlue = b;
	mAlpha = a;
}

void ColorRGBA::blend(const ColorRGBA &c)
{
	double ax = 1 - (1 - c.alpha()) * (1 - alpha());
	double rx = c.red() * c.alpha() / ax + red() * alpha() * (1-c.alpha())/ax;
	double gx = c.green() * c.alpha() / ax + green() * alpha() * (1-c.alpha())/ax;
	double bx = c.blue() * c.alpha() / ax + blue() * alpha() * (1-c.alpha())/ax;

	mRed = rx;
	mGreen = gx;
	mBlue = bx;
	mAlpha = ax;
}

double ColorRGBA::red() const
{
	return mRed;
}


double ColorRGBA::green() const
{
	return mGreen;
}


double ColorRGBA::blue() const
{
	return mBlue;
}


double ColorRGBA::alpha() const
{
	return mAlpha;
}
