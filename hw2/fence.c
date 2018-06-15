
#include "fence.h"
#include "util.h"
#include "primitives.h"
#include "helper.h"
#include <GL/glut.h> //linux
#define GL_GLEXT_PROTOTYPES

//Constants
static double post_height = 2.5;
static double post_width = 0.5;
static double beam_width = 5.0;
static double beam_height = 0.5;
static double beam_length = 0.5; 

static double post_spacing = 2; //units 

//ASSUME A RECTANGULAR FENCE 
void createFence(double x_posts, double y_posts, double max_x, double min_x, double max_y, double min_y){
	//One Edge X
	for (int i = 0; i < x_posts; i++){
		glPushMatrix();
		//move post into position
		printf("The index is %i",i);
		glTranslated(min_x + i*6,min_y,0);
		//create the post
		drawPost();
		glPopMatrix();
	}
	//Other Edge X
	for (int i = 0; i < x_posts; i++){
		glPushMatrix();
		//move post into position
		glTranslated(min_x + i*6,max_y,0);
		//create the post
		drawPost();
		glPopMatrix();
	}
}


void drawBeam(){
	glPushMatrix();
	glScaled(beam_length,beam_width,beam_height);
	drawCube();
	glPopMatrix();
}

void drawPost(){
	glPushMatrix();
	glScaled(post_width,post_width,post_height);
	drawCylinder();
	glPopMatrix();
}