#ifndef LIGHTING_H
#define LIGHTING_H

#define GL_GLEXT_PROTOTYPES
#include <GL/glut.h> 		//linux
#include "util.h"

//global variables
extern GLenum lightEnumerations[];

//Struct definitions
typedef struct light light;

//Prototypes
void createLightObj(struct light* my_light_ptr, GLenum lightObj);
void moveLightPosition(struct light* my_light_ptr, struct vector3 new_position);
void moveLightSpotDirection(struct light* my_light_ptr, float* v);
void makeLightAmbient(struct light* my_light_ptr, float* v);
void makeLightDiffuse(struct light* my_light_ptr, float*v);
void makeLightSpecular(struct light* my_light_ptr, float*v);
void performLighting(struct light* my_light_ptr);
void setLightSpecular(GLenum mylight, float* v);
void setLightDiffuse(GLenum mylight, float* v);
void setLightAmbient(GLenum mylight, float* v);
void setLightPosition(GLenum mylight, float* v);
void setLightSpotDirection(GLenum mylight, float* v);

//Struct Implementation
struct light{
	float ambient[4];
	float diffuse[4];
	float specular[4];
	float position[4];
	float spot_direction[3];
	GLenum thisLight;
	int On;
	//Shape object?
};

#endif