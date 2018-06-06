/*
* openGL Rendering functions with minor GLUT involvement
*/

//Includes
#include <stdio.h>
#include <GL/glut.h> //linux 
#include "rendering.h"

//Global Variables
double z_rotation_angle = 0;
double x_rotation_angle = 0;

/*
* Function called by GLUT to display/render the scene
* original by professor
*/
void display(){
	//Clear the screen and Z buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//reset transformations
	glLoadIdentity();
	//Rotate the desired objects
	glRotatef(z_rotation_angle,0.0,0.0,1.0);
	//Rotate the desired objects
	glRotatef(x_rotation_angle,1.0,0.0,0.0);
	//Draw the desired objects 
	drawPyramid();
	//Error Check
	ErrCheck("display");
	//flush and swap buffer
	glFlush();
	glutSwapBuffers();
}

void drawPyramid(){
	//Draw 4 triangles that are Red, Green, Blue, Yellow
	//Three side faces (Not an equalateral pyramid atm)
	glBegin(GL_POLYGON);
	glColor3f(1.0,0.0,0); glVertex3f(-0.5,0.5,0);
	glColor3f(1.0,0.0,0); glVertex3f(0.5,0.5,0);
	glColor3f(1.0,0.0,0); glVertex3f(0.0,0.0,0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0,1.0,0); glVertex3f(-0.5,0.5,0);
	glColor3f(0.0,1.0,0); glVertex3f(0.0,-0.5,0);
	glColor3f(0.0,1.0,0); glVertex3f(0.0,0.0,0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0,0.0,1.0); glVertex3f(0.5,0.5,0);
	glColor3f(0.0,0.0,1.0); glVertex3f(0.0,-0.5,0);
	glColor3f(0.0,0.0,1.0); glVertex3f(0.0,0.0,0.5);
	glEnd();
	//Bottom
	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,0); glVertex3f(-0.5,0.5,0);
	glColor3f(1.0,1.0,0); glVertex3f(0.5,0.5,0);
	glColor3f(1.0,1.0,0); glVertex3f(0.0,-0.5,0.0);
	glEnd();
	ErrCheck("DrawPyramid");
}

/*
* GL Basic Error Check Function
* Original by Professor
*/
void ErrCheck(char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}
