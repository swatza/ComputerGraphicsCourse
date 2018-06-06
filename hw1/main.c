/*
* Homework 1
*/
//INCLUDES
#define GL_GLEXT_PROTOTYPES

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <GL/glut.h> //linux 
#include "keyboard.h"
#include "rendering.h"

//Included Global Variables from other files 
extern double z_rotation_angle;
extern double x_rotation_angle;

/*
 * This function is called by GLUT when the window is resized
 * Original by Professor
 */
void reshape(int width,int height)
{
   //  Calculate width to height ratio
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set viewport as entire window
   glViewport(0,0, width,height);
   //  Select projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Set projection to identity
   glLoadIdentity();
   //  Orthogonal projection:  unit cube adjusted for aspect ratio
   glOrtho(-w2h,+w2h, -1.0,+1.0, -1.0,+1.0);
   //  Select model view matrix
   glMatrixMode(GL_MODELVIEW);
   //  Set model view to identity
   glLoadIdentity();
}

/*
* GLUT Based Main Setup 
* Original by Professor
*/
int main(int argc, char* argv[]){
	//Initialize GLUT
	glutInit(&argc,argv);
	//Request double buffer true color window with z buffer (if possible)
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//Create a window 
	glutCreateWindow("HW1: Spencer Watza"); //name homework assignment: your name
	// Register rendering function, reshaping, and key callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	//Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);
	// Pass control to GLUT for events
	glutMainLoop();
	// Return to OS
	return 0; 
}



