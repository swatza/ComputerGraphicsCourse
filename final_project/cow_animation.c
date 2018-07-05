/*
* Dancing Cow Test 
*/
//INCLUDES
#define GL_GLEXT_PROTOTYPES

#include "main.h"
#include "scene_1.h"
#include "cow.h"


int fov=55;       				//  Field of view (for perspective)
double asp=1;     				//  Aspect ratio
double dim=25.0;//68.0;   		//  Size of world
int mode=0;       				//  Projection mode (Always Perspective)
unsigned int texture[21]; 		// Texture Names
int zh = 90; 

double time_since = 0;
double time_start = 0;
int frame_time_threshold = 500;
int next_frame_ready = 0;

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

void idle()
{
   //  Get elapsed (wall) time in seconds
   double t =  glutGet(GLUT_ELAPSED_TIME)/5000.0; //better way to do this with actual system time so we can do pre-frame drawing calculations
   zh = fmod(90*t,360.0);
   glutPostRedisplay();
}

//Function to prep animation frames

void animate(int toggle){
	//Initialize the timer again:
	if(toggle) 
		glutTimerFunc(50,animate,1);
	//Do the animation calculations
	//printf("Calculating Next Frame\n");
	calculateScene1Animations();
	//Redsiplay
	//printf("Drawing Next Frame\n");
	glutPostRedisplay();

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
	glutCreateWindow("Cow Animation Tool"); //name homework assignment: your name
	// Register rendering function, reshaping, and key callbacks
	glutDisplayFunc(displayScene1); mode = 1;
	//glutDisplayFunc(display); glutIdleFunc(idle); mode = 0;
	
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(key);
	//glutMotionFunc(mouse_movement);
	glutPassiveMotionFunc(mouse_movement);
	glutWarpPointer(300,300);
	//Enable Z-buffer depth test
	glEnable(GL_DEPTH_TEST);
	//INITIALIZE ALL THE OBJECT MEMORIES
	printf("About to create objects\n");
	//CREATE ANIMATION KEY FRAME OBJS
	createWalkingFrames();
	createStandingFrame();
	createDancingFrame();
	//CREATE OTHER OBJS
	createObjects();//rendering.c
	createScene1Objects();
	printf("Finished creating objects\n");
	//Load all the textures
	texture[0] = LoadTexBMP("cow_white_black.bmp");
	texture[1] = LoadTexBMP("cow_face_black.bmp");
	texture[2] = LoadTexBMP("hay_edge.bmp");
	texture[3] = LoadTexBMP("hay_face.bmp");
	texture[4] = LoadTexBMP("rusted_metal_plate.bmp");
	texture[5] = LoadTexBMP("scratched_metalic_texture.bmp");
	texture[6] = LoadTexBMP("metalic_texture.bmp"); 
	texture[7] = LoadTexBMP("metal_tube_texture_w_rivets.bmp");
	texture[8] = LoadTexBMP("water.bmp");
	texture[9] = LoadTexBMP("metal_beam.bmp");
	texture[10] = LoadTexBMP("metal_beam_rivet_side.bmp");
	texture[11] = LoadTexBMP("top_skybox.bmp");
	texture[12] = LoadTexBMP("bottom_skybox.bmp");
	texture[13] = LoadTexBMP("face1_skybox.bmp");
	texture[14] = LoadTexBMP("face2_skybox.bmp");
	texture[15] = LoadTexBMP("face34_skybox.bmp");
	texture[16] = LoadTexBMP("grassland.bmp");
	texture[17] = LoadTexBMP("fence_beam_edge.bmp");
	texture[18] = LoadTexBMP("fence_beam_side.bmp");
	texture[19] = LoadTexBMP("fence_post.bmp");
	texture[20] = LoadTexBMP("fence_post_top.bmp");
	printf("Finished loading in textures\n");
	// Pass control to GLUT for events
	animate(1);
	glutMainLoop();
	// Return to OS
	cleanObjects();
	return 0; 
}



