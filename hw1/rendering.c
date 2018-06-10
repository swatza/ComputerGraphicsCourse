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
#include "lorenz.h"
#define GL_GLEXT_PROTOTYPES

//Global Variables
int number_of_points = 100; 
//double *vertex; //= malloc(sizeof(double) * 3); //3 doubles indicate a vertex
//double **points;// = malloc(sizeof(*double) * number_of_points * sizeof(vertex));

/*
* Function called by GLUT to display/render the scene
* original by professor
*/
void display(){
	//double* output = malloc(size*sizeof(double));
	//Clear the screen and Z buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//reset transformations
	glLoadIdentity();
	//Rotate the desired objects
	glRotatef(z_rotation_angle,0.0,0.0,1.0);
	//Rotate the desired objects
	glRotatef(x_rotation_angle,1.0,0.0,0.0);
	// Check to see if any parameters changed and we need to recalculate all the points 
		//If there are changes; recalculate lorenz function 
		//how do we store the points that we need to render each time? 
	//Draw the desired objects 
	double* vals = getLorenzPoints(number_of_points);
	draw3DLine(vals,number_of_points);
	//Draw Axis
	drawAxis();
	//Print Angles;
	printAngles();
	//Print variables
	printVariables();
	//Error Check
	ErrCheck("display");
	//flush and swap buffer
	glFlush();
	glutSwapBuffers();
}

void draw3DLine(double* values, int size){
	int i; int k;
	double location[3];
	//printf("The first value is %f\n",*values);
	glBegin(GL_LINE_STRIP); //should draw N-1 lines based on N vertices
	for (i = 0; i < size; i++){
		//printf("About to get the vertex location\n");
		location[0] = (values[i*3]);
		location[1] = (values[i*3+1]);
		location[2] = (values[i*3+2]);
		//printf("About to draw the vertex\n");
		glColor3f(1.0,1.0,0); glVertex3d(location[0],location[1],location[2]);
	}
	glEnd(); 
	ErrCheck("draw3DLine");
}

void drawAxis(){
	//default length
	double len = 1.5;
	//set color
	glColor3f(1,1,1); //white
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

void printAngles(){
	//Five pixels from lower left corner of window
	glWindowPos2i(5,5);
	//Print the text string
	Print("Angle=%f,%f",x_rotation_angle,z_rotation_angle); 
}

void printVariables(){
	//get window size
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	//Print out the variables in upper left corner
	glWindowPos2i(5,height-15);
	//In a top -down fashion
	Print("Parameter s: %f",lorenz_parameter_s);
	glWindowPos2i(5,height-35);
	Print("Parameter b: %f",lorenz_parameter_b);
	glWindowPos2i(5,height-55);
	Print("Parameter r: %f",lorenz_parameter_r);
	glWindowPos2i(5,height-75);
	Print("Scale Parameter: %d", scale);
	//Mark which one is selected (Change color??)
	
	//For debugging print out the selector number too
	glWindowPos2i(5,height-95);
	Print("Selector: %d",variable_selector);
}

void drawPyramid(){
	//Draw 4 triangles that are Red, Green, Blue, Yellow
	//Three side faces (Not an equalateral9pyramid atm)
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
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 *  Original by Professor 
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

/*
* GL Basic Error Check Function
* Original by Professor
*/
void ErrCheck(char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}
