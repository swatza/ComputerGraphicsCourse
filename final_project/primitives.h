#ifndef PRIMITIVES_H
#define PRIMITIVES_H

//Includes
#define GL_GLEXT_PROTOTYPES
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glut.h> //linux 

//Globals

//Prototypes
void drawVertex(double th,double ph, float s, int mode);
void drawPlanewTexture(unsigned int text);
void drawCube();
void drawPyramid();
void drawCylinder();
void drawCylinderFacewTexture(int unsigned text);
void drawPipewTexture(int unsigned text, float rep);
void drawPipe();
void drawSpherewTexture(unsigned int text);
void drawSphere();
void drawEllipsoidwTexture(double a, double b, double c,unsigned int text, int mode);
void drawEllipsoid(double a, double b, double c);
void drawSkyBoxModified(double dimension, unsigned int face1, unsigned int face2, unsigned int face34, unsigned int face5, unsigned int face6);
//void drawSkyBox(unsigned int face1, unsigned int face2, unsigned int face3, unsigned int face4, unsigned int face5, unsigned int face6);

#endif