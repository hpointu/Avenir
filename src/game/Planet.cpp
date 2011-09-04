#include "Planet.hpp"
#include <cmath>
#include <stdlib.h>
#include <iostream>

Planet::Planet() :
	mSlices(64),
	mStacks(32),
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

	randomizeMap();
//	deformVertexLinear(32, 64, 0.15, 0.1);

//	deformVertex(16, 32, 0.05);
//	deformVertex(16, 33, -0.05);
}

void Planet::randomizeMap()
{
	for(int i=2; i<mStacks-1; i++)
	{
		// latitude détermine la puissance du modifier
		double modifier = mStacks/2 - fabs((-mStacks/2) + i);
		std::cout << "modif : " << modifier << std::endl;
		for(int j=2; j<mSlices-2; j++)
		{
			double fac = (rand()%10000)/10000.f;
			fac -= 0.5;
			fac /= 2;
//			fac /= (mStacks/2.f);
			deformVertexLinear(i, j, fac/4, 0.1);
//			fac *= modifier;
//			double amount = 1.f+((fac-0.5)/5.0);
//			deformVertex(i,j,amount);
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
			if(i+k<mStacks && j+l<=mSlices
					&& i+k>0 && j+l>0)
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
	double offset = 1.f + amount;
	Vertex v = map[i][j];
	v.x *= offset;
	v.y *= offset;
	v.z *= offset;
	map[i][j] = v;
}

void Planet::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// render sphere from map
	for(int i=0; i<mStacks; i++)
	{
		glBegin(GL_QUAD_STRIP);
		Vertex v1 = map[i+1][0]; glVertex3d(v1.x, v1.y, v1.z);
		Vertex v2 = map[i][0]; glVertex3d(v2.x, v2.y, v2.z);
		for(int j=0; j<mSlices-1; j++)
		{
			Vertex v3 = map[i+1][j+1]; glVertex3d(v3.x, v3.y, v3.z);
			Vertex v4 = map[i][j+1]; glVertex3d(v4.x, v4.y, v4.z);
		}
		// last faces :
		Vertex v3 = map[i+1][0]; glVertex3d(v3.x, v3.y, v3.z);
		Vertex v4 = map[i][0]; glVertex3d(v4.x, v4.y, v4.z);
		glEnd();
	}
}
