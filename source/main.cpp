#include "functions.h"
#include "objloader.h"
#include <iostream>
using namespace std;
 
int planet_textureID;
int cube;
objloader obj;

void init()
{
        float col[]={1.0,1.0,1.0,1.0};

        glClearColor(0.5,0.5,0.5,1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(450,640.0/480.0,1.0,500.0);
        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);

	planet_textureID=obj.loadTexture("data/sun.jpg");
        cube=obj.load("data/jupiter.obj",planet_textureID);
	
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
        initskybox();
}

void display(float _angle, float _light, bool _mousein)
{
	float pos[]={-1.0,1.0,-2.0,1.0};
        glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glLightfv(GL_LIGHT0,GL_POSITION,pos); 
	GLfloat ambient[] = { _light, _light, _light, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	drawSkybox(50.0);
	glTranslatef(0.0,0.0,-5.0);
	glRotatef(_angle,0.0,0.0,10.0);
        Control(0.6,0.4,_mousein);       
	UpdateCamera();
	glBindTexture(GL_TEXTURE_2D,planet_textureID);
	glCallList(cube);
}

int main()
{
	float angle=0.0;
	float light = 0.1;
	bool mousein=false;

	cout << "Irányítás: W-A-S-D / egér\n";
	cout << "Pause: P\n";
	cout << "Fényerő: + és -\n";
	cout << "Kilépés: ESC.\n";
	cout << "Gáspár Andrea WZRZNC\n";
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Surface* screen=SDL_SetVideoMode(1024,768,32,SDL_SWSURFACE|SDL_OPENGL);
        bool running=true;
        Uint32 start;
        SDL_Event event;

        init();

        while(running)
        {
                start=SDL_GetTicks();
                while(SDL_PollEvent(&event))
                {
                        switch(event.type)
                        {
                                case SDL_QUIT:
                                        running=false;
                                        break;
                                case SDL_MOUSEBUTTONDOWN:
                                        mousein=true;
                                        SDL_ShowCursor(SDL_DISABLE);
                                        break;
                                case SDL_KEYDOWN:
                                        if(event.key.keysym.sym==SDLK_p)
                                        {
                                                mousein=false;
                                                SDL_ShowCursor(SDL_ENABLE);
                                                break;
                                        }
                                        if(event.key.keysym.sym==SDLK_ESCAPE)
                                        {
                                                running=false;
                                                break;
                                        }
					switch (event.key.keysym.sym)
					{
					case SDLK_KP_PLUS:
					light += 0.1f;
					break;

					case SDLK_KP_MINUS:
					light -=0.1f;
					break;
					}
                        }
                }
                display(angle, light, mousein);
                SDL_GL_SwapBuffers();
                angle+=0.5;
                if(angle>360)
                        angle-=360;
                if(1000/30>(SDL_GetTicks()-start))
                        SDL_Delay(1000/30-(SDL_GetTicks()-start));
        }
        SDL_Quit();
        killskybox();
        return 0;       	
}

