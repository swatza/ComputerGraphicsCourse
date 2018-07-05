
//INCLUDES
#include "materials.h"

float default_ambient[4] = {0.2,0.2,0.2,1.0};
float default_diffuse[4] = {0.8,0.8,0.8,1.0};
float default_specular[4] = {0.0,0.0,0.0,1.0};
float default_emission[4] = {0.0,0.0,0.0,1.0};
float default_shinny = 0;

static float metal_ambient[4] = {0.01,0.01,0.01,1.0};
static float metal_diffuse[4] = {0.2,0.2,0.2,1.0};
static float metal_specular[4] = {0.5,0.5,0.5,1.0};
static float metal_emission[4] = {0.0,0.0,0.0,1.0};
//static float metal_shinny = 10;
static float rusted_metal_shinny = 5;

static float cow_ambient[4] = {0.0,0.0,0.0,1.0};
static float cow_diffuse[4] = {0.4,0.4,0.4,1.0}; 
static float cow_specular[4] = {0.0,0.0,0.0,1.0};
static float cow_emission[4] = {0.0,0.0,0.0,1.0};

//For grass and hay
static float grass_ambient[4] = {0.0,0.0,0.0,1.0};
static float grass_diffuse[4] = {0.2,0.2,0.2,1.0};
static float grass_specular[4] = {0.3,0.3,0.3,1.0};
static float grass_emission[4] = {0.1,0.1,0.1,1.0};

static float water_ambient[4] = {0.1,0.1,0.1,1.0};
static float water_diffuse[4] = {0.8,0.8,0.8,1.0};
static float water_specular[4] = {0.8,0.8,0.8,1.0};
static float water_emission[4] = {0.1,0.1,0.1,1.0};

static float fence_ambient[4] = {0.01,0.01,0.01,1.0};
static float fence_diffuse[4] = {0.7,0.7,0.7,1.0};
static float fence_specular[4] = {0.1,0.1,0.1,1.0};
static float fence_emission[4] = {0.0,0.0,0.0,1.0};
static int fence_shiny = 0;

/*
* Function to set the material properties of an object for lighting
*/
void setMaterialForFence(){
	setMaterials(0,fence_ambient,fence_diffuse,fence_specular,fence_emission,fence_shiny);
}

void setMaterialForGrass(){
	setMaterials(1,grass_ambient,grass_diffuse,grass_specular,grass_emission,default_shinny);
}

void setMaterialForMetal(){
	setMaterials(1,metal_ambient,metal_diffuse,metal_specular,metal_emission,rusted_metal_shinny);
}

void setMaterialForCow(){
	setMaterials(1,cow_ambient,cow_diffuse,cow_specular,cow_emission,default_shinny);
}

void setMaterialForWater(){
	setMaterials(1,water_ambient,water_diffuse,water_specular,water_emission,default_shinny);
}

void setMaterials(int faceFlag, float* ambient, float* diffuse, float* specular, float* emission, float shinny){
	//printf("Inside Set Materials\n");
	//Ambient
	setMaterialAmbient(ambient,faceFlag);
	//printf("Set ambient material\n");
	//Diffuse
	setMaterialDiffuse(diffuse,faceFlag);
	//Specular
	setMaterialSpecular(specular,faceFlag);
	//Emission
	setMaterialEmission(emission,faceFlag);
	//printf("Set Emission Material\n");
	//Shinness
	setMaterialShine(shinny,faceFlag);
	//printf("Set Shiny Material\n");
}

void setMaterialShine(float v, int flag){
	if(flag)
		glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,v);
	else
		glMaterialf(GL_FRONT,GL_SHININESS, v);
}

void setMaterialEmission(float* v, int flag){
	if(flag)
		glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,v);
	else
		glMaterialfv(GL_FRONT,GL_EMISSION, v);
}

void setMaterialSpecular(float* v, int flag){
	if(flag)
		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,v);
	else
		glMaterialfv(GL_FRONT,GL_SPECULAR, v);
}

void setMaterialDiffuse(float* v, int flag){
	if(flag)
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,v);
	else
		glMaterialfv(GL_FRONT, GL_DIFFUSE, v);
}

void setMaterialAmbient(float* v, int flag){
	if(flag)
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,v);
	else
		glMaterialfv(GL_FRONT, GL_AMBIENT, v);
}