#ifndef MAIN_H
#define MAIN_H

//Includes
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h> //linux 
#include "keyboard.h"
#include "rendering.h"
#include "file_loader.h"

//Global Variables
extern int fov;       //  Field of view (for perspective)
extern double asp;     //  Aspect ratio
extern double dim;   //  Size of world
extern int mode;       //  Projection mode
extern double last_time_frame; // time since last new frame
extern int main_new_frame; //flag saying its time to render a new animation key frame
extern int zh;
extern unsigned int texture[];

//Prototypes
void reshape(int width,int height);
void idle();
void animate(int toggle);

#endif
