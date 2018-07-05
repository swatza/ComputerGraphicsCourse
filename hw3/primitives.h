#ifndef PRIMITIVES_H
#define PRIMITIVES_H

//Includes
#define GL_GLEXT_PROTOTYPES
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glut.h> //linux 

//Prototypes
void drawVertex(double th,double ph, float s, int mode);
void drawPlanewTexture(unsigned int text);
void drawCube();
void drawPyramid();
void drawCylinder();
void drawPipewTexture(int unsigned text);
void drawSpherewTexture(unsigned int text);
void drawEllipsoidwTexture(double a, double b, double c,unsigned int text, int mode);


#endif