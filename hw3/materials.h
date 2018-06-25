#ifndef MATERIALS_H
#define MATERIALS_H

//INCLUDES
#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h> 		//linux
#include "util.h"

//CONST
const static float default_ambient[4] = {0.2,0.2,0.2,1.0};
const static float default_diffuse[4] = {0.8,0.8,0.8,1.0};
const static float default_specular[4] = {0.0,0.0,0.0,1.0};
const static float default_emission[4] = {0.0,0.0,0.0,1.0};
const static int default_shinny = 0;

//Prototypes
void setMaterials(int faceFlag, float* ambient, float* diffuse, float* specular, float* emission, int shinny);
void setMaterialShine(int v);
void setMaterialEmission(float* v);
void setMaterialSpecular(float* v);
void setMaterialDiffuse(float* v);
void setMaterialAmbient(float* v);

#endif