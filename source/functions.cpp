#include "functions.h"
 
float camX=0.0,camY=0.0,camZ=5.0;
float camYaw=0.0;
float camPitch=0.0;
enum {SKY_LEFT=0,SKY_BACK,SKY_RIGHT,SKY_FRONT,SKY_TOP,SKY_BOTTOM};     
unsigned int skybox[6]; 
#ifndef M_PI
#define M_PI 3.1415926535
#endif
 
void initskybox()
{
        skybox[SKY_LEFT]=loadTexture("data/2k_stars_milky_way.jpg");
        skybox[SKY_BACK]=loadTexture("data/gra1.png");
        skybox[SKY_RIGHT]=loadTexture("data/gra2.png");
        skybox[SKY_FRONT]=loadTexture("data/gra2.png");
        skybox[SKY_TOP]=loadTexture("data/gra2.png");
        skybox[SKY_BOTTOM]=loadTexture("data/gra1.png");
}

void killskybox()
{
        glDeleteTextures(6,&skybox[0]);
}
 
void drawSkybox(float size)
{
        bool b1=glIsEnabled(GL_TEXTURE_2D);    
        glDisable(GL_LIGHTING); 
        glDisable(GL_DEPTH_TEST);       
        glEnable(GL_TEXTURE_2D);        
        glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);  
        glBegin(GL_QUADS);      
                
                glTexCoord2f(0,0);      
                glVertex3f(size/2,size/2,size/2);       
                glTexCoord2f(1,0);      
                glVertex3f(-size/2,size/2,size/2);
                glTexCoord2f(1,1);
                glVertex3f(-size/2,-size/2,size/2);
                glTexCoord2f(0,1);
                glVertex3f(size/2,-size/2,size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
        glBegin(GL_QUADS);     
                
                glTexCoord2f(0,0);
                glVertex3f(-size/2,size/2,size/2);
                glTexCoord2f(1,0);
                glVertex3f(-size/2,size/2,-size/2);
                glTexCoord2f(1,1);
                glVertex3f(-size/2,-size/2,-size/2);
                glTexCoord2f(0,1);
                glVertex3f(-size/2,-size/2,size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
        glBegin(GL_QUADS);     
                
                glTexCoord2f(1,0);
                glVertex3f(size/2,size/2,-size/2);
                glTexCoord2f(0,0);
                glVertex3f(-size/2,size/2,-size/2);
                glTexCoord2f(0,1);
                glVertex3f(-size/2,-size/2,-size/2);
                glTexCoord2f(1,1);
                glVertex3f(size/2,-size/2,-size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
        glBegin(GL_QUADS);     
                
                glTexCoord2f(0,0);
                glVertex3f(size/2,size/2,-size/2);
                glTexCoord2f(1,0);
                glVertex3f(size/2,size/2,size/2);
                glTexCoord2f(1,1);
                glVertex3f(size/2,-size/2,size/2);
                glTexCoord2f(0,1);
                glVertex3f(size/2,-size/2,-size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,skybox[SKY_TOP]);          
        glBegin(GL_QUADS);                      
                glTexCoord2f(1,0);
                glVertex3f(size/2,size/2,size/2);
                glTexCoord2f(0,0);
                glVertex3f(-size/2,size/2,size/2);
                glTexCoord2f(0,1);
                glVertex3f(-size/2,size/2,-size/2);
                glTexCoord2f(1,1);
                glVertex3f(size/2,size/2,-size/2);
        glEnd();
        glBindTexture(GL_TEXTURE_2D,skybox[SKY_BOTTOM]);               
        glBegin(GL_QUADS);     
                
                glTexCoord2f(1,1);
                glVertex3f(size/2,-size/2,size/2);
                glTexCoord2f(0,1);
                glVertex3f(-size/2,-size/2,size/2);
                glTexCoord2f(0,0);
                glVertex3f(-size/2,-size/2,-size/2);
                glTexCoord2f(1,0);
                glVertex3f(size/2,-size/2,-size/2);
        glEnd();
        glEnable(GL_LIGHTING);  
        glEnable(GL_DEPTH_TEST);
        if(!b1)
                glDisable(GL_TEXTURE_2D);
}
 
void lockCamera()
{
        if(camPitch>90)
                camPitch=90;
        if(camPitch<-90)
                camPitch=-90;
        if(camYaw<0.0)
                camYaw+=360.0;
        if(camYaw>360.0)
                camYaw-=360;
}
 
void moveCamera(float dist,float dir)
{
        float rad=(camYaw+dir)*M_PI/180.0;
        camX-=sin(rad)*dist;
        camZ-=cos(rad)*dist;
}
 
void moveCameraUp(float dist,float dir)
{
        float rad=(camPitch+dir)*M_PI/180.0;
        camY+=sin(rad)*dist;   
}
 
void Control(float movevel,float mousevel,bool mi)
{
        if(mi)
        {
                int MidX=320;
                int MidY=240;
                SDL_ShowCursor(SDL_DISABLE);
                int tmpx,tmpy;
                SDL_GetMouseState(&tmpx,&tmpy);
                camYaw+=mousevel*(MidX-tmpx);
                camPitch+=mousevel*(MidY-tmpy);
                lockCamera();
                SDL_WarpMouse(MidX,MidY);
                Uint8* state=SDL_GetKeyState(NULL);
                if(state[SDLK_w])
                {
                        if(camPitch!=90 && camPitch!=-90)
                                moveCamera(movevel,0.0);
                        moveCameraUp(movevel,0.0);
                }else if(state[SDLK_s])
                {
                        if(camPitch!=90 && camPitch!=-90)
                                moveCamera(movevel,180.0);
                        moveCameraUp(movevel,180.0);
                }              
                if(state[SDLK_a])
                        moveCamera(movevel,90.0);
                else if(state[SDLK_d])
                        moveCamera(movevel,270);       
        }
        glRotatef(-camPitch,1.0,0.0,0.0);
        glRotatef(-camYaw,0.0,1.0,0.0);
}
 
void UpdateCamera()
{
        glTranslatef(-camX,-camY,-camZ);
}
 
void drawCube(float size)
{
        float difamb[]={1.0,0.5,0.3,1.0};
        glBegin(GL_QUADS);
                
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,difamb);
                glNormal3f(0.0,0.0,1.0);
                glVertex3f(size/2,size/2,size/2);
                glVertex3f(-size/2,size/2,size/2);
                glVertex3f(-size/2,-size/2,size/2);
                glVertex3f(size/2,-size/2,size/2);
 
                
                glNormal3f(-1.0,0.0,0.0);
                glVertex3f(-size/2,size/2,size/2);
                glVertex3f(-size/2,size/2,-size/2);
                glVertex3f(-size/2,-size/2,-size/2);
                glVertex3f(-size/2,-size/2,size/2);
 
                
                glNormal3f(0.0,0.0,-1.0);
                glVertex3f(size/2,size/2,-size/2);
                glVertex3f(-size/2,size/2,-size/2);
                glVertex3f(-size/2,-size/2,-size/2);
                glVertex3f(size/2,-size/2,-size/2);
 
                
                glNormal3f(1.0,0.0,0.0);
                glVertex3f(size/2,size/2,-size/2);
                glVertex3f(size/2,size/2,size/2);
                glVertex3f(size/2,-size/2,size/2);
                glVertex3f(size/2,-size/2,-size/2);
 
                
                glNormal3f(0.0,1.0,0.0);
                glVertex3f(size/2,size/2,size/2);
                glVertex3f(-size/2,size/2,size/2);
                glVertex3f(-size/2,size/2,-size/2);
                glVertex3f(size/2,size/2,-size/2);
 
                
                glNormal3f(0.0,-1.0,0.0);
                glVertex3f(size/2,-size/2,size/2);
                glVertex3f(-size/2,-size/2,size/2);
                glVertex3f(-size/2,-size/2,-size/2);
                glVertex3f(size/2,-size/2,-size/2);
        glEnd();
}

unsigned int loadTexture(const char* filename)  
{
 unsigned int num;       
        glGenTextures(1,&num); 	
	SDL_Surface* img=IMG_Load(filename); 
        glBindTexture(GL_TEXTURE_2D,num);       
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);      
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);     
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w,img->h,0,GL_RGB,GL_UNSIGNED_SHORT_5_6_5,img->pixels);        
        SDL_FreeSurface(img);   
        return num;     
}


