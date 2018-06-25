
//Includes
#include "lighting.h"


GLenum lightEnumerations[] = {GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3};
//Default values
const float default_light_ambient[] = {0.0,0.0,0.0,1.0};
const float default_light_diffuse[] = {0.0,0.0,0.0,1.0};
const float default_light_diffuse_and_specular_0[] = {1.0,1.0,1.0,1.0};
const float default_light_specular[] = {0.0,0.0,0.0,1.0};

//Create an object to keep track of the parameters for the spotlight; initialize to defaults
//Make sure to enable the light beforehand
createLightObj(struct *light my_light_ptr, GLenum lightObj){
	struct light my_light = *my_light_ptr;
	my_light.thisLight = lightObj;
	memcpy(my_light.ambient, default_light_ambient, sizeof(default_light_ambient));
	//If this works, repeat for the others!!! 
	//If its light0, make sure to set the defaults being different
	*my_light_ptr = my_light;
}

//Set a new light position for a light pointer
void moveLightPosition(struct light* my_light_ptr, struct vector3 new_position){
	struct light my_light = *my_light_ptr;
	my_light.position[0] = new_position.x;
	my_light.position[1] = new_position.y;
	my_light.position[2] = new_position.z;
	*my_light_ptr = my_light;
}

void moveLightSpotDirection(struct light* my_light_ptr, float* v){
	struct light my_light = *my_light_ptr;
	//copy over the values in memory?
	memcpy(my_light.spot_direction, v, sizeof(v));
	*my_light_ptr = my_light;
}

//Functions to set the colors of the struct?; is there another way to do this? 
void makeLightAmbient(struct light* my_light_ptr, float* v){
	struct light my_light = *my_light_ptr;
	//copy over the values in memory?
	memcpy(my_light.ambient, v, sizeof(v));
	*my_light_ptr = my_light;
}

void makeLightDiffuse(struct light* my_light_ptr, float*v){
	struct light my_light = *my_light_ptr;
	//copy over the values in memory?
	memcpy(my_light.diffuse, v, sizeof(v));
	*my_light_ptr = my_light;
}

void makeLightSpecular(struct light* my_light_ptr, float*v){
	struct light my_light = *my_light_ptr;
	//copy over the values in memory?
	memcpy(my_light.specular, v, sizeof(v));
	*my_light_ptr = my_light;
}

//Enable this light
void performLighting(struct light* my_light_ptr){
	struct light this_light = *my_light_ptr;
	//enable the light
	glEnable(this_light.thisLight;
	//set each of the values
	setLightAmbient(this_light.thisLight, this_light.ambient);
	setLightDiffuse(this_light.thisLight, this_light.diffuse);
	setLightSpecular(this_light.thisLight, this_light.specular);
	setLightPosition(this_light.thisLight, this_light.position);
	//if this is a spot light, set the direciton 
	if(light.position[3] == 1){
		setLightSpotDirection(this_light.thisLight, this_light.spot_direction);
	}
}

void setLightSpecular(GLenum mylight, float* v){
	glLightfv(mylight, GL_SPECULAR, v);
}

void setLightDiffuse(GLenum mylight, float* v){
	glLightfv(mylight, GL_DIFFUSE, v);
}

void setLightAmbient(GLenum mylight, float* v){
	glLightfv(mylight, GL_AMBIENT, v);
}

void setLightPosition(GLenum mylight, float* v){
	glLightfv(mylight, GL_POSITION, v);
}

void setLightSpotDirection(GLenum mylight, float* v){
	glLightfv(mylight, GL_SPOT_DIRECTION, v);
}