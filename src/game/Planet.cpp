#include "Planet.hpp"
#include <cmath>
#include <stdlib.h>
#include <iostream>

Planet::Planet() :
	mSlices(4),
	mStacks(4),
	mRadius(1000.f)
{


	// initialize map
	map.resize(mStacks+1);
	for(int i=0; i<mStacks+1; i++)
	{
		map[i].resize(mSlices);
	}

	testMap = new GLfloat[3*(mSlices)*(mStacks+1)];


	// computing and storing vertices
	double pdelta = 360.f/mSlices;
	double tdelta = 180.f/mStacks;

	ColorRGBA c;

	int ind_i = 0;
	for(double t=-90; t<=90; t += tdelta)
	{
		int ind_j = 0;
		for(double p=0; p<360; p += pdelta)
		{
			Vector3d v;
			v.x = mRadius*cos(t*M_PI/180.f)*cos(p*M_PI/180.f);
			v.y = mRadius*cos(t*M_PI/180.f)*sin(p*M_PI/180.f);
			v.z = sin(t*M_PI/180.f)*mRadius;
			map[ind_i][ind_j].pos = v;
			map[ind_i][ind_j].color = c;
			testMap[(mSlices*3*ind_i)+ 3*ind_j+0]=v.x;
			testMap[(mSlices*3*ind_i)+ 3*ind_j+1]=v.y;
			testMap[(mSlices*3*ind_i)+ 3*ind_j+2]=v.z;
			ind_j++;
		}
		ind_i++;
	}
//	waterMap = map;

	// making relief
//	elevatePoles(0.3);
//	randomizeMap(10.0/(mSlices));
//	colorize();
}


/**
  used to add some random deformation
  according to lattitude :
  poles are less deformed
  */
void Planet::randomizeMap(double factor)
{
	for(int i=0; i<mStacks; i++)
	{
		// la latitude détermine la puissance du modifier
		double modifier = mStacks/2 - fabs((-mStacks/2) + i);
//		std::cout << "modif : " << (modifier/(mStacks/2)) << std::endl;
		for(int j=0; j<mSlices; j++)
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

void Planet::deformVertexLinear(int i, int j, double amount, double radius, double stroke)
{
	if(radius>1) radius = 1; // clip radius
	if(radius<0) radius = 0;
	if(stroke>=1) stroke = 0.99; // clip stroke
	if(stroke<0) stroke = 0;

	double iRadius = (mStacks/2.f)*radius;
	double jRadius = (mSlices/4.f)*radius;

	double iDelta = iRadius - (iRadius*stroke);
	double jDelta = jRadius - (jRadius*stroke);

	for(int k=-iRadius; k<=iRadius; k++)
	{
		for(int l=-jRadius; l<=jRadius; l++)
		{
			if(i+k<=mStacks && i+k>=0 ) // j is correctly managed later
			{

				double attI = 1.f;
				if(iDelta>0.f)
					attI = ((fabs(k)-(iRadius*stroke))/(iDelta));
				double factorI = 1*(1.f - attI );

				double attJ = 1.f;
				if(jDelta>0.f)
					attJ = ((fabs(l)-(jRadius*stroke))/(jDelta));
				double factorJ = 1*(1.f - attJ);

				if(factorI>1) factorI = 1.f;
				if(factorJ>1) factorJ = 1.f;

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
	Vector3d v = map[i][j].pos;
	v.x *= offset;
	v.y *= offset;
	v.z *= offset;
	map[i][j].pos = v;
}

void Planet::deformLine(int i1, int j1, int i2, int j2, double amount, double radius)
{
	amount *= radius;

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

void Planet::createRiver(int startJ)
{
	int minI = 1*mStacks/6;
	int maxI = 5*mStacks/6;
	int startI = (rand()%(maxI-minI))+minI;
	int endI = (rand()%(maxI-minI))+minI;

//	int startJ = rand()%(mSlices*2)-mSlices;
	int endJ = rand()%(mSlices*2)-mSlices;

	double amount = 0.3;
	int tmp = rand()%2;
	if(tmp>0)
		amount *= -1;

	deformLine(startI, startJ, endI, endJ, amount);
}

void Planet::render()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// render sphere from map
//	for(int i=0; i<mStacks; i++)
//	{
//		for(int j=0; j<mSlices; j++)
//		{
//			glBegin(GL_POINTS);
//			int _j = j+1; if(_j>=mSlices) _j=0;
//			Vertex v1 = map[i][j];
//			colorVertex(v1.color);
//			drawVertex(v1);
//			Vertex v2 = map[i][_j];
//			colorVertex(v2.color);
//			drawVertex(v2);
//			Vertex v3 = map[i+1][_j];
//			colorVertex(v3.color);
//			drawVertex(v3);
//			Vertex v4 = map[i+1][j];
//			colorVertex(v4.color);
//			drawVertex(v4);
//			glEnd();
//		}
//	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, testMap);
	glDrawArrays(GL_POINTS, 0, 3*mStacks*mSlices);
	glDisableClientState(GL_VERTEX_ARRAY);


//	renderWater();
}

void Planet::renderWater()
{
	int di = 4;
	int dj = 2;

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for(int i=0; i<mStacks/di; i++)
	{
		for(int j=0; j<mSlices/dj; j++)
		{
			glBegin(GL_POINTS);
			glColor4d(0,0.6,0.6,0.6);
			int _j = j+1; if(_j>=mSlices/dj) _j=0;
			Vertex v1 = waterMap[di*i][dj*j];
			drawVertex(v1);
			Vertex v2 = waterMap[di*i][dj*_j];
			drawVertex(v2);
			Vertex v3 = waterMap[di*(i+1)][dj*_j];
			drawVertex(v3);
			Vertex v4 = waterMap[di*(i+1)][dj*j];
			drawVertex(v4);
			glEnd();
		}
	}
	glDisable(GL_BLEND);
}

void Planet::colorVertex(ColorRGBA c)
{
	glColor4d(c.red(), c.green(), c.blue(), c.alpha());
	glColor4d(1,1,1,1);
}

void Planet::drawVertex(Vertex v)
{

	Vector3d normal(v.pos.x, v.pos.y, v.pos.z);
	normal.normalize();

	glNormal3d(normal.x, normal.y, normal.z);
	glVertex3d(v.pos.x, v.pos.y, v.pos.z);
}

void Planet::elevateAll(double amount)
{
	for(int i=0; i<=mStacks; i++)
	{
		for(int j=0; j<mSlices; j++)
		{
			deformVertex(i,j,amount);
		}
	}
}

void Planet::elevatePoles(double amount)
{
	for(int j=0; j<mSlices; j++)
	{
//		Vertex vTop = map[0][j];
//		Vertex vBottom = map[mStacks][j];
		deformVertexLinear(0, j, amount/mSlices, 0.2);
		deformVertexLinear(mStacks, j, amount/mSlices, 0.2);
	}
}

void Planet::colorize()
{
	double maxHeight = 0;
//	double minHeight = 0;

	for(int i=0; i<=mStacks; i++)
	{
		for(int j=0; j<mSlices; j++)
		{
			Vector3d delta = map[i][j].pos - waterMap[i][j].pos;
			double height = delta.length();
			if(height > maxHeight) maxHeight = height;
//			if(height < minHeight) minHeight = height;
		}
	}
	for(int i=0; i<=mStacks; i++)
	{
		for(int j=0; j<mSlices; j++)
		{
			Vector3d delta = map[i][j].pos - waterMap[i][j].pos;
			double height = delta.length();
			double scale = 0;
			if(maxHeight!=0)
			{
				scale = (2*height/maxHeight)-0.75;
				if(scale > 1) scale = 1;
				if(scale < 0) scale = 0;
			}

			ColorRGBA base(0.2,0.4,0.2,1);
			ColorRGBA snow(1,1,1,scale);

			base.blend(snow);



			map[i][j].color = base;


		}
	}
}



