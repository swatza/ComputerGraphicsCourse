//Includes
#include "cow.h"

//COW CONSTANTS
static double upper_leg_length = 2.0;
static double upper_leg_width = .25;
static double lower_leg_length = 2.0;
static double lower_leg_width = .25;
static double ankle_height = 0.25;

static double body_length = 5;
static double body_width = 2.0;
static double body_height = 1.5;

static double head_length = 1;
static double head_width = 1.5;
static double head_height = 1.2;

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

void renderCowObject(struct cow_object* my_cow_ptr){
	struct cow_object my_cow = *my_cow_ptr; //hand off the cow object
	struct cow_skeleton my_cow_skeleton = my_cow.skeleton; //hand off the cow skeleton 
	//Determine movement of cow

	//determine which frame to render (TBD)

	//Calculate the skeletons
	if(my_cow.new_frame){
		calculateCowSkeleton(0,&my_cow_skeleton); //animation frame and skeleton ptr
		my_cow.new_frame = 0;
	}
	//Render the cow
	drawCow(my_cow_skeleton);
	//Hand back the cow object
	*my_cow_ptr = my_cow;
}

//----------------------------------------------------------------------------------
//							DRAW COW FUNCTIONS
//----------------------------------------------------------------------------------

void drawCow(struct cow_skeleton my_cow_skeleton){
	glPushMatrix();
	glTranslated(my_cow_skeleton.body_point.x,my_cow_skeleton.body_point.y,my_cow_skeleton.body_point.z);
	glRotated(my_cow_skeleton.body_orientation.z, 0.0,0.0,1.0);
	//glRotatef(my_cow_skeleton.body_orientation.x,my_cow_skeleton.body_orientation.y,my_cow_skeleton.body_orientation.z);
	drawCowTorso();
	//Draw the head
	glPushMatrix();
	glTranslated(4.5,0,-0.4);
	drawCowHead();
	glPopMatrix();

	//Now shift the cow leg
	glPushMatrix();
	glTranslated(-2.5,-1,1.8); //Rear Leg Coordinate?
	drawCowLeg(my_cow_skeleton.LeftHindLeg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.5,1,1.8); //Rear Leg Coordinate?
	drawCowLeg(my_cow_skeleton.RightHindLeg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,-1,1.8); //Front Leg 
	drawCowLeg(my_cow_skeleton.LeftFrontLeg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,1,1.8); //Front Leg
	drawCowLeg(my_cow_skeleton.RightFrontLeg);
	glPopMatrix();

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

//----------------------------------------------------------------------------------
//							SKELETON FUNCTIONS
//----------------------------------------------------------------------------------


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

void calculateCowSkeleton(int animation_frame, struct cow_skeleton *cow_skeleton_ptr){
	struct cow_skeleton my_skeleton = *cow_skeleton_ptr;
	//Using the animation frame, grab the corresponding skeleton frames

	//Calcualte teh skeleton frames
	calculateCowLegSkeleton(90,90,&(my_skeleton.LeftFrontLeg));
	calculateCowLegSkeleton(90,90,&(my_skeleton.RightFrontLeg));
	calculateCowLegSkeleton(90,90,&(my_skeleton.LeftHindLeg));
	calculateCowLegSkeleton(90,90,&(my_skeleton.RightHindLeg));
}

//----------------------------------------------------------------------------------
//							COW INITIALIZATION FUNCTIONS
//----------------------------------------------------------------------------------

void initializeCowObject(struct cow_object *ptrCow, int index){
	cow_object thiscow = *ptrCow;
	//First set the name and index
	thiscow.object_name = "BasicCow";
	thiscow.object_identifier = index;
	thiscow.new_frame = 1;
	//Next generate the center point of the cow
	//COW LIMITS on position
	thiscow.skeleton.body_point.x = random_at_most(60) - 30; //Should center around 0
	thiscow.skeleton.body_point.y = random_at_most(60) - 30; //should center around 0
	thiscow.skeleton.body_point.z = -3; //offset based on height of cow (TBD)
	//Next generate the orientation point of the cow
	thiscow.skeleton.body_orientation.x = 0; //ignore
	thiscow.skeleton.body_orientation.y = 0; //ignore
	thiscow.skeleton.body_orientation.z = random_at_most(359); //yaw angle (heading of cow)
	*ptrCow = thiscow;
}

//----------------------------------------------------------------------------------
//							COW ANIMATION FUNCTIONS
//----------------------------------------------------------------------------------