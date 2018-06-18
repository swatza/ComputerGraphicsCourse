
#include "fence.h"
#include "util.h"
#include "primitives.h"
#include "helper.h"
#include <GL/glut.h> //linux
#define GL_GLEXT_PROTOTYPES

//Constants
static double post_height = 7.0;
static double post_width = 0.5;
static double beam_width = 5.0;
static double beam_height = 0.5;
static double beam_length = 0.5; 

static double post_spacing = 10; //units 

/*
* Create a fence bounding a box
*/
void createFence(int x_posts, int y_posts, double max_x, double min_x, double max_y, double min_y){
	//X EDGE POSTS
	for (int i = 0; i < x_posts; i++){
		glPushMatrix();
		//move post into position
		glTranslated(min_x + i*post_spacing,min_y,-post_height/2);
		//create the post
		drawPost();
		glPopMatrix();
		glPushMatrix();
		//move post into position
		glTranslated(min_x + i*post_spacing,max_y,-post_height/2);
		//create the post
		drawPost();
		glPopMatrix();
	} 
	//X EDGE BEAMS
	for (int i = 0; i < x_posts -1; i++){
		glPushMatrix();
		glTranslated(min_x + post_spacing/2 + i*post_spacing,min_y,-2.5);
		glRotated(90,0,0,1.0);
		drawBeam();
		glTranslated(0,0,-2.5);
		drawBeam();
		glPopMatrix();

		glPushMatrix();
		glTranslated(min_x + post_spacing/2 + i*post_spacing,max_y,-2.5);
		glRotated(90,0,0,1.0);
		drawBeam();
		glTranslated(0,0,-2.5);
		drawBeam();
		glPopMatrix();
	}

	//Y EDGE POSTS (do't render the corners since they are already drawn)
	for (int i = 1; i < y_posts-1; i++){
		glPushMatrix();
		glTranslated(min_x,min_y + i*post_spacing,-post_height/2);
		drawPost();
		glPopMatrix();

		glPushMatrix();
		glTranslated(max_x,min_y + i*post_spacing,-post_height/2);
		drawPost();
		glPopMatrix();
	}
	//Y EDGE BEAMS
	for (int i = 0; i < y_posts -1; i++){
		glPushMatrix();
		glTranslated(min_x,min_y + post_spacing/2 + i*post_spacing,-2.5);
		drawBeam();
		glTranslated(0,0,-2.5);
		drawBeam();
		glPopMatrix();

		glPushMatrix();
		glTranslated(max_x,min_y + post_spacing/2 + i*post_spacing,-2.5);
		drawBeam();
		glTranslated(0,0,-2.5);
		drawBeam();
		glPopMatrix();
	}

}

/*
* Draw a fence beam
*/
void drawBeam(){
	glPushMatrix();
	glScaled(beam_length,beam_width,beam_height);
	drawCube();
	glPopMatrix();
}

/* 
* Draw a fence Post
*/
void drawPost(){
	glPushMatrix();
	glScaled(post_width,post_width,post_height);
	drawCylinder();
	glPopMatrix();
}