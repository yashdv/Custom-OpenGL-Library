#ifndef _THE_API_
#define _THE_API_

#include<stack>
#include<queue>
#include<cstdio>
#include<cmath>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
using namespace std;
#define SZ 4

typedef struct transform
{
	float model[16];
}transform;

typedef struct triplet
{
	float x,y,z;
	int what;
}triplet;

transform matrix;
float *model_p = matrix.model;
float view_p[16];
float projection[16];
float viewPort[16];

stack<transform> Stack;
queue<triplet> Q;

void multiply(float *m1, float *m2, float *ans)
{
	float m3[SZ*SZ];
	for(int i=0; i<SZ; i++)
	{
		for(int j=0; j<SZ; j++)
		{
			m3[i*SZ + j] = 0;
			for(int k=0; k<SZ; k++)
				m3[i*SZ + j] += m1[i*SZ + k]*m2[k*SZ + j];
		}
	}
	for(int i=0; i<SZ*SZ; i++)
		ans[i] = m3[i];	
}
void sglMPushMatrix()
{
	Stack.push(matrix);
	model_p = Stack.top().model;
}

void sglMPopMatrix()
{
	Stack.pop();
	model_p = Stack.top().model;
}

void fillidentity(float *m)
{
	int t;
	for(int i=0; i<SZ; i++)
	{
		for(int j=0; j<SZ; j++)
		{
			if(i == j)
				t = 1;
			else 
				t = 0;
			m[i*SZ + j] = t;
		}
	}
}

void initialize()
{
	fillidentity(model_p);
	fillidentity(view_p);

	sglMPushMatrix();
	model_p = Stack.top().model;

	for(int i=0; i<SZ*SZ; i++)
		projection[i] = 0.0;
	for(int i=0; i<9; i++)
		viewPort[i] = 0.0;
}

void sglMTranslate(float tx,float ty,float tz)
{
	float translate[16] = {	1,0,0,tx,
				0,1,0,ty,
				0,0,1,tz,
				0,0,0,1	};
	multiply(model_p,translate,model_p);
}

void sglMScale(float sx,float sy,float sz)
{
	float scale[16] = {	sx,0,0,0,
				0,sy,0,0,
				0,0,sz,0,
				0,0,0,1	};
	multiply(model_p,scale,model_p);
}

void sglMMatrix(float *m)
{
	multiply(model_p,m,model_p);
}

void sglMLoadIdentity()
{
	fillidentity(model_p);
}

void sglMRotate(float angle,float x,float y,float z)
{
	float N = sqrt(x*x + y*y + z*z);
	x /= N;
	y /= N;
	z /= N;
	float c = cos(angle*M_PI/180);
	float s = sin(angle*M_PI/180);
	float rot[16] = { x*x*(1-c)+c,   x*y*(1-c)-z*s, x*z*(1-c)+y*s, 0,
		          y*x*(1-c)+z*s, y*y*(1-c)+c,   y*z*(1-c)-x*s, 0,
		          x*z*(1-c)-y*s, y*z*(1-c)+x*s, z*z*(1-c)+c,   0,
		          0,             0,             0,             1 };
	multiply(model_p,rot,model_p);
}

void sglVRotate(float angle,float x,float y,float z)
{
	float N = sqrt(x*x + y*y + z*z);
	x /= N;
	y /= N;
	z /= N;
	float c = cos(angle*M_PI/180);
	float s = sin(angle*M_PI/180);
	float rot[16] = { x*x*(1-c)+c,   x*y*(1-c)-z*s, x*z*(1-c)+y*s, 0,
		          y*x*(1-c)+z*s, y*y*(1-c)+c,   y*z*(1-c)-x*s, 0,
		          x*z*(1-c)-y*s, y*z*(1-c)+x*s, z*z*(1-c)+c,   0,
		          0,             0,             0,             1 };
	multiply(view_p,rot,view_p);
}

void sglVTranslate(float tx,float ty,float tz)
{
	float translate[16] = {	1,0,0,tx,
				0,1,0,ty,
				0,0,1,tz,
				0,0,0,1	};
	multiply(view_p,translate,view_p);
}

void sglLookAt(float camx,float camy,float camz, float refx,float refy,float refz, float upx,float upy,float upz)
{
	float N = sqrt(upx*upx + upy*upy + upz*upz);
	upx /= N;
	upy /= N;
	upz /= N;
	
	float neglookx=camx-refx, neglooky=camy-refy, neglookz=camz-refz;
	N = sqrt(neglookx*neglookx + neglooky*neglooky + neglookz*neglookz);
	neglookx /= N;
	neglooky /= N;
	neglookz /= N;
	
	float c1x, c1y, c1z ;
	c1x = neglookz*upy - neglooky*upz;
	c1y = neglookx*upz - neglookz*upx;
	c1z = neglooky*upx - neglookx*upy;
	N = sqrt(c1x*c1x + c1y*c1y + c1z*c1z);
	c1x /= N;
	c1y /= N;
	c1z /= N;

	float c2x, c2y, c2z;
	c2x = c1z*neglooky - c1y*neglookz;
	c2y = c1x*neglookz - c1z*neglookx;
	c2z = c1y*neglookx - c1x*neglooky;
	N = sqrt(c2x*c2x + c2y*c2y + c2z*c2z);
	c2x /= N;
	c2y /= N;
	c2z /= N;
	
	float lookAt[16] = { c1x,      c1y,      c1z,      0,
			     c2x,      c2y,      c2z,      0,
		             neglookx, neglooky, neglookz, 0,
			     0,        0,        0,        1 };


	multiply(view_p,lookAt,view_p);
	sglVTranslate(-camx,-camy,-camz);
}

void sglVMatrix(float *m)
{
	multiply(view_p,m,view_p);
}

void sglVLoadIdentity()
{
	fillidentity(view_p);
}

void sglProjOrtho(float left,float right,float bottom,float top,float near,float far)
{
	for(int i=0; i<SZ*SZ; i++)
		projection[i] = 0; 

	projection[0]  = 2.0/(right-left);
	projection[5]  = 2.0/(top-bottom);
	projection[10] = 2.0/(far-near);
	projection[3]  = -(right+left)/(right-left);
	projection[7]  = -(top+bottom)/(top-bottom);
	projection[11] = (far+near)/(far-near);
	projection[15] = 1.0;
}

void sglProjFrustum(float left,float right,float bottom,float top,float near,float far)
{
	for(int i=0; i<SZ*SZ; i++)
		projection[i] = 0; 

	projection[0]  = (2.0*near)/(right-left);
	projection[2]  = (right + left) /(right - left);
	projection[5]  = (2.0*near)/(top-bottom);
	projection[6]  = (top + bottom)/(top-bottom);
	projection[10] = (far + near)/(far - near);
	projection[11] = (2.0*far*near)/(far - near);
	projection[14] = -1;
}

void sglViewport(float llx,float lly,float urx,float ury)
{
	for(int i=0; i<16; i++)
		viewPort[i] = 0;
	
	viewPort[0] = (urx - llx)/2.0;
	viewPort[2] = (urx + llx)/2.0;
	viewPort[5] = (ury - lly)/2.0;
	viewPort[6] = (ury + lly)/2.0;
	viewPort[10] = 1;
}

void sglBegin(int x)
{
	triplet t;
	t.x=0; t.y=0; t.z=0; t.what=4;
	Q.push(t);
}

void sglEnd()
{
	triplet t;
	t.x=0; t.y=0; t.z=0; t.what=5;
	Q.push(t);
}

void sglColour(float r,float g,float b)
{
	triplet t;
	t.x=r; t.y=g; t.z=b; t.what=1;
	Q.push(t);
}

void sglClear(float r,float g,float b)
{
	triplet t;
	t.x=r; t.y=g; t.z=b; t.what=2;
	Q.push(t);
}

void sglVertex(float x,float y,float z)
{
	float point[16] = { x,0,0,0,
			    y,0,0,0,
			    z,0,0,0,
			    1,0,0,0 };
	
	multiply(model_p,point,point);
	multiply(view_p,point,point);
	multiply(projection,point,point);
	
	point[8] = point[12];
	point[12] = 0;
	multiply(viewPort,point,point);
	
	triplet t;
	t.x=point[0]; t.y=point[4]; t.z=point[8]; t.what=3;
	if(t.z != 0)
	{
		t.x /= t.z; t.y /= t.z; t.z /= t.z;
	}
	Q.push(t);
}

void sglShow()
{
	triplet t;
	while(!Q.empty())
	{
		t = Q.front();
		Q.pop();
		switch(t.what)
		{
			case 1:
				glColor3f(t.x, t.y, t.z);
				break;
			case 2:
				glClearColor(t.x, t.y, t.z, 1);
				glClear(GL_COLOR_BUFFER_BIT);
				break;
			case 3:
				glVertex2f(t.x, t.y);
				break;
			case 4:
				glBegin(GL_TRIANGLES);
				break;
			case 5:
				glEnd();
				break;
			default:
				printf("wrong switch case");
		}
	}
}
#endif
