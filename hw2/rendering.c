/*
* openGL Rendering functions with minor GLUT involvement
*/

//Includes
#include "rendering.h"

//Global Variables
int number_of_cows = 2;
//struct aircraft **airplanes;
struct cow_object **cows; //list of cow objects
struct mesh_collider **mc_fence;

/*
* Function called by GLUT to display/render the scene
* original by Willem A. (Vlakkies) Schreuder
*/
void display(){
	//double* output = malloc(size*sizeof(double));
	//Clear the screen and Z buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//reset transformations
	glLoadIdentity();
	//Rotate the desired objects
	glRotated(90,1.0,0.0,0.0);
	if (mode){
		//TODO Change this to first person look around
		//PERSPECTIVE
		if (view_mode == 0){			
			glRotated(-90,1.0,0.0,0.0);
			if(z_rotation_angle > 88){
				z_rotation_angle = 88; //limiting Z rotation
			}
			if(z_rotation_angle < 2){
				z_rotation_angle = 2;
			}
			double* xyz = spherical2cartesianCoords(3*dim,z_rotation_angle,-x_rotation_angle,0,0,0);
			double Ex = xyz[0];
			double Ey = xyz[1];
			double Ez = -xyz[2]; //flip sign ??
			gluLookAt(Ex,Ey,Ez,0,0,0,0,0,-cos(deg2rad(z_rotation_angle)));
			/* WORKING VERSION KIND OF
			double* xy = polar2cartesianCoords(3*dim,x_rotation_angle);
			double Ex = xy[0];
			double Ey = xy[1];
			double Ez = -1*dim;
			gluLookAt(Ex,Ey,Ez,0,0,0,0,0,-1); */
		}
		//Circuling Aircraft 1
		if (view_mode == 1){
			//Get teh aircraf'ts position 
			// Figure out the vector from the aircraft 
			//looking out bottom
			if(side == 0){
				//Down Vector from teh aircraft 
			}
			//Looking out right 
			else if(side == 1){
				//Cross product of the down vector and forward vector (+ if Z up)
			}
			//looking out left
			else if(side == 2){
				//Cross product of th down vector and forward vector (- if Z up)
			}
			//gluLookAt(...);
		}
		//Circuling Aircraft 2
		else if (view_mode == 2){
			//Use the check from aircraft 1
			//gluLookAt(...);
		}
		//First person walk around
		else if (view_mode == 3){
			glRotated(-90,1.0,0.0,0.0);
			//Use the position 
			double LAH_X = 1 * cos(deg2rad(camera_yaw)) + camera_x;
			double LAH_Y = 1 * sin(deg2rad(camera_yaw)) + camera_y;
			double LAH_Z = camera_z;
			gluLookAt(camera_x,camera_y,camera_z,LAH_X,LAH_Y,LAH_Z,0,0,-1);
			printCameraPosition();
		}
	}
	else{
		//ORTHOGONAL 
		glRotatef(z_rotation_angle,1.0,0.0,0.0);
		glRotatef(y_rotation_angle,0.0,1.0,0.0);
		glRotatef(x_rotation_angle,0.0,0.0,1.0);
	}
	//Translate based on scale desired
	//Draw the desired objects
	//-----------
	// Draw Ground Plane
	//-----------
	glPushMatrix();
	glScaled(51,51,0);
	glColor3f(0.13,0.54,0.13);
	drawPlane();
	glPopMatrix();
	//------------
	// Draw Fence to border ground plane
	//------------
	createFence(11,11,50,-50,50,-50); //How big should the fence be? )
	// -----------
	// Draw Cows
	// -----------
	for (int i = 0; i < number_of_cows; i++){
		//Check collisions here?
		renderCowObject(cows[i]);
	}
	if(axis_on)
		drawAxis();
	// -----------
	// Draw Aircraft
	// -----------
	/*
	for (int i =0; i < 2; i++){
		renderAircraftObject(airplanes[i]);
	} */
	//Print Angles;
	//printAngles();
	//Print Modes
	printModes();
	//Error Check
	ErrCheck("display");
	//flush and swap buffer
	glFlush();
	glutSwapBuffers();
	//Main new frame set back to 0
	main_new_frame = 0;
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
	//How many airplanes do we want to create
	/*
	double altitude[2];
	altitude[0] = 20;
	altitude[1] = 30;
	double loiter_radius[2];
	loiter_radius[0] = 70;
	loiter_radius[1] = 40;
	double velocity_scaler[2];
	velocity_scaler[0] = 2;
	velocity_scaler[1] = 1;

	airplanes = (struct aircraft**)malloc(sizeof(struct aircraft*)*2);
	for (int i =0; i < 2; i++){
		//initialize aircraft into memory
		struct aircraft *my_ac_ptr = (struct aircraft*)malloc(sizeof(struct aircraft));
		//initialize the values  for aircraft
		initializeLoiterDrone(my_ac_ptr,altitude[i],loiter_radius[i],velocity_scaler[i]);
		airplanes[i] = my_ac_ptr;
	} */

	//Mesh Collider for Fence
	/*
	mc_fence = (struct mesh_collider*)malloc(sizeof(struct mesh_collider*)*4);
	for (int i =0; i < 4; i++){
		struct mesh_collider* mesh_ptr = (struct mesh_collider*)malloc(sizeof(struct mesh_collider));
		struct mesh_collider thismesh = {.d=2,.w=52,.h=10}; //
		*mesh_ptr = thismesh;
		mc_fence[i] = mesh_ptr;
	} */

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

/*
* Used to print out the rotation angles in the bottom left 
* Original by Willem A. (Vlakkies) Schreuder
*/
void printModes(){
	//int height = glutGet(GLUT_WINDOW_HEIGHT);
	//int width = glutGet(GLUT_WINDOW_WIDTH);
	glColor3f(1.0,1.0,1.0);
	glWindowPos2i(5,50);
	Print("CAMERA INFO");
	glWindowPos2i(5,35);
	Print("FOV: %i; DIM %f",fov,dim);
	glWindowPos2i(5,20);
	if (mode){
		if(view_mode == 0){
			Print("Mode: PERSPECTIVE; View Mode: WORLD");
		}
		else{
			Print("Mode: PERSPECTIVE; View Mode: 1st Person");
		}
	}
	else{
		Print("Mode: ORTHOGONAL; View Mode: WORLD");
	}
	glWindowPos2i(5,5);
	//Print the text string
	Print("Global View Angle=%i,%i",x_rotation_angle,z_rotation_angle); 
}

/*
* Function to provide camera location information in 1st person
*/
void printCameraPosition(){
	glColor3f(1.0,1.0,1.0);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	glWindowPos2i(5,height-15);
	Print("Camera Position: %f, %f, %f", camera_x, camera_y, camera_z);
	glWindowPos2i(5,height-30);
	Print("Camera Direction: %f", camera_yaw);
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
