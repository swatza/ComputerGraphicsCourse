#ifndef COW_H
#define COW_H

#include "util.h"
#include "primitives.h"
#include "helper.h"
#include "main.h"

#include <time.h>
#include <stdlib.h>

#include <GL/glut.h> //linux
#define GL_GLEXT_PROTOTYPES

//Struct Definitions
typedef struct cow_leg_skeleton cow_leg_skeleton;
typedef struct cow_skeleton cow_skeleton;
typedef struct cow_object cow_object;
typedef struct cow_frame cow_frame;

//Prototypes
void renderCowObject(struct cow_object* my_cow_ptr, unsigned int cow_body_text, unsigned int cow_head_text);
void drawCow(struct cow_skeleton my_cow_skeleton,unsigned int cow_body_text, unsigned int cow_head_text);
void drawCowLeg(struct cow_leg_skeleton leg,unsigned int body_texture);
void drawCowHead(unsigned int cow_head_text);
void drawCowTorso(unsigned int body_texture);
void drawHorns();
void drawEars();
void calculateCowSkeleton(int frl,int fll, int brl, int bll, struct cow_skeleton *cow_skeleton_ptr);
void calculateCowLegSkeleton(double upper_leg_angle, double lower_leg_angle, struct cow_leg_skeleton *ptrleg);
void initializeCowObject(struct cow_object *ptrCow, int index);
double getSkeletonAngle1FromFrame(int frameNumber);
double getSkeletonAngle2FromFrame(int frameNumber);
//void renderCowObject(struct cow_object* my_cow_ptr, struct cow_object** all_cows);

//Struct Implementations
//Cow Leg Skeleton Information 
struct cow_leg_skeleton{
	struct vector3 upper_leg_pos;
	struct vector3 lower_leg_pos;
	struct vector3 knee_pos;
	struct vector3 ankle_pos;

	double upper_leg_angle;
	double lower_leg_angle;
};

//Struct for the cow skeleton; one for each object
struct cow_skeleton{
	//Torso Skeleton
	struct vector3 body_point; 
	struct vector3 body_orientation;
	//struct vector3 head_point; 
	//Leg skeletons
	struct cow_leg_skeleton LeftFrontLeg; 
	struct cow_leg_skeleton RightFrontLeg;
	struct cow_leg_skeleton LeftHindLeg; 
	struct cow_leg_skeleton RightHindLeg;
};

//struct for the leg angles on the cow for a frame
struct cow_frame{
	double A1;
	double A2;
};

struct cow_object{
	//We need information to draw the object (MESH) (polygons, triangles, etc...)
	//Information about where the object is (location and orientation)
	//Information about the mesh collider 

	//Object Name 
	char *object_name;
	//Object identifier
	int object_identifier;
	//Object type (Cow, Aircraft, Groundplane, Fence)
	struct cow_skeleton skeleton;
	struct mesh_collider mc;
	//Is the cow going to be moving
	int is_moving; //boolean 0 or 1
	int was_stopped; //boolean 0 or 1
	//new frame calculation
	int new_frame;
	//Current Frame 
	int FLL;
	int FRL;
	int BLL;
	int BRL;
};



#endif