/*
* Draw the outdoors scene that has a fence, grass
*
*/

#include "scene_1.h"
#include "materials.h"

//Objects to store all of the related information
/*struct cow_object ** scene_1_cows; 
struct windmill_object ** windmills;
struct fence_object ** fences;
struct person_object * person; */

//Global variables for Objects
int number_of_haybales = 20;
int number_of_cows_scene1 = 10;
struct cow_object** scene_1_cows;
double* haybale_x;
double* haybale_z;
double* haybale_yaw;

//Global variables for animation
int sub_frame_number = 0;
int key_frame_spacing = 5;

double PH = 0;
double TH = 0;
double TH_Step = 1;


void displayScene1(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//reset transformations
	glLoadIdentity();

	//Set as first person view mode
	/*
	double LAH_X = 1 * cos(deg2rad(camera_yaw)) + camera_x;
	double LAH_Y = 1 * sin(deg2rad(camera_yaw)) + camera_y;
	double LAH_Z = camera_z; */
	//camera_yaw = x_rotation_angle;
	double LAH_X = 1 * cos(deg2rad(camera_yaw)) + camera_x;
	double LAH_Z = 1 * sin(deg2rad(camera_yaw)) + camera_y;
	double LAH_Y = 1 * sin(deg2rad(camera_pitch))+ camera_z;
	gluLookAt(camera_x,camera_z,camera_y,LAH_X,LAH_Y,LAH_Z,0,cos(deg2rad(z_rotation_angle)),0);

	//Lighting -> Sky
	//Copy Code from previous assignment
	float light_ambient[] = {0.0,0.0,0.0,1.0}; //yellowish-white light?
	float light_diffuse[] = {0.8,0.8,0.8,1.0}; //default
	float light_specular[] = {0.1,0.1,0.1,1.0}; //default

	float flashlight_ambient[] = {0,0,0,1.0};
	float flashlight_diffuse[] = {1,1,1,1};
	float flashlight_specular[] = {0.5,0.5,0.5,1.0};
	//normalize normal vectors
	glEnable(GL_NORMALIZE);		
	//Enable 
	glEnable(GL_LIGHTING);
	//Location of viewer for specular calculations
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1); 
	//  glColor sets ambient and diffuse color materials
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //Set Global Light Parameters
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_AMBIENT ,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE ,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	float light_position[] = {0,2,1,0}; //should be a directional source from way up - can be slightly tweaked
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	//Set Flash light
	if(flash_light_toggle){
		float Direction[] = {cos(deg2rad(camera_yaw)),sin(deg2rad(camera_pitch)),sin(deg2rad(camera_yaw))};
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_AMBIENT, flashlight_ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, flashlight_diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, flashlight_specular);
		float light_position1[] = {camera_x*1.0,camera_z*1.0,camera_y*1.0,1};
		glLightfv(GL_LIGHT1, GL_POSITION,light_position1);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION,Direction);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,60);
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,16);
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION ,1);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION   ,0.02);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION,0.01);
	}
	else
		glDisable(GL_LIGHT1);

	if(dance_party_toggle){
		float redlight_diffuse[] = {1.0,0,0,1.0};
		float bluelight_diffuse[] = {0,0,1.0,1};
		float purplelight_diffuse[] = {0.0,1,0.0,1.0};

		float light_position2[] = {15,15,15,1};
		float light_position3[] = {-15,15,15,1};
		float light_position4[] = {0,15,-15,1};

		float Direction2[] = {-1,-1,-1};
		float Direction3[] = {1,-1,-1};
		float Direction4[] = {0,-1,1};

		//Enable
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHT4);

		//Set 
		glLightfv(GL_LIGHT2, GL_DIFFUSE, redlight_diffuse);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, bluelight_diffuse);
		glLightfv(GL_LIGHT4, GL_DIFFUSE, purplelight_diffuse);

		glLightfv(GL_LIGHT2, GL_POSITION,light_position2);
		glLightfv(GL_LIGHT3, GL_POSITION,light_position3);
		glLightfv(GL_LIGHT4, GL_POSITION,light_position4);

		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION,Direction2);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION,Direction3);
		glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION,Direction4);

		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF,60);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF,60);
		glLightf(GL_LIGHT4, GL_SPOT_CUTOFF,60);

		glLightf(GL_LIGHT2, GL_SPOT_EXPONENT,1);
		glLightf(GL_LIGHT3, GL_SPOT_EXPONENT,1);
		glLightf(GL_LIGHT4, GL_SPOT_EXPONENT,1);

		//Put all cows into standing mode
		for (int i = 0; i < number_of_cows_scene1; i ++){
			scene_1_cows[i]->isStanding = 1;
			scene_1_cows[i]->move_type = 2;
		}
	}
	else{
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		glDisable(GL_LIGHT4);

		//Put all cows into normal mode
		for (int i = 0; i < number_of_cows_scene1; i ++){
			scene_1_cows[i]->isStanding = 0;
			scene_1_cows[i]->move_type = 1;
		}
	}

	glShadeModel(GL_SMOOTH);
	//Textures On
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//Create Skybox
	drawSkyBoxModified(dim,texture[13],texture[14],texture[15],texture[11],texture[12]); //insert the 6 textures (or can we just use 1)?
	
	//Draw the grass ground
	glPushMatrix();
	glRotated(90,1.0,0.0,0.0);
	glColor3f(0.5,0.5,0.5);
	//glScaled(200,200,1);
	//Set the materials
	setMaterialForGrass();
	//drawPlanewTexture(texture[16]);
	drawGroundPlanewTexture(texture[16],20,40,40);
	glPopMatrix(); 

	//Draw the Fence
	/*
	glPushMatrix();
	glRotated(90,1.0,0.0,0.0);
	setMaterialForFence();
	createFence(11,11,200,-200,200,-200,texture[19],texture[20],texture[17],texture[18]);
	glPopMatrix(); */

	//====================
	//Draw the windmill(s)
	//====================
	//Windmill 1 and Water Container 1
	glPushMatrix();
	glTranslated(35,0,15);
	glRotated(-90,1,0,0);
	glRotated(40,0,0,1);
	drawWindmill(texture[10],texture[9],texture[7],texture[4],texture[6],texture[5]);
	glPopMatrix(); 

	glPushMatrix();
	glTranslated(20,0,15);
	glRotated(-90,1,0,0);
	glScaled(2,2,1);
	drawWaterContainer(texture[5],texture[4],texture[6]);
	drawWater(texture[8]);
	glPopMatrix();

	//Water Container 2
	glPushMatrix();
	glTranslated(-48,0,-77);
	glRotated(-90,1,0,0);
	glScaled(2,2,1);
	drawWaterContainer(texture[5],texture[4],texture[6]);
	drawWater(texture[8]);
	glPopMatrix();

	//Windmill 2 and 3
	glPushMatrix();
	glTranslated(-122,0,88);
	glRotated(-90,1,0,0);
	glRotated(113,0,0,1);
	drawWindmill(texture[10],texture[9],texture[7],texture[4],texture[6],texture[5]);
	glPopMatrix(); 

	glPushMatrix();
	glTranslated(122,0,-65);
	glRotated(-90,1,0,0);
	drawWindmill(texture[10],texture[9],texture[7],texture[4],texture[6],texture[5]);
	glPopMatrix(); 

	//Draw Hay Bales
	for (int i = 0; i < number_of_haybales; i++){
		glPushMatrix();
		glTranslated(haybale_x[i],2,haybale_z[i]);
		glScaled(.35,.35,.5);
		glRotated(-90,0,0,1);
		glRotated(haybale_yaw[i],1,0,0);
		setMaterialForGrass();
		drawHayBale(texture[3],texture[2]);
		glPopMatrix();
	}

	//Draw all the cows
	for (int i = 0; i < number_of_cows_scene1; i ++){
		glPushMatrix();
		if(scene_1_cows[i]->isStanding){
			drawDancingCow(scene_1_cows[i]->skeleton, texture[0],texture[1]); 
		}
		else{
			drawCow(scene_1_cows[i]->skeleton, texture[0],texture[1]); 
		}
		glPopMatrix();
	}

	glDisable(GL_TEXTURE_2D);
	drawAxis();

	//Error Check
	ErrCheck("scene_1");
	//flush and swap buffer
	glFlush();
	glutSwapBuffers();
}

void createScene1Objects(){
	//Create HayBale Locations
	haybale_x = malloc(sizeof(double)*number_of_haybales);
	haybale_z = malloc(sizeof(double)*number_of_haybales);
	haybale_yaw = malloc(sizeof(double)*number_of_haybales);
	for (int i = 0; i < number_of_haybales; i++){
		haybale_x[i] = random_at_most(400) - 200; 
		haybale_z[i] = random_at_most(400) - 200; 
		haybale_yaw[i] = random_at_most(360);
	}
	//How many cows do we want to create
	scene_1_cows = (struct cow_object**)malloc(sizeof(struct cow_object*)*number_of_cows_scene1);
	//for i in number of cows
	for (int i = 0; i < number_of_cows_scene1; i++){
		//Initialize a cow object into memory
		struct cow_object *my_cow_ptr = (struct cow_object*)malloc(sizeof(struct cow_object));
		//Initialize the values for said cow object
		initializeCowObject(my_cow_ptr,i);
		//create a cow object structure
		scene_1_cows[i] = my_cow_ptr;
	}
}

//For now leave this empty
void calculateScene1Animations(){
	//increment sub frame number
	int key_frame_shift_flag = 0;
	sub_frame_number += 1;
	if (sub_frame_number == key_frame_spacing){
		//restart counter
		sub_frame_number = 0;
		//incremet keyframe
		key_frame_shift_flag = 1;
	}
	//Determine which skeleton to draw
	for(int i = 0; i < number_of_cows_scene1; i++){
		//Do frame calculations
		determineFrameToDraw(scene_1_cows[i],key_frame_shift_flag,key_frame_spacing,sub_frame_number);
		//Do skeleton calculations
		calculateCowSkeleton(scene_1_cows[i]->frame_to_draw, scene_1_cows[i]);
	}
}

//For now leave this empty
void calculateScene1Collisions2D(){
	return;
}

void drawGroundPlanewTexture(unsigned int text, int spacing, int xsize, int ysize){
	glBindTexture(GL_TEXTURE_2D,text);
	glBegin(GL_QUADS);
	for (int i = 0; i < xsize-1; i++){
		for (int j = 0; j < ysize-1; j++){
			int xmin = i*spacing - xsize/2 * spacing;
			int ymin = j*spacing - ysize/2 * spacing;
			int xmax = (i+1)*spacing - xsize/2 * spacing;
			int ymax = (j+1)*spacing - ysize/2 * spacing;
			glTexCoord2f(0.0,0.0); glNormal3f(0,0,1); glVertex3f(xmin,ymin,0);
			glTexCoord2f(0.0,1.0); glNormal3f(0,0,1); glVertex3f(xmin,ymax,0);
			glTexCoord2f(1.0,1.0); glNormal3f(0,0,1); glVertex3f(xmax,ymax,0);
			glTexCoord2f(1.0,0.0); glNormal3f(0,0,1); glVertex3f(xmax,ymin,0);
		}
	}
	glEnd();
}