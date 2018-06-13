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
#define GL_GLEXT_PROTOTYPES

//Global Variables
int number_of_points = 10000; 
//double *vertex; //= malloc(sizeof(double) * 3); //3 doubles indicate a vertex
//double **points;// = malloc(sizeof(*double) * number_of_points * sizeof(vertex));


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
	glRotatef(z_rotation_angle,1.0,0.0,0.0);
	//Rotate the desired objects
	glRotatef(x_rotation_angle,0.0,1.0,0.0);
	//Translate based on scale desired
	//Draw the desired objects 
	//**** TODO -> Optimization could be done here ****
	//double* vals = getLorenzPoints(number_of_points);
	//draw3DLine(vals,number_of_points);
	drawOval(0,0,0,2);
	//Print Angles;
	printAngles();
	//Error Check
	ErrCheck("display");
	//flush and swap buffer
	glFlush();
	glutSwapBuffers();
}

void drawTerrainMesh(double* x, double* y, double* z, int size){
	int i;
	//loop through and generate one of the points of the mesh
	glBegin(GL_TRIANGLE_STRIP);
	for (i = 0; i < size; i++){
		glColor3f(1.0,1.0,1.0); //white
		glVertex3d(x[i],y[i],z[i]); //assign the x,y,z positions to the vertex; 
	}
	glEnd();
	ErrCheck("Draw Terrain Mesh");
}

void drawVertex(double th,double ph){
	//Draw Polar vertex
	double* xyz = spherical2cartesianCoords(1,th,ph,0,0,0);
	glColor3f(xyz[2],sin(deg2rad(ph)) * sin(deg2rad(ph)), sin(deg2rad(th)) * sin(deg2rad(th)));
	glVertex3f(xyz[0],xyz[1],xyz[2]);
}

/*
* Draw a 3D oval extended version of a sphere
* Based on Professors' sphere1 version 
*/
void drawOval(double cx,double cy, double cz, double r){
	const int d=5; //spacing on angles
	int th,ph;

	//Save transformation
	glPushMatrix();
	//offset and scale
	glTranslated(cx,cy,cz);
	glScaled(r,r,r);

	for (ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
         drawVertex(th,ph);
         drawVertex(th,ph+d);
      }
      glEnd();
   }
	

	//Undo transformations
	glPopMatrix();

}

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

/*
* GL Basic Error Check Function
* Original by Willem A. (Vlakkies) Schreuder
*/
void ErrCheck(char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}
