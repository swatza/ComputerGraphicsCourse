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

//Object Viewer
int obj_viewer = 0; //Cow, Water Container, windmill, Hay Bale, 
int file_counter = 0;

double movespeed = 0.5;
double turn_speed = 1;

int flash_light_toggle = 0;
int dance_party_toggle = 0;

//1st Person Movement
double camera_x = 0;
double camera_y = 0; 
double camera_z = 2; //default height of the camera
double camera_roll = 0;
double camera_pitch = 0;
double camera_yaw = 0;

int changex = 0;
int changey = 0;

int prevx = 300;
int prevy = 300;

//Camera view
int x_rotation_angle = 24;
int y_rotation_angle = 0;
int z_rotation_angle = 10;

int left_knee_angle_x = 0; //q
int left_knee_angle_y = 0; //a
int left_knee_angle_z = 0; //z

int left_ankle_angle_x = 0; //w
int left_ankle_angle_y = 0; //s
int left_ankle_angle_z = 0; //x

int right_knee_angle_x = 0; //e
int right_knee_angle_y = 0; //d
int right_knee_angle_z = 0; //c

int right_ankle_angle_x = 0; //r
int right_ankle_angle_y = 0; //f
int right_ankle_angle_z = 0; //v

int left_hip_angle = 0; //unsure if needed
int right_hip_angle = 0; //unsure if needed

int cow_body_angle = 90; //s / S
int cow_head_angle = 0; //x / X 

int left_elbow_angle_x = 0; //q / Q
int left_elbow_angle_y = 0;
int left_elbow_angle_z = 0;

int right_elbow_angle_x = 0; // e / E
int right_elbow_angle_y = 0;
int right_elbow_angle_z = 0;

int left_wrist_angle_x = 0; // w / W
int left_wrist_angle_y = 0;
int left_wrist_angle_z = 0;

int right_wrist_angle_x = 0; // r / T
int right_wrist_angle_y = 0;
int right_wrist_angle_z = 0;

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
      gluPerspective(fov,asp,dim/16,16*dim);
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
	else if (key == GLUT_KEY_INSERT){
		saveAnimation();
	}
	else if (key == GLUT_KEY_HOME){
		obj_viewer += 1;
		if(obj_viewer == 0)
			dim = 8;
		else if(obj_viewer == 1)
			dim = 8;
		else if(obj_viewer == 2)
			dim = 15;
		else if(obj_viewer == 3)
			dim = 8;
		else if (obj_viewer > 3){
			obj_viewer = 0;
			dim = 8;
		}
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
	else{
		animationKeyTool(ch);
		movementTool(ch);
	}

	Projection();
	//Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

void mouse_clicks(int button, int state, int x, int y){
	//relative mouse buttons and other things...
}

void mouse_movement(int x, int y){
	changex = x - prevx;
	changey = y - prevy;
	prevx = x;
	prevy = y;

	camera_yaw += changex * turn_speed;
	camera_pitch -= changey * turn_speed;
}

void saveAnimation(){
	char buffer[20];
	sprintf(buffer,"KeyFrame_%i.txt",file_counter);
	FILE *out_file = fopen(buffer,"w");
	if(out_file == NULL){
		fprintf(stderr,"Can't open input file %s\n",buffer);
		exit(1);
	}

	fprintf(out_file,"Left Leg: %i, %i; %i, %i\n",left_knee_angle_x,left_knee_angle_y,left_ankle_angle_x,left_ankle_angle_y);
	fprintf(out_file,"Right Leg: %i, %i; %i, %i\n",right_knee_angle_x,right_knee_angle_y,right_ankle_angle_x,right_ankle_angle_y);
	fprintf(out_file,"Left Arm: %i, %i; %i, %i\n",left_elbow_angle_x,left_elbow_angle_y,left_wrist_angle_x,left_wrist_angle_y);
	fprintf(out_file,"Right Arm: %i, %i; %i, %i\n",right_elbow_angle_x,right_elbow_angle_y,right_wrist_angle_x,right_wrist_angle_y);

	//close file
	fclose(out_file);

	//increment file counter
	file_counter += 1;
}

void movementTool(unsigned char ch){
	if(ch == 'w'){
		//move forward
		camera_x += movespeed * cos(deg2rad(camera_yaw));
		camera_y += movespeed * sin(deg2rad(camera_yaw));
	}
	else if(ch == 'a'){
		//move left
		camera_x += movespeed * sin(deg2rad(camera_yaw));
		camera_y -= movespeed * cos(deg2rad(camera_yaw));
	}
	else if(ch == 's'){
		//move backward
		camera_x -= movespeed * cos(deg2rad(camera_yaw));
		camera_y -= movespeed * sin(deg2rad(camera_yaw));
	}
	else if(ch == 'd'){
		//move right
		camera_x -= movespeed * sin(deg2rad(camera_yaw));
		camera_y += movespeed * cos(deg2rad(camera_yaw));
	}
	else if(ch == 'f'){
		flash_light_toggle = 1 - flash_light_toggle;
	}
	else if(ch == 'p'){
		dance_party_toggle = 1 - dance_party_toggle;
	}
}

void animationKeyTool(unsigned char ch){
	//LEFT KNEE
	if (ch == 'q')
		left_knee_angle_x += 1;
	else if (ch == 'Q')
		left_knee_angle_x -= 1;
	else if (ch == 'a')
		left_knee_angle_y += 1;
	else if (ch == 'A')
		left_knee_angle_y -= 1;
	else if (ch == 'z'){
		left_knee_angle_y = 0;
		left_knee_angle_x = 0;
	}
	//LEFT ANKLE
	else if (ch == 'w')
		left_ankle_angle_x += 1;
	else if (ch == 'W')
		left_ankle_angle_x -= 1;
	else if (ch == 's')
		left_ankle_angle_y += 1;
	else if (ch == 'S')
		left_ankle_angle_y -= 1;
	else if (ch == 'x'){
		left_ankle_angle_x = 0;
		left_ankle_angle_y = 0;
	}
	//RIGHT KNEE
	else if (ch == 'e')
		right_knee_angle_x += 1;
	else if (ch == 'E')
		right_knee_angle_x -= 1;
	else if (ch == 'd')
		right_knee_angle_y += 1;
	else if (ch == 'D')
		right_knee_angle_y -= 1;
	else if (ch == 'c'){
		right_knee_angle_x = 0;
		right_knee_angle_y = 0;
	}
	//RIGHT ANKLE
	else if (ch == 'r')
		right_ankle_angle_x += 1;
	else if (ch == 'R')
		right_ankle_angle_x -= 1;
	else if (ch == 'f')
		right_ankle_angle_y += 1;
	else if (ch == 'F')
		right_ankle_angle_y -= 1;
	else if (ch == 'v'){
		right_ankle_angle_x = 0;
		right_ankle_angle_y = 0;
	}
	//Left ELBOW
	else if (ch == 't')
		left_elbow_angle_x += 1;
	else if (ch == 'T')
		left_elbow_angle_x -= 1;
	else if (ch == 'g')
		left_elbow_angle_y += 1;
	else if (ch == 'G')
		left_elbow_angle_y -= 1;
	else if (ch == 'b'){
		left_elbow_angle_x = 0;
		left_elbow_angle_y = 0;
	}
	//Left WRIST
	else if (ch == 'y')
		left_wrist_angle_x += 1;
	else if (ch == 'Y')
		left_wrist_angle_x -= 1;
	else if (ch == 'h')
		left_wrist_angle_y += 1;
	else if (ch == 'H')
		left_wrist_angle_y -= 1;
	else if (ch == 'n'){
		left_wrist_angle_x = 0;
		left_wrist_angle_y = 0;
	}
	//RIGHT ELBOW
	else if (ch == 'u')
		right_elbow_angle_x += 1;
	else if (ch == 'U')
		right_elbow_angle_x -= 1;
	else if (ch == 'j')
		right_elbow_angle_y += 1;
	else if (ch == 'J')
		right_elbow_angle_y -= 1;
	else if (ch == 'm'){
		right_elbow_angle_x = 0;
		right_elbow_angle_y = 0;
	}
		
	//RIGHT WRIST
	else if (ch == 'i')
		right_wrist_angle_x += 1;
	else if (ch == 'I')
		right_wrist_angle_x -= 1;
	else if (ch == 'k')
		right_wrist_angle_y += 1;
	else if (ch == 'K')
		right_wrist_angle_y -= 1;
	else if (ch == ','){
		right_wrist_angle_x = 0;
		right_wrist_angle_y = 0;
	}

		//Modulate them down to 360
	right_wrist_angle_x %= 360;
	right_wrist_angle_y %= 360;
	right_wrist_angle_z %= 360;

	left_wrist_angle_x %= 360;
	left_wrist_angle_y %= 360;
	left_wrist_angle_z %= 360;

	right_elbow_angle_x %= 360;
	right_elbow_angle_y %= 360;
	right_elbow_angle_z %= 360;

	left_elbow_angle_x %= 360;
	left_elbow_angle_y %= 360;
	left_elbow_angle_z %= 360;

	right_ankle_angle_x %= 360;
	right_ankle_angle_y %= 360;
	right_ankle_angle_z %= 360;

	left_ankle_angle_x %= 360;
	left_ankle_angle_y %= 360;
	left_ankle_angle_z %= 360;

	right_knee_angle_x %= 360;
	right_knee_angle_y %= 360;
	right_knee_angle_z %= 360;

	left_knee_angle_x %= 360;
	left_knee_angle_y %= 360;
	left_knee_angle_z %= 360;
}