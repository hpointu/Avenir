#ifndef PLANET_HPP
#define PLANET_HPP

#include <GL/glew.h>
#include <vector>

class Planet
{
public:
    Planet();

	void render();

	void randomizeMap(double factor = 0.1);

	void deformVertexLinear(int i, int j, double amount, double radius, double stroke = 0.f);
	void deformVertex(int i, int j, double amount);

	void deformLine(int i1, int j1, int i2, int j2, double amount, double radius = 0.1);
	void createRiver(int startJ);

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
	std::vector< std::vector<Vertex> > waterMap;
};

#endif // PLANET_HPP
