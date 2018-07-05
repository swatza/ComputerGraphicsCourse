/*
* Dancing Cow Test 
*/
//INCLUDES
#define GL_GLEXT_PROTOTYPES

#include "main.h"


int fov=55;       				//  Field of view (for perspective)
double asp=1;     				//  Aspect ratio
double dim=10;//68.0;   		//  Size of world
int mode=1;       				//  Projection mode (Always Perspective)
unsigned int texture[2]; 		// Texture Names

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
* An idle function to run only animate / draw on updated frames.
* NEEDS LOTS OF OPTIMIZATION AND ARCHITECTURE CHANGES
* Original by Willem A. (Vlakkies) Schreuder
*/
void idle()
{
   //  Get elapsed (wall) time in seconds
   double t =  glutGet(GLUT_ELAPSED_TIME)/5000.0; //better way to do this with actual system time so we can do pre-frame drawing calculations
   zh = fmod(90*t,360.0);
   glutPostRedisplay();
   // Do 1 frame a second for now 
   /*
   if (last_time_frame >= 250){
		//reset frame timer
		last_time_frame = 0.0;
		main_new_frame = 1;
		glutPostRedisplay();
   }
   else{
   		main_new_frame = 0;
   		glutPostRedisplay();
   }*/
}

/*
* GLUT Based Main Setup 
* Original by Willem A. (Vlakkies) Schreuder
*/
int main(int argc, char* argv[]){
	printf("Starting!!\n");
	srand(time(0));
	//Initialize GLUT
	glutInit(&argc,argv);
	glutInitWindowSize(600,600);
	//Request double buffer true color window with z buffer (if possible)
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	//Create a window 
	glutCreateWindow("HW3: Spencer Watza"); //name homework assignment: your name
	// Register rendering function, reshaping, and key callbacks
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	//Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);
	//INITIALIZE ALL THE OBJECT MEMORIES
	printf("About to create objects\n");
	createObjects();//rendering.c
	printf("Finished creating objects\n");
	//Load all the textures
	texture[0] = LoadTexBMP("fence_beam_edge.bmp");
	texture[1] = LoadTexBMP("fence_beam_side.bmp");
	texture[2] = LoadTexBMP("fence_post.bmp");
	texture[3] = LoadTexBMP("fence_post_top.bmp");
	texture[4] = LoadTexBMP("grassland.bmp");
	texture[5] = LoadTexBMP("cow_white_black.bmp");
	texture[6] = LoadTexBMP("cow_face_black.bmp");
	printf("Finished loading in textures\n");
	// Pass control to GLUT for events
	glutMainLoop();
	// Return to OS
	cleanObjects();
	return 0; 
}



