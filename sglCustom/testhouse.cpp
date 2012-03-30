#include<math.h>
#include<SDL/SDL.h>
#include<SDL/SDL_opengl.h>
#include "sgl.h"   //whatever your file name is
#include "homeIGL.h"

#define PI 3.142

void drawplane()
{
	sglColour(0.5,0.7,0.5);
	sglBegin(1);
	sglVertex(-200,-50,-200);
	sglVertex(200,-50,-200);
	sglVertex(200,-50,200);
	sglEnd();
	sglBegin(1);
	sglVertex(200,-50,200);
	sglVertex(-200,-50,200);
	sglVertex(-200,-50,-200);
	sglEnd();
}

int main(void)
{
	initialize();
	int height=480,width=640;
	bool fullscreen=false,freeze=false,up=false,close=false;
	double camangle=0,camangle2=0,var_r=0;
	SDL_Init( SDL_INIT_VIDEO );
	SDL_WM_SetCaption( "Test 2 - Clipping, Graphics Made By Pawan Harish", NULL );
	int nFlags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE | SDL_HWSURFACE | SDL_HWACCEL;
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER,1);
	SDL_Surface *pSDLSurface = SDL_SetVideoMode(width,height,16, nFlags );

	sglViewport(width/4,height/4, width/2, height/2);
	glViewport(0,0, width, height);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	sglProjOrtho(width/4, width/2, width/4, width/2,0,500);
	gluOrtho2D ( width/4, width/2, width/4, width/2 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	//GLfloat x = (GLfloat)width / height;

	double cx=20,cy=150,cz=350;

	double r=sqrt(pow(cx,2)+pow(cz,2)+pow(cz,2));
	double th=double(atan(double(cy)/double(r))*180)/double(PI);
	double phi=double(atan(double(cx)/double(-cz))*180)/double(PI);
	sglMLoadIdentity();
	sglVLoadIdentity();
	bool Done = false;
	SDL_Event Event;
	while(!Done)
	{
		SDL_PollEvent(&Event);
		switch(Event.type)
		{
			case SDL_QUIT:
				Done=true;
				break;
			case SDL_KEYDOWN:
				if(Event.key.keysym.sym==SDLK_ESCAPE)
					Done=true;
				else
					if(Event.key.keysym.sym=='s'&&!freeze)
					{
						if(!fullscreen)
						{
							pSDLSurface=SDL_SetVideoMode(width,height,16, nFlags|SDL_FULLSCREEN);
							fullscreen=true;
						}	
						else
						{
							pSDLSurface=SDL_SetVideoMode(width,height,16, nFlags);
							fullscreen=false;
						}
					}
					else
						if(Event.key.keysym.sym=='f')freeze=true;
						else
							if(Event.key.keysym.sym=='r')freeze=false;
				break;
		}
		if(!freeze)
		{
			sglClear(0,0,0);
			//My drawings
			camangle+=2;
			if(camangle>360)camangle=0;

			if(up)camangle2+=0.25;
			else
				camangle2-=0.25;
			if(camangle2>=30)up=false;
			if(camangle2<=-30)up=true;

			if(close)var_r+=2;
			else
				var_r-=2;
			if(var_r>=200)close=false;
			if(var_r<=-200)close=true;


			sglVLoadIdentity();
		//	sglOCamera(-x, x, -1.0, 1.0, 4.0, 2000.0); 
			sglProjOrtho(-60, 130, -60, 130, -60, 130); 
			sglVTranslate(0,0,-r+var_r);
			sglVRotate(-camangle2+th,1,0,0);
			sglVRotate(-camangle+phi,0,1,0);


			drawplane();
			sglMPushMatrix();
			sglMLoadIdentity();
			sglMTranslate(0,0,-50);
			DrawHome();
			sglMPopMatrix();

			sglShow(); //show everything made up till now in IGL.
			SDL_GL_SwapBuffers(); 
		}
	}
	SDL_Quit();
	return 0;
} 
