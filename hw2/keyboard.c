/*
* Keyboard Interface Functions 
*/

#include <GL/glut.h> //linux 
#include "keyboard.h"
#include "rendering.h"
#define GL_GLEXT_PROTOTYPES

/*
* Function called by glut when special keys are pressed: 
* Original by Willem A. (Vlakkies) Schreuder
*/
void special(int key, int x, int y){
	//Right Arrow 
	if (key == GLUT_KEY_RIGHT)
		z_rotation_angle += 2; 
	//Left Arrow
	else if (key == GLUT_KEY_LEFT)
		z_rotation_angle -= 2;
	//Up Arrow

	//Request display update
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

	}
	//Move left
	else if(ch == 'a'){

	}
	//Move Right
	else if(ch == 'd'){

	}
	//Move Backwards
	else if(ch == 's'){

	}
	//Switch View Mode
	if(ch == 1){
		//Switch to aircraft 1
	}
	if(ch == 2){
		//switch to aircraft 2
	}

	//Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}


void mouse(int button, int state, int x, int y){
	//relative mouse buttons and other things...

}
