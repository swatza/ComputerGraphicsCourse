/*
* openGL Rendering functions with minor GLUT involvement
*/

//Includes
#include "rendering.h"

//Global Variables
int number_of_cows = 2;
int number_of_lights = 2;
struct cow_object **cows; //list of cow objects
struct light **lights; //list of light objects

//Set material properties here
// ---------- Grass -----------
const static float grass_ambient[4] = {0.1,0.1,0.1,1.0};
const static float grass_diffuse[4] = {0.9,0.9,0.9,1.0};
const static float grass_specular[4] = {0.0,0.0,0.0,1.0};
const static float grass_emission[4] = {0.0,0.0,0.0,1.0};
const static int grass_shiny = 0;
// ---------- Fence -----------
const static float fence_ambient[4] = {0.1,0.1,0.1,1.0};
const static float fence_diffuse[4] = {0.6,0.6,0.6,1.0};
const static float fence_specular[4] = {0.0,0.0,0.0,1.0};
const static float fence_emission[4] = {0.0,0.0,0.0,1.0};
const static int fence_shiny = 0;
// ---------- Cow -----------
const static float cow_ambient[4] = {0.1,0.1,0.1,1.0};
const static float cow_diffuse[4] = {0.8,0.8,0.8,1.0};
const static float cow_specular[4] = {0.0,0.0,0.0,1.0};
const static float cow_emission[4] = {0.0,0.0,0.0,1.0};
const static int cow_shiny = 0;


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
	
	//Rotate the entire frame to make Logical sense
	glRotated(90,1.0,0.0,0.0);
	
	//WHAT VIEW MODE ARE WE IN? (PERSPECTIVE vs ORTHOGONAL
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
		}
		//First person walk around
		else if (view_mode == 1){
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
	
	//Turn on lighting
	int light = 0;
	
	//Flat or smooth shading
	glShadeModel(GL_SMOOTH); //smooth baby!
	
	//Lighting
	if(light){
		//normalize normal vectors
		glEnable(GL_NORMALIZE);		
		//Enable 
		glEnable(GL_LIGHTING);
		//Location of viewer for specular calculations
		glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,0); //parallel to the z thing (rather than with eye)
		//  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
		//Loop through all the lights that we have and turn those babies on! (if they are supposed to be)
		for (int i = 0; i < number_of_lights; i++){
			//Is it supposed to be on? else break;
			
			//Set it active
			glEnable(lightEnumerations[i]);
			//Make a ball for it (placeholder!)
			glPushMatrix();
			//Put it in the correct spot 
			glTranslated(0,0,30);
			glScaled(0.1,0.1,0.1);
			//Draw representative sphere
			drawSphere();
			glPopMatrix();
			//Set the lighting on
			performLighting(lights[i]);
		}
	}
	else{
    	glDisable(GL_LIGHTING);
    }
	
	//Are we using textures
	if(textureFlag == 0)
		glDisable(GL_TEXTURE_2D);
	else{
		//Enable textures
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); // modulate mode (not replace)
	}
	
	//Translate based on scale desired
	//Draw the desired objects
	//-----------
	// Draw Ground Plane
	//-----------
	
	glPushMatrix();
	glScaled(51,51,0);
	setMaterials(0,grass_ambient,grass_diffuse,grass_specular,grass_emission,grass_shiny);
	drawPlanewTexture(texture[4]);
	glPopMatrix(); 
	
	//------------
	// Draw Fence to border ground plane
	//------------
	//setMaterials(0,fence_ambient,fence_diffuse,fence_specular,fence_emission,fence_shiny);
	//createFence(11,11,50,-50,50,-50); //How big should the fence be? )
	// -----------
	// Draw Cows
	// -----------
	//setMaterials(0,cow_ambient,cow_diffuse,cow_specular,cow_emission,cow_shiny);
	for (int i = 0; i < number_of_cows; i++){
		//Check collisions here?
		//renderCowObject(cows[i]);
	}
	if(axis_on){
		//drawAxis();
	}
	//Print Modes
	printModes();
	//Error Check
	ErrCheck("display");
	//flush and swap buffer
	glFlush();
	glutSwapBuffers();
	//CHANGE THIS IF WE FIX THE COW STUFF
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
	//How many Lights do we want to create??
	lights = (struct light**)malloc(sizeof(struct light*) * number_of_lights);
	//for i in number of lights
	for (int i =0; i<number_of_lights;i++){
		//initialize a light object into memory
		struct light *my_light_ptr = (struct light*)malloc(sizeof(struct light));
		//set all parameters to default 
		createLightObj(my_light_ptr, lightEnumerations[i]);
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
	for (int i=0; i < number_of_lights; i++){
		free(lights[i]);
	}
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
