/*
* openGL Rendering functions with minor GLUT involvement
*/

//Includes
#include "rendering.h"
#include "windmill.h"
#include "materials.h"

#define GL_GLEXT_PROTOTYPES

//Global Variables
int number_of_cows = 1;
struct cow_object **cows; //list of cow objects

float light_ambient[] = {0.0,0.0,0.0,1.0}; //how bright is the world; diffuse and specular indicate actual light from object
float light_diffuse[] = {0.8,0.8,0.8,1.0};
float light_specular[] ={0.5,0.5,0.5,0.0};

/*
float default_ambient[4] = {0.2,0.2,0.2,1.0};
float default_diffuse[4] = {0.8,0.8,0.8,1.0};
float default_specular[4] = {0.0,0.0,0.0,1.0};
float default_emission[4] = {0.0,0.0,0.0,1.0};
float default_shinny = 0; */

/*
* Function called by GLUT to display/render the scene
* original by Willem A. (Vlakkies) Schreuder
*/

//TODO! Break this function into subparts
void display(){
	//Clear the screen and Z buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//reset transformations
	glLoadIdentity();

	//Set the view position

	if(mode){
		double *xyz = spherical2cartesianCoords(3*dim, z_rotation_angle, -x_rotation_angle,0,0,0);
		double Ex = xyz[0];
		double Ey = xyz[1];
		double Ez = -xyz[2]; //flip sign
		gluLookAt(Ex,Ey,Ez,0,0,0,0,0,-cos(deg2rad(z_rotation_angle))); 
	}
	else{
		glRotatef(z_rotation_angle,1.0,0.0,0.0);
		//glRotatef(y_rotation_angle,0.0,1.0,0.0);
		glRotatef(x_rotation_angle,0.0,0.0,1.0);
	}

	//LIGHTING

	//normalize normal vectors
	glEnable(GL_NORMALIZE);		
	//Enable 
	glEnable(GL_LIGHTING);
	//Location of viewer for specular calculations
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,1); //parallel to the z thing (rather than with eye)
	//  glColor sets ambient and diffuse color materials
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //Set Light Parameters
    double distance = dim;
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0,GL_AMBIENT ,light_ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE ,light_diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR,light_specular);
	float light_position[] = {distance*cos(deg2rad(zh)),distance*sin(deg2rad(zh)),5,1};; //should be a directional source from way up - can be slightly tweaked
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	float yellow[] = {1.0,1.0,0.0,1.0};
	glPushMatrix();
	setMaterials(0,default_ambient,default_diffuse,yellow,default_emission,2);
	glTranslated(distance*cos(deg2rad(zh)),distance*sin(deg2rad(zh)),5);
	glScaled(0.5,0.5,0.5);
	glColor3f(1.0,1.0,1.0);
	drawSpherewTexture(texture[0]);
	glPopMatrix();

	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	//Draw Cow
	if(obj_viewer == 0){
		//Set at 0,0,0
		struct vector3 my_position;
		my_position.x = 0;
		my_position.y = 0;
		my_position.z = 0;
		cows[0]->skeleton.body_point = my_position;
		//Calculate Skeleton with new angles
		struct vector3 my_orientation;
		my_orientation.x = 0;
		my_orientation.y = cow_body_angle;
		my_orientation.z = 0;
		cows[0]->skeleton.body_orientation = my_orientation;
		//Create all the structures
		struct vector3 left_elbow_angle;
		left_elbow_angle.x = left_elbow_angle_x;
		left_elbow_angle.y = left_elbow_angle_y;
		left_elbow_angle.z = left_elbow_angle_z;
		struct vector3 right_elbow_angle;
		right_elbow_angle.x = right_elbow_angle_x;
		right_elbow_angle.y = right_elbow_angle_y;
		right_elbow_angle.z = right_elbow_angle_z;
		struct vector3 left_wrist_angle;
		left_wrist_angle.x = left_wrist_angle_x;
		left_wrist_angle.y = left_wrist_angle_y;
		left_wrist_angle.z = left_wrist_angle_z;
		struct vector3 right_wrist_angle;
		right_wrist_angle.x = right_wrist_angle_x;
		right_wrist_angle.y = right_wrist_angle_y;
		right_wrist_angle.z = right_wrist_angle_z;

		struct vector3 left_knee_angle;
		left_knee_angle.x = left_knee_angle_x;
		left_knee_angle.y = left_knee_angle_y;
		left_knee_angle.z = left_knee_angle_z;
		struct vector3 left_ankle_angle;
		left_ankle_angle.x = left_ankle_angle_x;
		left_ankle_angle.y = left_ankle_angle_y;
		left_ankle_angle.z = left_ankle_angle_z;
		struct vector3 right_knee_angle;
		right_knee_angle.x = right_knee_angle_x;
		right_knee_angle.y = right_knee_angle_y;
		right_knee_angle.z = right_knee_angle_z;
		struct vector3 right_ankle_angle;
		right_ankle_angle.x = right_ankle_angle_x;
		right_ankle_angle.y = right_ankle_angle_y;
		right_ankle_angle.z = right_ankle_angle_z;

		calculateCowLegSkeleton(left_elbow_angle, left_wrist_angle, &cows[0]->skeleton.LeftFrontLeg);
		calculateCowLegSkeleton(right_elbow_angle, right_wrist_angle, &cows[0]->skeleton.RightFrontLeg);

		calculateCowLegSkeleton(left_knee_angle, left_ankle_angle, &cows[0]->skeleton.LeftHindLeg);
		calculateCowLegSkeleton(right_knee_angle, right_ankle_angle, &cows[0]->skeleton.RightHindLeg);

		//Draw the Cow 
		//drawCowLeg(cows[0]->skeleton.LeftHindLeg,texture[0]);
		drawCow(cows[0]->skeleton, texture[0],texture[1]); 
		//renderCowObject(cows[0],texture[0],texture[1]);
	}
	else if (obj_viewer == 1){
		drawWaterContainer(texture[5],texture[4],texture[6]);
		drawWater(texture[8]);
	}
	else if (obj_viewer == 2){
		//glDisable(GL_TEXTURE_2D);
		drawWindmill(texture[10],texture[9],texture[7],texture[4],texture[6],texture[5]);
	}
	else if (obj_viewer == 3){
		drawHayBale(texture[3],texture[2]);//texture number
		//drawSkyBoxModified(dim, texture[13],texture[14],texture[15],texture[11],texture[12]);
	}
	glDisable(GL_TEXTURE_2D);
	drawAxis();
	if(obj_viewer == 0)
		printCowAngles();
	//Print Information
	printViewing();

	//Error Check
	ErrCheck("display");
	//flush and swap buffer
	glFlush();
	glutSwapBuffers();
}


/*
* Function to draw the X-Y-Z axis -> useful for checking
* Original by Willem A. (Vlakkies) Schreuder
*/
void drawAxis(){
	//default length
	double len = dim;
	//set color
	glColor3f(1,1,1); //whte
	//Draw the 3 axeses
	glBegin(GL_LINES);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(len,0.0,0.0);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(0.0,len,0.0);
	glVertex3d(0.0,0.0,0.0);
	glVertex3d(0.0,0.0,len);
	glEnd();
	//Label Axes
	glRasterPos3d(len,0.0,0.0);
	Print("X");
	glRasterPos3d(0.0,len,0.0);
	Print("Y");
	glRasterPos3d(0.0,0.0,len);
	Print("Z");
	ErrCheck("drawAxis");
}

/*
* Function to instantiate my global object memory for cows and other future objects.
*/
void createObjects(){
	//How many cows do we want to create
	cows = (struct cow_object**)malloc(sizeof(struct cow_object*)*number_of_cows);
	//for i in number of cows
	for (int i = 0; i < number_of_cows; i++){
		//Initialize a cow object into memory
		struct cow_object *my_cow_ptr = (struct cow_object*)malloc(sizeof(struct cow_object));
		//Initialize the values for said cow object
		initializeCowObject(my_cow_ptr,i);
		//create a cow object structure
		cows[i] = my_cow_ptr;
	}
}

/*
* End program clean up just in case.
*/
void cleanObjects(){
	for (int i =0; i < number_of_cows; i++){
		free(cows[i]);
		//printf("We are now freeing the cow %i from the pen\n",i);
	}
	//free(cows);
	printf("All cows are free\n");
}

void printViewing(){
	glColor3f(1.0,1.0,1.0);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	glWindowPos2i(5,height-20);
	if(obj_viewer == 0)
		Print("Viewing: Cow");
	else if(obj_viewer == 1)
		Print("Viewing: Water Container");
	else if(obj_viewer == 2)
		Print("Viewing: Windmill");
	else if (obj_viewer == 3)
		Print("Viewing: Hay Bale"); 
}

void printCowAngles(){
	//int base = 5;
	//int delta = 15;
	
	glColor3f(1.0,1.0,1.0); //White
	glWindowPos2i(5,65);
	Print("Body - Body %i, Head %i", cow_body_angle, cow_head_angle);
	glWindowPos2i(5,50);
	Print("Right Elbow: %i, %i, %i; Left Elbow: %i, %i, %i",right_elbow_angle_x, right_elbow_angle_y, right_elbow_angle_z, right_wrist_angle_x, right_wrist_angle_y, right_wrist_angle_z);
	glWindowPos2i(5,35);
	Print("Left Elbow: %i, %i, %i; Left Wrist: %i, %i, %i",left_elbow_angle_x, left_elbow_angle_y, left_elbow_angle_z, left_wrist_angle_x, left_wrist_angle_y, left_wrist_angle_z);
	glWindowPos2i(5,20);
	Print("Right Knee: %i, %i, %i; Right Ankle: %i, %i, %i",right_knee_angle_x,right_knee_angle_y,right_knee_angle_z,right_ankle_angle_x, right_ankle_angle_y, right_ankle_angle_z);
	glWindowPos2i(5,5);
	Print("Left Knee: %i, %i, %i; Left Ankle: %i, %i, %i",left_knee_angle_x,left_knee_angle_y,left_knee_angle_z,left_ankle_angle_x,left_ankle_angle_y,left_ankle_angle_z);

	ErrCheck("Print Cow Angles"); 
}

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 *  Original by Willem A. (Vlakkies) Schreuder
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format, ...){
	char    buf[LEN];
	char*   ch=buf;
	va_list args;
	//  Turn the parameters into a character string
	va_start(args,format);
	vsnprintf(buf,LEN,format,args);
	va_end(args);
	//  Display the characters one at a time at the current raster position
	while (*ch)
	  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}
