/*
* Keyboard Interface Functions 
*/

#include <GL/glut.h> //linux 
#include "keyboard.h"
#include "lorenz.h"
#include "rendering.h"

//TODO! Need to add extra buttons to change the parameters of the lorenz function 
int variable_selector = 0;
int scale = 0; 
double lorenz_parameter_s  = 10;
double lorenz_parameter_b  = 2.6666;
double lorenz_parameter_r  = 28;
double z_rotation_angle = 0;
double x_rotation_angle = 0;

/*
* Function called by glut when special keys are pressed: 
* Original by Professor 
*/
void special(int key, int x, int y){
	//Right Arrow 
	if (key == GLUT_KEY_RIGHT)
		z_rotation_angle += 2; 
	//Left Arrow
	else if (key == GLUT_KEY_LEFT)
		z_rotation_angle -= 2;
	//Up Arrow
	if (key == GLUT_KEY_UP)
		x_rotation_angle += 2;
	//Down Arrow
	if (key == GLUT_KEY_DOWN)
		x_rotation_angle -= 2;
	//Page Up
	if (key == GLUT_KEY_HOME){
		if (variable_selector == 0)
			lorenz_parameter_s += 1;
		if (variable_selector == 1)
			lorenz_parameter_b += 1;
		if (variable_selector == 2)
			lorenz_parameter_r += 1;
		if (variable_selector == 3)
			scale += 1;
	}
	//Page Down
	if (key == GLUT_KEY_END){
		if (variable_selector == 0)
			lorenz_parameter_s -= 1;
		if (variable_selector == 1)
			lorenz_parameter_b -= 1;
		if (variable_selector == 2)
			lorenz_parameter_r -= 1;
		if (variable_selector == 3)
			scale -= 1;
	}
	//INSERT
	if (key == GLUT_KEY_INSERT){
		//Rotate through the different possible variables 
		variable_selector += 1;
		//If its bigger than the variable number; go back to 0
		if (variable_selector > 3)
			variable_selector = 0; 
	}
	//TODO Put limits on the scale and parameters
	x_rotation_angle %= 360;
	z_rotation_angle %= 360;
	//Request display update
	glutPostRedisplay();
}
