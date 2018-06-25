#ifndef PRIMITIVES_H
#define PRIMITIVES_H

//Includes
#define GL_GLEXT_PROTOTYPES
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glut.h> //linux 

//Prototypes
void drawVertex(double th,double ph);
void drawPlanewTexture(unsigned int texture);
void drawCube();
void drawPyramid();
void drawCylinder();
void drawSphere();
void drawEllipsoid(double a, double b, double c);


#endif