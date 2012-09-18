#ifndef PLANET_HPP
#define PLANET_HPP

#include <GL/glew.h>
#include <vector>

#include "../core/ColorRGBA.hpp"
#include "../core/Vector3d.hpp"

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

	void updateArrays(int i, int j);

private:
	typedef struct
	{
		Vector3d pos;
		ColorRGBA color;
	} Vertex;

	int mSlices, mStacks;

	double mRadius;

	void colorVertex(ColorRGBA c);
	void drawVertex(Vertex v);

	void renderWater();
	void renderNormals();

	void elevateAll(double amount = 0.1);
	void elevatePoles(double amount = 0.1);

	void colorize();

	std::vector< std::vector<Vertex> > map;
	std::vector< std::vector<Vertex> > waterMap;

	GLfloat *mVertexes;
	GLfloat *mWaterVertexes;
	GLfloat *mNormals;
	GLfloat *mColors;
	GLuint *mIndices;
};

#endif // PLANET_HPP
