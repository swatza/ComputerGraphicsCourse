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
typedef struct cow_limb_angles cow_limb_angles;

//Prototypes
void drawDancingCow(struct cow_skeleton my_cow_skeleton, unsigned int cow_body_text, unsigned int cow_head_text);
void drawCow(struct cow_skeleton my_cow_skeleton,unsigned int cow_body_text, unsigned int cow_head_text);
void drawCowLeg(struct cow_leg_skeleton leg,unsigned int body_texture);
void drawCowHead(unsigned int cow_head_text);
void drawCowTorso(unsigned int body_texture);
void drawHorns();
void drawEars();
void calculateCowSkeleton(struct cow_frame new_frame, struct cow_object *cow_ptr);
void calculateCowLegSkeleton(struct vector3 upper_leg_angle, struct vector3 lower_leg_angle, struct cow_leg_skeleton *ptrleg);
void initializeCowObject(struct cow_object *ptrCow, int index);
double getSkeletonAngle1FromFrame(int frameNumber);
double getSkeletonAngle2FromFrame(int frameNumber);
void drawLeg(int unsigned text);

void determineFrameToDraw(struct cow_object *ptrCow,int flag, int steps, int number);
void AnimateBetweenKeyFrames(struct cow_object *ptrCow, int move_type, int keyframe0, int keyframe1, int number_of_steps, int step_number);
double* AnglesBetweenLimbs(struct cow_limb_angles L1, struct cow_limb_angles L2);
void createWalkingFrames();
void createStandingFrame();
void createDancingFrame();
//void renderCowObject(struct cow_object* my_cow_ptr, struct cow_object** all_cows);

//Struct Implementations
//Cow Leg Skeleton Information 
struct cow_leg_skeleton{
	struct vector3 upper_leg_pos;
	struct vector3 lower_leg_pos;
	struct vector3 knee_pos;
	struct vector3 ankle_pos;

	struct vector3 upper_leg_angle;
	struct vector3 lower_leg_angle;
	double upper_leg_length;
	double lower_leg_length;
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

struct cow_limb_angles{
	double ULX;
	double ULY;
	double LLX;
	double LLY;
};

//struct for the leg angles on the cow for a frame
struct cow_frame{
	struct cow_limb_angles LeftLeg;
	struct cow_limb_angles RightLeg;
	struct cow_limb_angles LeftArm;
	struct cow_limb_angles RightArm;
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
	//is the cow standing like a human
	int isStanding;
	//Current Frame Information
	int move_type; //Dancing; Stopped; Walking;
	int key_frame_number; 
	//Walking key Frames -> 6?
	//Stopped key Frames -> 0
	struct cow_frame frame_to_draw;
	struct cow_frame last_frame_drawn;
};



#endif