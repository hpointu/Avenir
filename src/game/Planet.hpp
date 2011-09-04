#ifndef PLANET_HPP
#define PLANET_HPP

#include <GL/glew.h>
#include <vector>

class Planet
{
public:
    Planet();

	void render();

	void randomizeMap();

	void deformVertexLinear(int i, int j, double amount, double radius);
	void deformVertex(int i, int j, double amount);

private:

	int mSlices, mStacks;

	double mRadius;

	typedef struct
	{
		double x;
		double y;
		double z;
	} Vertex;

	std::vector< std::vector<Vertex> > map;
};

#endif // PLANET_HPP
