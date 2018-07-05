
#include "fence.h"
#include "util.h"
#include "primitives.h"
#include "helper.h"
#include <GL/glut.h> //linux
#define GL_GLEXT_PROTOTYPES

//Constants
const static double post_height = 7.0;
const static double post_width = 0.5;
const static double beam_width = 5.0;
const static double beam_height = 0.5;
const static double beam_length = 0.5; 

const static double post_spacing = 20; //units 

/*
* Create a fence bounding a box
*/
void createFence(int x_posts, int y_posts, double max_x, double min_x, double max_y, double min_y, unsigned int postT1, unsigned int postT2, unsigned int beamT1, unsigned int beamT2){
	//X EDGE POSTS
	for (int i = 0; i < x_posts; i++){
		glPushMatrix();
		//move post into position
		glTranslated(min_x + i*post_spacing,min_y,-post_height/2);
		//create the post
		drawPost(postT1, postT2);
		glPopMatrix();
		glPushMatrix();
		//move post into position
		glTranslated(min_x + i*post_spacing,max_y,-post_height/2);
		//create the post
		drawPost(postT1, postT2);
		glPopMatrix();
	} 
	//X EDGE BEAMS
	for (int i = 0; i < x_posts -1; i++){
		glPushMatrix();
		glTranslated(min_x + post_spacing/2 + i*post_spacing,min_y,-2.5);
		glRotated(90,0,0,1.0);
		drawBeam(beamT1, beamT2);
		glTranslated(0,0,-2.5);
		drawBeam(beamT1, beamT2);
		glPopMatrix();

		glPushMatrix();
		glTranslated(min_x + post_spacing/2 + i*post_spacing,max_y,-2.5);
		glRotated(90,0,0,1.0);
		drawBeam(beamT1, beamT2);
		glTranslated(0,0,-2.5);
		drawBeam(beamT1, beamT2);
		glPopMatrix();
	}

	//Y EDGE POSTS (do't render the corners since they are already drawn)
	for (int i = 1; i < y_posts-1; i++){
		glPushMatrix();
		glTranslated(min_x,min_y + i*post_spacing,-post_height/2);
		drawPost(postT1, postT2);
		glPopMatrix();

		glPushMatrix();
		glTranslated(max_x,min_y + i*post_spacing,-post_height/2);
		drawPost(postT1, postT2);
		glPopMatrix();
	}
	//Y EDGE BEAMS
	for (int i = 0; i < y_posts -1; i++){
		glPushMatrix();
		glTranslated(min_x,min_y + post_spacing/2 + i*post_spacing,-2.5);
		drawBeam(beamT1, beamT2);
		glTranslated(0,0,-2.5);
		drawBeam(beamT1, beamT2);
		glPopMatrix();

		glPushMatrix();
		glTranslated(max_x,min_y + post_spacing/2 + i*post_spacing,-2.5);
		drawBeam(beamT1, beamT2);
		glTranslated(0,0,-2.5);
		drawBeam(beamT1, beamT2);
		glPopMatrix();
	}

}

/*
* Draw a fence beam
*/
void drawBeam(unsigned int beamside, unsigned int beamtop){
	glPushMatrix();
	//Scale all the following points correctly?
	glScaled(beam_length,beam_width,beam_height);
	float rep = 2;
	glBindTexture(GL_TEXTURE_2D,beamtop);
	//Draw 2x4 Edges (LEFT)
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0.0,1.0); glVertex3f(+1,-1,+1);
	glTexCoord2f(0.0,0.0); glVertex3f(+1,-1,-1);
	glTexCoord2f(rep,0.0); glVertex3f(+1,+1,-1);
	glTexCoord2f(rep,1.0); glVertex3f(+1,+1,+1);
	glEnd();
	//RIGHT
	glBegin(GL_QUADS);
	glNormal3f(-1,0,0);
	glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,-1);
	glTexCoord2f(0.0,1.0); glVertex3f(-1,-1,+1);
	glTexCoord2f(rep,1.0); glVertex3f(-1,+1,+1);
	glTexCoord2f(rep,0.0); glVertex3f(-1,+1,-1);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, beamside);
	//Draw Top/Bottom, and Front/Back
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0.0,rep); glVertex3f(-1,+1,+1);
	glTexCoord2f(rep,rep); glVertex3f(+1,+1,+1);
	glTexCoord2f(rep,0.0); glVertex3f(+1,+1,-1);
	glTexCoord2f(0.0,0.0); glVertex3f(-1,+1,-1);
	glEnd();
	//  Bottom
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,-1);
	glTexCoord2f(rep,0.0); glVertex3f(+1,-1,-1);
	glTexCoord2f(rep,rep); glVertex3f(+1,-1,+1);
	glTexCoord2f(0.0,rep); glVertex3f(-1,-1,+1);
	glEnd();
	//  Front
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0,0.0); glVertex3f(-1,-1, 1);
	glTexCoord2f(1.0,0.0); glVertex3f(+1,-1, 1);
	glTexCoord2f(1.0,1.0); glVertex3f(+1,+1, 1);
	glTexCoord2f(0.0,1.0); glVertex3f(-1,+1, 1);
	glEnd();
	//  Back
	glBegin(GL_QUADS);
	glNormal3f(0,0,-1);
	glTexCoord2f(1.0,0.0); glVertex3f(+1,-1,-1);
	glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,-1);
	glTexCoord2f(0.0,1.0); glVertex3f(-1,+1,-1);
	glTexCoord2f(1.0,1.0); glVertex3f(+1,+1,-1);
	glEnd();
	
	glPopMatrix();
	ErrCheck("Draw Fence Beam");
}

/* 
* Draw a fence Post
*/
void drawPost(unsigned int postSide, unsigned int postTop){
	glPushMatrix();
	
	glScaled(post_width,post_width,post_height);
	
	//Draw Top (we don't need the draw the bottom bit)
	const int d = 5;
	int th;
	double h = 1; int r = 1; double* xyz;
	
	glBindTexture(GL_TEXTURE_2D, postTop);
	//Draw Top
	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0,0,1);
	glTexCoord2f(0.5,0.5); glVertex3f(0,0,h/2);
	//Loop through
	for(th = 0; th<=360;th+=d){
		xyz = polar2cartesianCoords(r,th);
		glNormal3f(0,0,1);
		glTexCoord2f(0.5+0.5*xyz[0], 0.5+0.5*xyz[1]); glVertex3f(xyz[0],xyz[1],h/2);
	}
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, postSide);
	//Draw Side
	glBegin(GL_QUAD_STRIP);
	for(th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r,th);
		glNormal3f(xyz[0],xyz[1],0);
		glTexCoord2f(th/360,1.0); glVertex3f(xyz[0],xyz[1],h/2);
		glTexCoord2f(th/360,0.0); glVertex3f(xyz[0],xyz[1],-h/2);
	}
	glEnd();
	
	glPopMatrix();
	ErrCheck("Draw Fence Post");
}

