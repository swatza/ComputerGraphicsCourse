/*
* Homework 1
*/
//INCLUDES
#define GL_GLEXT_PROTOTYPES

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h> //linux 
#include "main.h"
#include "keyboard.h"
#include "rendering.h"

int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=68.0;   //  Size of world
int mode=0;       //  Projection mode

/*
 * This function is called by GLUT when the window is resized
 * Original by Willem A. (Vlakkies) Schreuder
 */

void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Projection();
}

/*
* GLUT Based Main Setup 
* Original by Willem A. (Vlakkies) Schreuder
*/
int main(int argc, char* argv[]){
	srand(time(0));
	//Initialize GLUT
	glutInit(&argc,argv);
	glutInitWindowSize(600,600);
	//Request double buffer true color window with z buffer (if possible)
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//Create a window 
	glutCreateWindow("HW2: Spencer Watza"); //name homework assignment: your name
	// Register rendering function, reshaping, and key callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	//Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);
	//INITIALIZE ALL THE OBJECT MEMORIES
	createObjects();//rendering.c
	// Pass control to GLUT for events
	glutMainLoop();
	// Return to OS
	cleanObjects();
	return 0; 
}



