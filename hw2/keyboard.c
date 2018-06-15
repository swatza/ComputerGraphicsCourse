/*
* Keyboard Interface Functions 
*/

#include <math.h>
#include <GL/glut.h> //linux 
#include "main.h"
#include "keyboard.h"
#include "util.h"
#include "rendering.h"
#define GL_GLEXT_PROTOTYPES

int x_rotation_angle = 0;
int z_rotation_angle = 0;
int angle1 = 0;
int angle2 = 0;
int view_mode = 0; //0 = overhead/god mode, 1 = aircraft 1, 2 = aircraft 2, 3 = first person
double camera_x = 0;
double camera_y = 0; 
double camera_z = 1; //default height of the camera
double camera_roll = 0;
double camera_pitch = 0;
double camera_yaw = 0;

static double movespeed = 1;
static double turnspeed = 1;

/*
 *  Set projection
 */
void Projection()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (mode)
      gluPerspective(fov,asp,dim/4,4*dim);
   //  Orthogonal projection
   else
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}


/*
* Function called by glut when special keys are pressed: 
* Original by Willem A. (Vlakkies) Schreuder
*/
void special(int key, int x, int y){
	//Right Arrow 
	if (key == GLUT_KEY_RIGHT)
		x_rotation_angle += 2; 
	//Left Arrow
	else if (key == GLUT_KEY_LEFT)
		x_rotation_angle -= 2;
	//Up Arrow
	else if (key == GLUT_KEY_UP){
		z_rotation_angle += 2;
	}
	else if (key == GLUT_KEY_DOWN){
		z_rotation_angle -= 2;
	}
	else if (key == GLUT_KEY_HOME){
		if (mode == 0){
			mode = 1;
		}
		else if (mode == 1){
			mode = 0;
		}
	}
	//Request display update
	Projection();
	glutPostRedisplay();
}

/*
* GLUT Calls this routine when a key is pressed (not special keys)
* Original by Willem A. (Vlakkies) Schreuder
*/
void key(unsigned char ch, int x, int y){
	//Exit on ESC
	if(ch == 27)
		exit(0);
	//reset view position and parameters
	else if (ch == 'r'){

	}
	//Move Forward in 1st Person
	else if(ch == 'w'){
		//move the camera location 
		//camera_x += movespeed * cos(deg2rad(camera_yaw));
		angle1 += 2;
	}
	//Turn Left
	else if(ch == 'a'){
		//camera_yaw += turnspeed;
		angle2 += 2;
	}
	//Turn Right
	else if(ch == 'd'){
		//camera_yaw -= turnspeed;
		angle2 -= 2;
	}
	//Move Backwards
	else if(ch == 's'){
		//camera_y += movespeed * sin(deg2rad(camera_yaw));
		angle1 -= 2;
	}
	//Switch View Mode
	//Switch to first person mode
	else if(ch == 0){
		view_mode = 0;
	}
	else if(ch == 1){
		//Switch to aircraft 1
		view_mode = 1;
	}
	else if(ch == 2){
		//switch to aircraft 2
		view_mode = 2;
	}
	else if(ch == 'p'){
		view_mode = 3;
	}
	//Dealing with FOV
	else if (ch == '-' && ch>1)
		fov--;
	else if (ch == '+' && ch<179)
		fov++;
	Projection();
	//Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y){
	//relative mouse buttons and other things...

}
