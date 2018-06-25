
//INCLUDES
#include "materials.h"

/*
* Function to set the material properties of an object for lighting
*/

void setMaterials(int faceFlag, float* ambient, float* diffuse, float* specular, float* emission, int shinny){
	//Ambient
	setMaterialAmbient(ambient);
	//Diffuse
	setMaterialDiffuse(diffuse);
	//Specular
	setMaterialSpecular(specular);
	//Emission
	setMaterialEmission(emission);
	//Shinness
	setMaterialShine(shinny);
}

void setMaterialShine(int v){
	glMaterialfv(GL_FRONT,GL_SHININESS, v);
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