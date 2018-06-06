/*
* Keyboard Interface Functions 
*/

#include <GL/glut.h> //linux 

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
	//Request display update
	glutPostRedsiplay();
}