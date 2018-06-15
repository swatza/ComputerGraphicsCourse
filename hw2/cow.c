//Includes
#include "cow.h"
#include "util.h"
#include "primitives.h"
#include "helper.h"
#include <GL/glut.h> //linux
#define GL_GLEXT_PROTOTYPES

//COW CONSTANTS
static double upper_leg_length = 1.0;
static double upper_leg_width = .25;
static double lower_leg_length = 1.0;
static double lower_leg_width = .25;
static double ankle_height = 0.25;

static double body_length = 5;
static double body_width = 2.0;
static double body_height = 1.5;

static double head_length = 1;
static double head_width = 1.5;
static double head_height = 1.2;

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
};


void drawCowTest(int angle1,int angle2){
	angle1 = angle1 - 90;
	angle2 = angle2 - 90;
	//Calculate the skeleton parts
	cow_leg_skeleton *my_cow_leg = (struct cow_leg_skeleton*)malloc(sizeof(struct cow_leg_skeleton)); //OPTIMIZATION ISSUE IS THIS
	calculateCowLegSkeleton(angle1,angle2,my_cow_leg);

	//Using the skeleton information, draw the cow parts
	drawCowTorso();
	glPushMatrix();
	glTranslated(4.5,0,-0.4);
	drawCowHead();
	glPopMatrix();

	//Now shift the cow leg
	glPushMatrix();
	glTranslated(-2.5,-1,1); //Rear Leg Coordinate?
	drawCowLeg(*my_cow_leg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.5,1,1); //Rear Leg Coordinate?
	drawCowLeg(*my_cow_leg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,-1,1); //Front Leg 
	drawCowLeg(*my_cow_leg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,1,1); //Front Leg
	drawCowLeg(*my_cow_leg);
	glPopMatrix();
}

void drawCowTorso(){
	drawEllipsoid(body_length,body_width,body_height);
}

void drawCowLeg(struct cow_leg_skeleton leg){
	//Using the angles and positions gathered from the skeleton leg
	//printf("Upper Leg Position %f,0,%f\n",leg.upper_leg_pos.x, leg.upper_leg_pos.z);
	//printf("Lower Leg Position %f,0,%f\n",leg.lower_leg_pos.x, leg.lower_leg_pos.z);
	//HIP
	glPushMatrix();
	glScaled(upper_leg_width,upper_leg_width,upper_leg_width);
	drawSphere();
	glPopMatrix();
	//UPPER LEG
	glPushMatrix(); //Save the transformations
	glTranslated(leg.upper_leg_pos.x,leg.upper_leg_pos.y, leg.upper_leg_pos.z);
	glRotatef(leg.upper_leg_angle,0.0,1.0,0.0);
	glScaled(upper_leg_width, upper_leg_width, upper_leg_length);
	drawCylinder();
	glPopMatrix(); //Undo the transformations
	//KNEE
	glPushMatrix(); //Do i Need to do a glPush?
	glTranslated(leg.knee_pos.x, leg.knee_pos.y, leg.knee_pos.z);
	glScaled(upper_leg_width,upper_leg_width,upper_leg_width);
	drawSphere();
	glPopMatrix();
	//LOWER LEG
	glPushMatrix();
	glTranslated(leg.lower_leg_pos.x, leg.lower_leg_pos.y, leg.lower_leg_pos.z);
	glRotatef(leg.lower_leg_angle,0.0,1.0,0.0);
	glScaled(lower_leg_width, lower_leg_width, lower_leg_length);
	drawCylinder();
	glPopMatrix();
	//ANKLE TODO
	glPushMatrix();
	glTranslated(leg.ankle_pos.x, leg.ankle_pos.y, leg.ankle_pos.z);
	glScaled(lower_leg_width,lower_leg_width,ankle_height);
	drawCylinder();
	glPopMatrix();

}

void drawCowHead(){
	drawEllipsoid(head_length,head_width,head_height);
	glPushMatrix();
	glTranslated(-4.5,0,+0.4);
	drawHorns();
	drawEars();
	glPopMatrix();
}

void drawHorns(){
	glBegin(GL_POLYGON);
	//yellow
	glColor3f(1.0,1.0,-0.0);
	glVertex3f(4.5,1.4,-0.4);
	glVertex3f(4.5,0.4,-0.4);
	glVertex3f(4.5,1.0,-2.0);
	glEnd();
	glBegin(GL_POLYGON);
	//yellow
	glColor3f(1.0,1.0,-0.0);
	glVertex3f(4.5,-1.4,-0.4);
	glVertex3f(4.5,-0.4,-0.4);
	glVertex3f(4.5,-1.0,-2.0);
	glEnd();
	ErrCheck("DrawHorns");
}

void drawEars(){
	glBegin(GL_POLYGON);
	//Purple
	glColor3f(1.0,0.0,-1.0);
	glVertex3f(4.5,1.2,-1.0);
	glVertex3f(4.5,1.2,-0.4);
	glVertex3f(4.5,2.0,-0.4);
	glVertex3f(4.5,2.0,-0.6);
	glEnd();
	glBegin(GL_POLYGON);
	//Purple
	glColor3f(1.0,0.0,-1.0);
	glVertex3f(4.5,-1.2,-1.0);
	glVertex3f(4.5,-1.2,-0.4);
	glVertex3f(4.5,-2.0,-0.4);
	glVertex3f(4.5,-2.0,-0.6);
	glEnd();
	ErrCheck("DrawEars");
}

void calculateCowLegSkeleton(double upper_leg_angle, double lower_leg_angle, struct cow_leg_skeleton *ptrleg){
	struct cow_leg_skeleton leg = *ptrleg;

	double cos_ula = cos(deg2rad(upper_leg_angle));
	double sin_ula = sin(deg2rad(upper_leg_angle));
	double cos_lla = cos(deg2rad(lower_leg_angle));
	double sin_lla = sin(deg2rad(lower_leg_angle));

	//Calculate the upper leg center point
	//double x_upper_leg = .5 * upper_leg_length * cos_ula;
	//double z_upper_leg = -(.5 * upper_leg_length * sin_ula);
	//printf("Upper Leg Position %f,0,%f\n",x_upper_leg,z_upper_leg);
	leg.upper_leg_pos.x = .5 * upper_leg_length * cos_ula;
	leg.upper_leg_pos.y = 0;
	leg.upper_leg_pos.z = -(.5 * upper_leg_length * sin_ula);
	//Calculate the knee joint center point
	//printf("knee Position %f,0,%f\n",x_knee,z_knee);
	leg.knee_pos.x = upper_leg_length * cos_ula;
	leg.knee_pos.y = 0;
	leg.knee_pos.z = -(upper_leg_length * sin_ula);
	double x_knee = leg.knee_pos.x;
	double z_knee = leg.knee_pos.z;
	//Calculate lower leg center point
	//double x_lower_leg = .5 * lower_leg_length * cos_lla + x_knee;
	//double z_lower_leg = -(.5 * lower_leg_length * sin_lla + z_knee;
	//printf("Lower Leg Position %f,0,%f\n",x_lower_leg,z_lower_leg);
	leg.lower_leg_pos.x = .5 * lower_leg_length * cos_lla + x_knee;
	leg.lower_leg_pos.y = 0;
	leg.lower_leg_pos.z = -(.5 * lower_leg_length * sin_lla) + z_knee;
	//Calculate ankle center point
	//double x_ankle = lower_leg_length * cos_lla + x_knee;
	//double z_ankle = -(lower_leg_length * sin_lla) + z_knee;
	leg.ankle_pos.x = lower_leg_length * cos_lla + x_knee;
	leg.ankle_pos.y = 0;
	leg.ankle_pos.z = -(lower_leg_length * sin_lla) + z_knee;
	//Hand off the angles
	leg.upper_leg_angle = upper_leg_angle + 90;
	leg.lower_leg_angle = lower_leg_angle + 90;
	*ptrleg = leg;
}

void calculateCowSkeleton(struct cow_frame frame_angles, struct cow_skeleton thisCow){
	//Figure out where the legs should be
	//calculateCowLegSkeleton(frame_angles.fl_cow_upper_leg_angle,frame_angles.fl_cow_lower_leg_angle, thisCow.LeftFrontLeg); //FRONT LEFT
	//calculateCowLegSkeleton(frame_angles.fr_cow_upper_leg_angle,frame_angles.fr_cow_lower_leg_angle, thisCow.RightFrontLeg); //FRONT RIGHT
	//calculateCowLegSkeleton(frame_angles.bl_cow_upper_leg_angle,frame_angles.bl_cow_lower_leg_angle, thisCow.LeftHindLeg); //HIND LEFT
	//calculateCowLegSkeleton(frame_angles.br_cow_upper_leg_angle,frame_angles.br_cow_lower_leg_angle, thisCow.LeftHindLeg); //HIND RIGHT
	//Determine anything about the body? 
}


void initializeCowObject(struct cow_object *ptrCow, int index){
	cow_object thiscow = *ptrCow;
	//First set the name and index
	thiscow.object_name = "BasicCow";
	thiscow.object_identifier = index;
	//Next generate the center point of the cow
	thiscow.skeleton.body_point.x = 0; 
	thiscow.skeleton.body_point.y = 0;
	thiscow.skeleton.body_point.z = 0; //offset based on height of cow
	//Next generate the orientation point of the cow
	thiscow.skeleton.body_orientation.x = 0; //ignore
	thiscow.skeleton.body_orientation.y = 0; //ignore
	thiscow.skeleton.body_orientation.z = 0; //yaw angle (heading of cow)
	*ptrCow = thiscow;
}