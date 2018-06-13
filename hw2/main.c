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

/*
 * This function is called by GLUT when the window is resized
 * Original by Willem A. (Vlakkies) Schreuder
 */
void reshape(int width,int height)
{
	const double dim=5.0;
	//double dim = zoom_scale;
   //  Calculate width to height ratio
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set viewport as entire window
   glViewport(0,0, width,height);
   //  Select projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Set projection to identity
   glLoadIdentity();
   //  Orthogonal projection:  unit cube adjusted for aspect ratio
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   //  Select model view matrix
   glMatrixMode(GL_MODELVIEW);
   //  Set model view to identity
   glLoadIdentity();
}

/*
* GLUT Based Main Setup 
* Original by Willem A. (Vlakkies) Schreuder
*/
int main(int argc, char* argv[]){
	//Initialize GLUT
	glutInit(&argc,argv);
	glutInitWindowSize(600,600);
	//Request double buffer true color window with z buffer (if possible)
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//Create a window 
	glutCreateWindow("HW1: Spencer Watza"); //name homework assignment: your name
	// Register rendering function, reshaping, and key callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	//Enable Z-buffer depth test
	//glEnable(GL_DEPTH_TEST);
	// Pass control to GLUT for events
	glutMainLoop();
	// Return to OS
	return 0; 
}



