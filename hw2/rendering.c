/*
* openGL Rendering functions with minor GLUT involvement
*/

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GL/glut.h> //linux 
#include "rendering.h"
#include "keyboard.h"
#include "util.h"
#include "primitives.h"
#include "cow.h"
#include "helper.h"
#include "main.h"
#define GL_GLEXT_PROTOTYPES

//Global Variables
int number_of_cows = 3;
struct cow_object **cows; //list of cow objects

/*
* Function called by GLUT to display/render the scene
* original by Willem A. (Vlakkies) Schreuder
*/
void display(){
	//double* output = malloc(size*sizeof(double));
	//Clear the screen and Z buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//reset transformations
	glLoadIdentity();
	//Rotate the desired objects
	if (mode){
		//PERSPECTIVE
		double Ex = -2*dim*sin(deg2rad(x_rotation_angle))*cos(deg2rad(z_rotation_angle));
		double Ey = +2*dim*sin(deg2rad(z_rotation_angle));
		double Ez = +2*dim*cos(deg2rad(x_rotation_angle))*cos(deg2rad(z_rotation_angle));
		gluLookAt(Ex,Ey,Ez,0,0,0,0,cos(deg2rad(z_rotation_angle)),0);
	}
	else{
		//ORTHOGONAL 
		glRotatef(z_rotation_angle,1.0,0.0,0.0);
		glRotatef(x_rotation_angle,0.0,0.0,1.0);
	}
	//Translate based on scale desired
	//Draw the desired objects
	//drawAxis();
	createFence(2,2,10,-10,10,-10);
	//Print Angles;
	printAngles();
	//Error Check
	ErrCheck("display");
	//flush and swap buffer
	glFlush();
	glutSwapBuffers();
}

void drawAxis(){
	//default length
	double len = 1.5;
	//set color
	glColor3f(1,1,1); //whte
	//Draw the 3 axeses
	glBegin(GL_LINES);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(len,0.0,0.0);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(0.0,len,0.0);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(0.0,0.0,len);
	glEnd();
	//Label Axes
	glRasterPos3d(len,0.0,0.0);
	Print("X");
	glRasterPos3d(0.0,len,0.0);
	Print("Y");
	glRasterPos3d(0.0,0.0,len);
	Print("Z");
	ErrCheck("drawAxis");
}

/*
//Create my rendering objects
void createObjects(){
	//How many cows do we want to create
	//for i in number of cows
	for (int i = 0; i < number_of_cows; i++){
		//Initialize a cow object into memory
		struct cow_object * mycow = malloc(sizeof(struct cow_object));
		//Initialize the values for said cow object
		initializeCowObject(mycow);
		//create a cow object structure
		//initialize it into memory
		//add the address to the object to a global pointer of objects
	}
		//create a cow object structure
		//Initialize it into memory
		//add this location in memory to my pointer of objects
	//How many airplanes do we want to create

	//How many ... 
} */

/*
* Used to print out the rotation angles in the bottom left 
* Original by Willem A. (Vlakkies) Schreuder
*/
void printAngles(){
	//Five pixels from lower left corner of window
	glWindowPos2i(5,5);
	//Print the text string
	Print("Angle=%f,%f",x_rotation_angle,z_rotation_angle); 
}

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 *  Original by Willem A. (Vlakkies) Schreuder
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format, ...){
	char    buf[LEN];
	char*   ch=buf;
	va_list args;
	//  Turn the parameters into a character string
	va_start(args,format);
	vsnprintf(buf,LEN,format,args);
	va_end(args);
	//  Display the characters one at a time at the current raster position
	while (*ch)
	  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}
