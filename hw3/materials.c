
//INCLUDES
#include "materials.h"

/*
* Function to set the material properties of an object for lighting
*/

void setMaterials(int faceFlag, float* ambient, float* diffuse, float* specular, float* emission, float shinny){
	//printf("Inside Set Materials\n");
	//Ambient
	setMaterialAmbient(ambient);
	//printf("Set ambient material\n");
	//Diffuse
	setMaterialDiffuse(diffuse);
	//Specular
	setMaterialSpecular(specular);
	//Emission
	setMaterialEmission(emission);
	//printf("Set Emission Material\n");
	//Shinness
	setMaterialShine(shinny);
	//printf("Set Shiny Material\n");
}

void setMaterialShine(float v){
	glMaterialf(GL_FRONT,GL_SHININESS, v);
}

void setMaterialEmission(float* v){
	glMaterialfv(GL_FRONT,GL_EMISSION, v);
}

void setMaterialSpecular(float* v){
	glMaterialfv(GL_FRONT,GL_SPECULAR, v);
}

void setMaterialDiffuse(float* v){
	glMaterialfv(GL_FRONT, GL_DIFFUSE, v);
}

void setMaterialAmbient(float* v){
	glMaterialfv(GL_FRONT, GL_AMBIENT, v);
}