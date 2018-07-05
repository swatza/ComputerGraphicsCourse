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

//God mode camera variables
int x_rotation_angle = 24;
int y_rotation_angle = 0;
int z_rotation_angle = 10;

int view_mode = 0; //0 = overhead/god mode, 1st Person
int axis_on = 1;

int sceneflag = 0; //daylight - night-time
// texture and lighting flag to turn on
int textureFlag = 1;
int lightingOn = 1;
int flashlightFlag = 0;

//1st Person Camera Variables
double camera_x = 0;
double camera_y = 0; 
double camera_z = -5; //default height of the camera
double camera_roll = 0;
double camera_pitch = 0;
double camera_yaw = 0;

static double movespeed = 1;
static double turnspeed = 2.5;

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
	//Down Arrow
	else if (key == GLUT_KEY_DOWN){
		z_rotation_angle -= 2;
	}
	//Scene Change
	else if (key == GLUT_KEY_HOME){
		sceneflag = 1 - sceneflag;
	}
	//Keep within 360
	x_rotation_angle %= 360;
	z_rotation_angle %= 360;
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
	//reset view position,parameters and animation
	else if (ch == 'r'){
		//TODO!
	}
	//Move Forward in 1st Person
	else if(ch == 'w'){
		//move the camera location 
		if(view_mode){
			camera_x += movespeed * cos(deg2rad(camera_yaw));
			camera_y += movespeed * sin(deg2rad(camera_yaw));
		}
		//angle1 += 2;
	}
	//Turn Left
	else if(ch == 'a'){
		if(view_mode){
			camera_yaw -= turnspeed;
		}
		//angle2 += 2;
	}
	//Turn Right
	else if(ch == 'd'){
		if(view_mode){
			camera_yaw += turnspeed;
		}
		//angle2 -= 2;
	}
	//Move Backwards
	else if(ch == 's'){
		if(view_mode){
			camera_x -= movespeed * cos(deg2rad(camera_yaw));
			camera_y -= movespeed * sin(deg2rad(camera_yaw));
		}
		//angle1 -= 2;
	}
	//toggle axis
	else if(ch == 'm'){
		axis_on = 1 - axis_on;
	}
	//toggle lighting
	else if(ch == 'l'){
		lightingOn = 1 - lightingOn;  
	}
	//Toggle texture
	else if(ch == 't'){
		textureFlag = 1 - textureFlag;
	}
	else if(ch == 'f'){
		flashlightFlag = 1 - flashlightFlag;
	}
	//Dealing with FOV
	else if (ch == '-' && ch>1)
		fov--;
	else if (ch == '+' && ch<179)
		fov++;
	//Switch View Mode
	//Switch to first person mode

	if(mode){
		if(ch == '0'){
			view_mode = 1 - view_mode;
		}
	}
	Projection();
	//Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y){
	//relative mouse buttons and other things...

}
