#ifndef MATERIALS_H
#define MATERIALS_H

//INCLUDES
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h> 		//linux
#include "util.h"

//CONSTANTS

extern float default_ambient[];
extern float default_diffuse[];
extern float default_specular[];
extern float default_emission[];
extern float default_shinny; 

//Prototypes
void setMaterialForFence();
void setMaterialForGrass();
void setMaterialForMetal();
void setMaterialForCow();
void setMaterialForWater();

void setMaterials(int faceFlag, float* ambient, float* diffuse, float* specular, float* emission, float shinny);
void setMaterialShine(float v, int flag);
void setMaterialEmission(float* v, int flag);
void setMaterialSpecular(float* v, int flag);
void setMaterialDiffuse(float* v, int flag);
void setMaterialAmbient(float* v, int flag);

#endif