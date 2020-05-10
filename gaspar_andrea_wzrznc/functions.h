#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <cmath>
#ifndef FUNCTION_H
#define FUNCTION_H


void drawCube(float size);
void drawSkybox(float size);
void initskybox();
void killskybox();
void lockCamera();
void moveCamera(float, float);
void moveCameraUp(float, float);
void Control(float, float, bool);
void UpdateCamera();
unsigned int loadTexture(const char*);

#endif
