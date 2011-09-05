#include "Planet.hpp"
#include <cmath>
#include <stdlib.h>
#include <iostream>

// TODO: bug under 32*32
Planet::Planet() :
	mSlices(64),
	mStacks(64),
	mRadius(1000.f)
{
	// initialize map
	map.resize(mStacks+1);
	for(int i=0; i<mStacks+1; i++)
		map[i].resize(mSlices);


	// computing and storing vertices
	double pdelta = 360.f/mSlices;
	double tdelta = 180.f/mStacks;

	int ind_i = 0;
	for(double t=-90; t<=90; t += tdelta)
	{
		int ind_j = 0;
		for(double p=0; p<360; p += pdelta)
		{
			Vertex v;
			v.x = mRadius*cos(t*M_PI/180.f)*cos(p*M_PI/180.f);
			v.y = mRadius*cos(t*M_PI/180.f)*sin(p*M_PI/180.f);
			v.z = sin(t*M_PI/180.f)*mRadius;
			map[ind_i][ind_j] = v;
			ind_j++;
		}
		ind_i++;
	}
	waterMap = map;

//	deformVertexLinear(17, 33, -0.2, 0.1);
	createRiver(10);
//	deformLine(32,-32, 35,10, -0.05, 0.1);
//	createRiver(10);createRiver(10);createRiver(10);
//	createRiver(10);createRiver(10);createRiver(10);
//	createRiver(10);createRiver(10);createRiver(10);
//	randomizeMap(0.1);

//	deformVertex(16, 32, 0.05);
//	deformVertex(16, 33, -0.05);
}


/**
  used to add some random deformation
  according to lattitude :
  poles are less deformed
  */
void Planet::randomizeMap(double factor)
{
	for(int i=2; i<mStacks-1; i++)
	{
		// la latitude détermine la puissance du modifier
		double modifier = mStacks/2 - fabs((-mStacks/2) + i);
//		std::cout << "modif : " << (modifier/(mStacks/2)) << std::endl;
		for(int j=2; j<mSlices-2; j++)
		{
			double fac = (rand()%10000)/10000.f;
			fac -= 0.5;
			fac /= 2;
			fac *= (modifier/(mStacks/2));

			fac *= factor; // final factor

//			std::cout << "fac : " << fac << std::endl;
			deformVertexLinear(i, j, fac, 0.1);
		}
	}
}

void Planet::deformVertexLinear(int i, int j, double amount, double radius)
{
	if(radius>1) radius = 1; // clip radius

	int iRadius = (mStacks/2)*radius;
	int jRadius = (mSlices/2)*radius;

	for(int k=-iRadius; k<=iRadius; k++)
	{
		for(int l=-jRadius; l<=jRadius; l++)
		{
			if(i+k<mStacks && i+k>0 ) // j is correctly managed later
			{
				double factorI = 1*(1.f - (fabs(k)/(iRadius)));
				double factorJ = 1*(1.f - (fabs(l)/(jRadius)));
				double offset = amount*factorI*factorJ;

				deformVertex(i+k,j+l,offset);
			}
		}
	}
}

void Planet::deformVertex(int i, int j, double amount)
{
	// well formed j
	if(j<0) j+=mSlices;
	if(j>=mSlices) j-=mSlices;

	double offset = 1.f + amount;
	Vertex v = map[i][j];
	v.x *= offset;
	v.y *= offset;
	v.z *= offset;
	map[i][j] = v;
}

void Planet::deformLine(int i1, int j1, int i2, int j2, double amount, double radius)
{

	int sx, sy;
	int dx = abs(i2-i1);
	int dy = abs(j2-j1);
	sx = (i1<i2) ? 1 : -1 ;
	sy = (j1<j2) ? 1 : -1 ;
	int err = dx-dy;
	do
	{
		if(j1<0) j1+=mSlices;
		if(j1>=mSlices) j1-=mSlices;
		if(j2<0) j2+=mSlices;
		if(j2>=mSlices) j2-=mSlices;
		this->deformVertexLinear(i1,j1, amount, radius);
		int e2 = 2*err;
		if(e2 > -dy)
		{
			err -= dy;
			i1 += sx;
		}
		if(e2 < dx)
		{
			err += dx;
			j1 += sy;
		}
	} while(i1 != i2 || j1 != j2);
}

void Planet::createRiver(int offset, int length)
{
	int startI = (rand()%(mStacks-5))+2;
	int endI = (rand()%(mStacks-5))+2;

	int startJ = rand()%(mSlices*2)-mSlices;
	int endJ = rand()%(mSlices*2)-mSlices;

	deformLine(startI, startJ, endI, endJ, -0.05);
}

void Planet::render()
{
	glColor3d(1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// render sphere from map
	for(int i=0; i<mStacks; i++)
	{
		glBegin(GL_QUAD_STRIP);
		glColor3d(0,0,1); // seam color (debug)
		Vertex v1 = map[i+1][0]; glVertex3d(v1.x, v1.y, v1.z);
		Vertex v2 = map[i][0]; glVertex3d(v2.x, v2.y, v2.z);
		glColor3d(1,1,1);
		for(int j=0; j<mSlices-1; j++)
		{
			Vertex v3 = map[i+1][j+1]; glVertex3d(v3.x, v3.y, v3.z);
			Vertex v4 = map[i][j+1]; glVertex3d(v4.x, v4.y, v4.z);
		}
		// last faces :
		glColor3d(1,0,0); // seam color (debug)
		Vertex v3 = map[i+1][0]; glVertex3d(v3.x, v3.y, v3.z);
		Vertex v4 = map[i][0]; glVertex3d(v4.x, v4.y, v4.z);
		glColor3d(1,1,1);
		glEnd();
	}
}
