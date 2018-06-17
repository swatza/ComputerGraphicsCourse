#ifndef COW_H
#define COW_H

#include "util.h"
#include "primitives.h"
#include "helper.h"

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
void drawCowTest(int angle1, int angle2);
void renderCowObject(struct cow_object* my_cow_ptr);
void drawCow(struct cow_skeleton my_cow_skeleton);
void drawCowLeg(struct cow_leg_skeleton leg);
void drawCowHead();
void drawCowTorso();
void drawHorns();
void drawEars();
void calculateCowSkeleton(int animation_frame, struct cow_skeleton *cow_skeleton_ptr);
void calculateCowLegSkeleton(double upper_leg_angle, double lower_leg_angle, struct cow_leg_skeleton *ptrleg);
void initializeCowObject(struct cow_object *ptrCow, int index);

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
	double fl_cow_upper_leg_angle;
	double fl_cow_lower_leg_angle;

	double fr_cow_upper_leg_angle;
	double fr_cow_lower_leg_angle;

	double bl_cow_upper_leg_angle;
	double bl_cow_lower_leg_angle;

	double br_cow_upper_leg_angle;
	double br_cow_lower_leg_angle;
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
	//new frame calculation
	int new_frame;
};



#endif