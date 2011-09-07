#ifndef COLORRGBA_HPP
#define COLORRGBA_HPP

class ColorRGBA
{
public:
	ColorRGBA();
	ColorRGBA(const ColorRGBA &c);
	ColorRGBA(double r, double g, double b, double a = 1.f);

	void blend(const ColorRGBA &c);

	double red() const;
	double green() const;
	double blue() const;
	double alpha() const;

private:
	double mRed;
	double mGreen;
	double mBlue;
	double mAlpha;
};

#endif // COLORRGBA_HPP
