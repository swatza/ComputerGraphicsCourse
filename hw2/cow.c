//Includes
#include "cow.h"

//COW CONSTANTS
static double upper_leg_length = 2.0;
static double upper_leg_width = .25;
static double lower_leg_length = 2.0;
static double lower_leg_width = .25;
static double ankle_height = 0.25;

const double cow_move_speed = .5;
const double cow_buffer = 5.5;

static double body_length = 5;
static double body_width = 2.0;
static double body_height = 1.5;

static double head_length = 1;
static double head_width = 1.5;
static double head_height = 1.2;
/*
static struct cow_frame frame0 = {.flcula=90,.flclla=90,.frcula=90,.frclla=90,.blcula=0,.blclla=0,.brcula=0,.blcula=0}; 
static struct cow_frame frame1 = {.flcula=45,.flclla=90,.frcula=90,.frclla=90,.blcula=0,.blclla=0,.brcula=0,.blcula=0}; 
static struct cow_frame frame2 = {.flcula=30,.flclla=30,.frcula=60,.frclla=60,.blcula=0,.blclla=0,.brcula=0,.blcula=0}; //shift body
static struct cow_frame frame3 = {.flcula=60,.flclla=60,.frcula=30,.frclla=30,.blcula=0,.blclla=0,.brcula=0,.blcula=0}; //shift body more
static struct cow_frame frame4 = {.flcula=90,.flclla=90,.frcula=90,.frclla=180,.blcula=0,.blclla=0,.brcula=0,.blcula=0};
static struct cow_frame frame5 = {.flcula=90,.flclla=90,.frcula=45,.frclla=90,.blcula=0,.blclla=0,.brcula=0,.blcula=0};*/
static struct cow_frame frame0 = {.A1 = 0,.A2=0};
static struct cow_frame frame1 = {.A1 = 45,.A2=0};
static struct cow_frame frame2 = {.A1 = 30,.A2=30};
static struct cow_frame frame3 = {.A1 = 0,.A2=0};
static struct cow_frame frame4 = {.A1 = 0,.A2=0};
static struct cow_frame frame5 = {.A1 = 0,.A2=0};
static struct cow_frame frame6 = {.A1 = -30,.A2=-30};
static struct cow_frame frame7 = {.A1 = -60,.A2=-60};
static struct cow_frame frame8 = {.A1 = 0,.A2=-90};
// Both start at F0 
// F1 - F5
// F2 - F6
//90,90 F0- 90,90 

//45,90 F1- 90,90 
//60,60 F2- 120,120 //shift forward
//90,90 F3- 150,150 //shift forward
//--End of 1 step
//90,90 F4- 90,180 
//90,90 F5- 45,90
//120,120 F6- 60,60 //shift forward
//150,150 F7- 90,90 //shift forward
//90,180 F8 - 90,90 -> either to 1 or 0


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
	if(main_new_frame){
		if(my_cow_skeleton.body_point.x + cow_buffer > 50 || my_cow_skeleton.body_point.x - cow_buffer < -50){
			my_cow.is_moving = 0;
		}
		else if(my_cow_skeleton.body_point.y + cow_buffer > 50 || my_cow_skeleton.body_point.y - cow_buffer < -50){
			my_cow.is_moving = 0;
		}
		//printf("Calculating a new frame: %i\n", main_new_frame);
		if (my_cow.is_moving && my_cow.was_stopped){
			//printf("My Cow is starting to move %i\n",my_cow.is_moving);
			//Prepare to calculate a new skeleton position
			my_cow.new_frame = 1;
			//Set all the frames to be calculated
			my_cow.FRL = 1;
			my_cow.FLL = 5;
			my_cow.BLL = 1;
			my_cow.BRL = 5;
			//turn off stopped
			my_cow.was_stopped = 0;
		}
		else if (my_cow.is_moving){
			//printf("My Cow is still moving: %i\n",my_cow.is_moving);
			my_cow.new_frame = 1;
			my_cow.FRL += 1;
			my_cow.FLL += 1;
			my_cow.BLL += 1;
			my_cow.BRL += 1;
			my_cow.FRL = (my_cow.FRL % 9) + 1; //should put it back to frame 1
			my_cow.FLL = (my_cow.FLL % 9) + 1;
			my_cow.BLL = (my_cow.BLL % 9) + 1;
			my_cow.BRL = (my_cow.BRL % 9) + 1;
		}
		else if (my_cow.was_stopped){
			//printf("My Cow is stopped: %i\n",my_cow.was_stopped);
			//Set to standing still
			my_cow.new_frame = 1;
			my_cow.FRL = 0;
			my_cow.FLL = 0;
			my_cow.BLL = 0;
			my_cow.BRL = 0;
			my_cow.was_stopped = 1; //set stopped flag
		}
	}

	//Calculate the skeletons
	if(my_cow.new_frame){
		//Check if it is going to collide with the edge of the fence
		//no collision
		my_cow_skeleton.body_point.x += cos(deg2rad(my_cow_skeleton.body_orientation.z))*cow_move_speed;
		my_cow_skeleton.body_point.y += sin(deg2rad(my_cow_skeleton.body_orientation.z))*cow_move_speed;

		calculateCowSkeleton(my_cow.FRL,my_cow.FLL,my_cow.BRL,my_cow.BLL,&my_cow_skeleton); //animation frame and skeleton ptr
		my_cow.new_frame = 0;
	}
	//Render the cow
	drawCow(my_cow_skeleton);
	my_cow.skeleton = my_cow_skeleton;
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
	glTranslated(-2.5,-1,1.0); //Rear Leg Coordinate?
	drawCowLeg(my_cow_skeleton.LeftHindLeg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.5,1,1.0); //Rear Leg Coordinate?
	drawCowLeg(my_cow_skeleton.RightHindLeg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,-1,1.0); //Front Leg 
	drawCowLeg(my_cow_skeleton.LeftFrontLeg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,1,1.0); //Front Leg
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
	leg.upper_leg_pos.x = .5 * upper_leg_length * sin_ula;
	leg.upper_leg_pos.y = 0;
	leg.upper_leg_pos.z = (.5 * upper_leg_length * cos_ula);
	//Calculate the knee joint center point
	//printf("knee Position %f,0,%f\n",x_knee,z_knee);
	leg.knee_pos.x = upper_leg_length * sin_ula;
	leg.knee_pos.y = 0;
	leg.knee_pos.z = (upper_leg_length * cos_ula);
	double x_knee = leg.knee_pos.x;
	double z_knee = leg.knee_pos.z;
	//Calculate lower leg center point
	//double x_lower_leg = .5 * lower_leg_length * cos_lla + x_knee;
	//double z_lower_leg = -(.5 * lower_leg_length * sin_lla + z_knee;
	//printf("Lower Leg Position %f,0,%f\n",x_lower_leg,z_lower_leg);
	leg.lower_leg_pos.x = .5 * lower_leg_length * sin_lla + x_knee;
	leg.lower_leg_pos.y = 0;
	leg.lower_leg_pos.z = (.5 * lower_leg_length * cos_lla) + z_knee;
	//Calculate ankle center point
	//double x_ankle = lower_leg_length * cos_lla + x_knee;
	//double z_ankle = -(lower_leg_length * sin_lla) + z_knee;
	leg.ankle_pos.x = lower_leg_length * sin_lla + x_knee;
	leg.ankle_pos.y = 0;
	leg.ankle_pos.z = (lower_leg_length * cos_lla) + z_knee;
	//Hand off the angles
	leg.upper_leg_angle = upper_leg_angle;
	leg.lower_leg_angle = lower_leg_angle;
	*ptrleg = leg;
}

void calculateCowSkeleton(int frl,int fll, int brl, int bll, struct cow_skeleton *cow_skeleton_ptr){
	struct cow_skeleton my_skeleton = *cow_skeleton_ptr;
	//Using the animation frame, grab the corresponding skeleton frames
	double angle1 = getSkeletonAngle1FromFrame(fll); 
	double angle2 = getSkeletonAngle2FromFrame(fll);
	//Calcualte teh skeleton frames angles[0],angles[1],
	calculateCowLegSkeleton(angle1,angle2,&(my_skeleton.LeftFrontLeg));
	angle1 = getSkeletonAngle1FromFrame(frl); 
	angle2 = getSkeletonAngle2FromFrame(frl);
	calculateCowLegSkeleton(angle1,angle2,&(my_skeleton.RightFrontLeg));
	angle1 = getSkeletonAngle1FromFrame(bll); 
	angle2 = getSkeletonAngle2FromFrame(bll);
	calculateCowLegSkeleton(angle1,angle2,&(my_skeleton.LeftHindLeg));
	angle1 = getSkeletonAngle1FromFrame(brl); 
	angle2 = getSkeletonAngle2FromFrame(brl);
	calculateCowLegSkeleton(angle1,angle2,&(my_skeleton.RightHindLeg));
	//hand it back
	*cow_skeleton_ptr = my_skeleton;
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
	thiscow.is_moving = 1;
	thiscow.was_stopped = 1;
	thiscow.FRL = 0;
	thiscow.FLL = 0;
	thiscow.BLL = 0;
	thiscow.BRL = 0;
	//Next generate the center point of the cow
	//COW LIMITS on position
	thiscow.skeleton.body_point.x = random_at_most(60) - 30; //Should center around 0
	thiscow.skeleton.body_point.y = random_at_most(60) - 30; //should center around 0
	thiscow.skeleton.body_point.z = -5; //offset based on height of cow (TBD)
	//Next generate the orientation point of the cow
	thiscow.skeleton.body_orientation.x = 0; //ignore
	thiscow.skeleton.body_orientation.y = 0; //ignore
	thiscow.skeleton.body_orientation.z = random_at_most(359); //yaw angle (heading of cow)
	*ptrCow = thiscow;
}

//----------------------------------------------------------------------------------
//							COW ANIMATION FUNCTIONS
//----------------------------------------------------------------------------------

double getSkeletonAngle1FromFrame(int frameNumber){
	double retval = 0;
	switch(frameNumber){
		case 0:
			retval = frame0.A1;
			break;
		case 1:
			retval = frame1.A1;
			break;
		case 2:
			retval = frame2.A1;
			break;
		case 3:
			retval = frame3.A1;
			break;
		case 4:
			retval = frame4.A1;
			break;
		case 5:
			retval = frame5.A1;
			break;
		case 6:
			retval = frame6.A1;
			break;
		case 7:
			retval = frame7.A1;
			break;
		case 8:
			retval = frame8.A1;
			break;
	}
	return retval;
}

double getSkeletonAngle2FromFrame(int frameNumber){
	double retval = 0;
	switch(frameNumber){
		case 0:
			retval = frame0.A2;
			break;
		case 1:
			retval = frame1.A2;
			break;
		case 2:
			retval = frame2.A2;
			break;
		case 3:
			retval = frame3.A2;
			break;
		case 4:
			retval = frame4.A2;
			break;
		case 5:
			retval = frame5.A2;
			break;
		case 6:
			retval = frame6.A2;
			break;
		case 7:
			retval = frame7.A2;
			break;
		case 8:
			retval = frame8.A2;
			break;
	}
	return retval;
}


