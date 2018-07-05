//Includes
#include "cow.h"
#include "materials.h"

//COW CONSTANTS
const double upper_leg_length = 1.0;
const double upper_leg_width = .25;
const double lower_leg_length = 1.0;
const double lower_leg_width = .25;
const double ankle_height = 0.25;

const double cow_move_speed = .05;
const double cow_buffer = 5.5;
const double cow_z_offset = -3;

const double body_length = 5;
const double body_width = 2.0;
const double body_height = 1.5;

const double head_length = 1;
const double head_width = 1.5;
const double head_height = 1.2;

//ANIMATION FRAMES
struct cow_frame** walking_frames;
int number_of_walking_frames = 12;
struct cow_frame* cow_standing_frame;

struct cow_frame** dancing_frames;
int number_of_dancing_frames = 10;

//----------------------------------------------------------------------------------
//							DRAW COW FUNCTIONS
//----------------------------------------------------------------------------------

void drawDancingCow(struct cow_skeleton my_cow_skeleton, unsigned int cow_body_text, unsigned int cow_head_text){
	glTranslated(my_cow_skeleton.body_point.x,my_cow_skeleton.body_point.z+8,my_cow_skeleton.body_point.y);
	glRotated(my_cow_skeleton.body_orientation.z,0,1,0);
	glRotated(90,0,0,1);
	glRotated(90,1,0,0);
	glColor3f(1.0,1.0,1.0);//reset to white
	setMaterialForCow();
	glPushMatrix();
	//glTranslated(my_cow_skeleton.body_point.x,my_cow_skeleton.body_point.y,my_cow_skeleton.body_point.z);
	drawCowTorso(cow_body_text);
	//Draw the head
	glPushMatrix();
	glTranslated(4.5,0,-0.4);
	drawCowHead(cow_head_text);
	glPopMatrix();

	//Now shift the cow leg
	glPushMatrix();
	glTranslated(-2.5,-1.5,1.0); //Rear Leg Coordinate?
	drawCowLeg(my_cow_skeleton.LeftHindLeg, cow_body_text);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.5,1.5,1.0); //Rear Leg Coordinate?
	drawCowLeg(my_cow_skeleton.RightHindLeg, cow_body_text);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,-1.5,1.0); //Front Leg 
	drawCowLeg(my_cow_skeleton.LeftFrontLeg, cow_body_text);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,1.5,1.0); //Front Leg
	drawCowLeg(my_cow_skeleton.RightFrontLeg, cow_body_text);
	glPopMatrix();

	glPopMatrix();
}

/*
* Function to draw all parts of a cow
*/
void drawCow(struct cow_skeleton my_cow_skeleton, unsigned int cow_body_text, unsigned int cow_head_text){
	glRotated(90,1.0,0,0);///aligns cows properly with ground. 
	glColor3f(1.0,1.0,1.0);//reset to white
	setMaterialForCow();
	glPushMatrix();
	glTranslated(my_cow_skeleton.body_point.x,my_cow_skeleton.body_point.y,my_cow_skeleton.body_point.z);
	glRotated(my_cow_skeleton.body_orientation.z, 0.0,0.0,1.0);
	glRotated(my_cow_skeleton.body_orientation.y, 0.0,1.0,0.0);
	glRotated(my_cow_skeleton.body_orientation.x, 1.0,0.0,0.0);
	drawCowTorso(cow_body_text);
	//Draw the head
	glPushMatrix();
	glTranslated(4.5,0,-0.4);
	drawCowHead(cow_head_text);
	glPopMatrix();

	//Now shift the cow leg
	glPushMatrix();
	glTranslated(-2.5,-1.5,1.0); //Rear Leg Coordinate?
	drawCowLeg(my_cow_skeleton.LeftHindLeg, cow_body_text);
	glPopMatrix();

	glPushMatrix();
	glTranslated(-2.5,1.5,1.0); //Rear Leg Coordinate?
	drawCowLeg(my_cow_skeleton.RightHindLeg, cow_body_text);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,-1.5,1.0); //Front Leg 
	drawCowLeg(my_cow_skeleton.LeftFrontLeg, cow_body_text);
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.5,1.5,1.0); //Front Leg
	drawCowLeg(my_cow_skeleton.RightFrontLeg, cow_body_text);
	glPopMatrix();

	glPopMatrix();
}

/*
* Draw a cow torso
*/
void drawCowTorso(unsigned int body_texture){
	drawEllipsoidwTexture(body_length,body_width,body_height,body_texture,0);
}

/*
* Draw a cow's leg based on skeleton data of the join locations
*/
void drawCowLeg(struct cow_leg_skeleton leg, unsigned int body_texture){
	//Using the angles and positions gathered from the skeleton leg
	//printf("Upper Leg Position %f,0,%f\n",leg.upper_leg_pos.x, leg.upper_leg_pos.z);
	//printf("Lower Leg Position %f,0,%f\n",leg.lower_leg_pos.x, leg.lower_leg_pos.z);
	//HIP
	glColor3f(1.0,1.0,1.0);
	glPushMatrix();
	glScaled(upper_leg_width,upper_leg_width,upper_leg_width);
	drawSpherewTexture(body_texture);
	glPopMatrix();
	//UPPER LEG
	glPushMatrix(); //Save the transformations
	glTranslated(leg.upper_leg_pos.x,leg.upper_leg_pos.y, leg.upper_leg_pos.z);
	glRotatef(-leg.upper_leg_angle.x,1.0,0.0,0.0);
	glRotatef(-leg.upper_leg_angle.y,0.0,1.0,0.0);
	glRotatef(0,0.0,0.0,1.0);
	//glRotatef(leg.upper_leg_angle.y,0.0,1.0,0.0);
	//glRotatef(leg.upper_leg_angle.x,-1.0,0.0,0.0); 
	glScaled(upper_leg_width, upper_leg_width, leg.upper_leg_length);
	//drawPipewTexture(body_texture);
	drawLeg(body_texture);
	glPopMatrix(); //Undo the transformations
	//KNEE
	glPushMatrix(); //Do i Need to do a glPush?
	glTranslated(leg.knee_pos.x, leg.knee_pos.y, leg.knee_pos.z);
	glScaled(upper_leg_width,upper_leg_width,upper_leg_width);
	drawSpherewTexture(body_texture);
	glPopMatrix();
	//LOWER LEG
	glPushMatrix();
	glTranslated(leg.lower_leg_pos.x, leg.lower_leg_pos.y, leg.lower_leg_pos.z);
	glRotatef(-leg.lower_leg_angle.x,1.0,0.0,0.0);
	glRotatef(-leg.lower_leg_angle.y,0.0,1.0,0.0);
	glRotatef(0,0.0,0.0,1.0);
	glScaled(lower_leg_width, lower_leg_width, leg.lower_leg_length);
	//drawPipewTexture(body_texture);
	drawLeg(body_texture);
	glPopMatrix();
	//ANKLE TODO
	glPushMatrix();
	glColor3f(0.0,0.0,0.0);
	glTranslated(leg.ankle_pos.x, leg.ankle_pos.y, leg.ankle_pos.z);
	glScaled(lower_leg_width,lower_leg_width,ankle_height);
	drawCylinder();
	glPopMatrix();

}

/*
* Draw the cow head 
*/
void drawCowHead(unsigned int head_texture){
	drawEllipsoidwTexture(head_length,head_width,head_height,head_texture,1);
	glPushMatrix();
	glTranslated(-4.5,0,+0.4);
	drawHorns();
	drawEars();
	glPopMatrix();
}

/*
* draw some baby horns on the cow
*/
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

/*
* Draw some baby ears on teh cow
*/
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

void drawLeg(int unsigned text){
	double r = 1;
	double h = 1;
	double th;
	int d = 5;
	double* xyz;
	glBindTexture(GL_TEXTURE_2D,text);

	glBegin(GL_QUAD_STRIP);
	for (th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r,th);
		glNormal3f(xyz[0],xyz[1],0);
		glTexCoord2f(th/360.0,0.0); glVertex3f(xyz[0],xyz[1],0);
		glTexCoord2f(th/360.0,1.0); glVertex3f(xyz[0],xyz[1],h);
	}
	glEnd();
}

//----------------------------------------------------------------------------------
//							SKELETON FUNCTIONS
//----------------------------------------------------------------------------------

/*
* calculate the joint locations of the cow leg based on leg angles
*/
void calculateCowLegSkeleton(struct vector3 upper_leg_angle, struct vector3 lower_leg_angle, struct cow_leg_skeleton *ptrleg){
	struct cow_leg_skeleton leg = *ptrleg;
	//Leg
	struct vector3 upperLeg;
	upperLeg.x = 0;
	upperLeg.y = 0;
	upperLeg.z = upper_leg_length;
	struct vector3 lowerLeg;
	lowerLeg.x = 0;
	lowerLeg.y = 0;
	lowerLeg.z = lower_leg_length;
	//Variables
	double* xyz;

	//Position the knee joint
	xyz = Rotation321(upper_leg_angle.z,upper_leg_angle.y,upper_leg_angle.x,upperLeg);
	leg.knee_pos.x = xyz[0];
	leg.knee_pos.y = xyz[1];
	leg.knee_pos.z = xyz[2];

	//Position the ankle joint
	xyz = Rotation321(lower_leg_angle.z, lower_leg_angle.y, lower_leg_angle.x, lowerLeg);
	leg.ankle_pos.x = xyz[0] + leg.knee_pos.x;
	leg.ankle_pos.y = xyz[1] + leg.knee_pos.y;
	leg.ankle_pos.z = xyz[2] + leg.knee_pos.z;

	//Calculate the halfway position between knee and hip for upper leg point (Could we just draw a new leg item?)
	leg.upper_leg_pos.x = 0;
	leg.upper_leg_pos.y = 0;
	leg.upper_leg_pos.z = 0;

	leg.lower_leg_pos.x = leg.knee_pos.x;
	leg.lower_leg_pos.y = leg.knee_pos.y;
	leg.lower_leg_pos.z = leg.knee_pos.z;

	//Track the size of the leg
	leg.upper_leg_length = upper_leg_length;//distance(leg.knee_pos,zerovector);
	leg.lower_leg_length = lower_leg_length;//distance(leg.ankle_pos,leg.knee_pos);

	//Hand over the angles
	leg.upper_leg_angle = upper_leg_angle;
	leg.lower_leg_angle = lower_leg_angle;
	//Return
	*ptrleg = leg;
}

/*
* Using the skeleton of a cow, figure out which frame (pose the cow's legs are in) and calculate the new skeleton pose
*/
void calculateCowSkeleton(struct cow_frame new_frame, struct cow_object *cow_ptr){
	struct cow_skeleton my_skeleton = cow_ptr->skeleton;
	//Using the animation frame, grab the corresponding skeleton frames
	struct vector3 angle1;
	struct vector3 angle2;
	angle1.x = new_frame.LeftArm.ULX;
	angle1.y = new_frame.LeftArm.ULY;
	angle1.z = 0;
	angle2.x = new_frame.LeftArm.LLX;
	angle2.y = new_frame.LeftArm.LLY;
	angle2.z = 0;
	calculateCowLegSkeleton(angle1,angle2,&(my_skeleton.LeftFrontLeg));
	angle1.x = new_frame.RightArm.ULX;
	angle1.y = new_frame.RightArm.ULY;
	angle1.z = 0;
	angle2.x = new_frame.RightArm.LLX;
	angle2.y = new_frame.RightArm.LLY;
	angle2.z = 0;
	calculateCowLegSkeleton(angle1,angle2,&(my_skeleton.RightFrontLeg));
	angle1.x = new_frame.LeftLeg.ULX;
	angle1.y = new_frame.LeftLeg.ULY;
	angle1.z = 0;
	angle2.x = new_frame.LeftLeg.LLX;
	angle2.y = new_frame.LeftLeg.LLY;
	angle2.z = 0;
	calculateCowLegSkeleton(angle1,angle2,&(my_skeleton.LeftHindLeg));
	angle1.x = new_frame.RightLeg.ULX;
	angle1.y = new_frame.RightLeg.ULY;
	angle1.z = 0;
	angle2.x = new_frame.RightLeg.LLX;
	angle2.y = new_frame.RightLeg.LLY;
	angle2.z = 0;
	calculateCowLegSkeleton(angle1,angle2,&(my_skeleton.RightHindLeg));
	//hand it back
	cow_ptr->skeleton = my_skeleton;
}

//----------------------------------------------------------------------------------
//							COW INITIALIZATION FUNCTIONS
//----------------------------------------------------------------------------------

/*
* Simple random cow generation code that sets cow values and randomizes it into the pen
*/
void initializeCowObject(struct cow_object *ptrCow, int index){
	cow_object thiscow = *ptrCow;
	//First set the name and index
	thiscow.object_name = "BasicCow";
	thiscow.object_identifier = index;

	thiscow.isStanding = 0;
	//thiscow.was_stopped = 1;
	thiscow.key_frame_number = 0;
	thiscow.move_type = 1; //random_at_most(1); //0 is standing, 1 is walking

	//Next generate the center point of the cow
	//COW LIMITS on position
	thiscow.skeleton.body_point.x = random_at_most(150) - 75; //Should center around 0
	thiscow.skeleton.body_point.y = random_at_most(150) - 75; //should center around 0
	thiscow.skeleton.body_point.z = cow_z_offset; //offset based on height of cow (TBD)
	//Next generate the orientation point of the cow
	thiscow.skeleton.body_orientation.x = 0; //ignore
	thiscow.skeleton.body_orientation.y = 0; //ignore
	thiscow.skeleton.body_orientation.z = random_at_most(359); //yaw angle (heading of cow)
	*ptrCow = thiscow;
}

//----------------------------------------------------------------------------------
//							COW Animation Functions
//----------------------------------------------------------------------------------

//The animation/waiting timer function determines how to best figure out the number we are going to draw
void determineFrameToDraw(struct cow_object *ptrCow,int flag, int steps, int number){
	//Move the draw frame buffer one
	ptrCow->last_frame_drawn = ptrCow->frame_to_draw;
	//Check Walking condition
	if(ptrCow->move_type == 1){

		//Increment the keyframe if necessary
		if(flag){
			ptrCow->key_frame_number += 1;
			//reset the motion if its for walking
			if(ptrCow->key_frame_number == number_of_walking_frames){
				ptrCow->key_frame_number = 0;
			}
		}

		//Figure out what is the next key frame
		int key_frame0 = ptrCow->key_frame_number;
		int next_frame = key_frame0 + 1;

		//We hit the end; start over
		if(next_frame == number_of_walking_frames){
			next_frame = 0;
		}

		//Shift the cow's body slightly to match feet motion
		ptrCow->skeleton.body_point.x += cos(deg2rad(ptrCow->skeleton.body_orientation.z))*cow_move_speed;
		ptrCow->skeleton.body_point.y += sin(deg2rad(ptrCow->skeleton.body_orientation.z))*cow_move_speed;

		//Calculate the inbetweens
		AnimateBetweenKeyFrames(ptrCow, ptrCow->move_type, key_frame0, next_frame, steps, number);
	}
	else if(ptrCow->move_type == 2){
		//Increment the keyframe if necessary
		if(flag){
			ptrCow->key_frame_number += 1;
			//reset the motion if its for walking
			if(ptrCow->key_frame_number == number_of_dancing_frames){
				ptrCow->key_frame_number = 0;
			}
		}

		//Figure out what is the next key frame
		int key_frame0 = ptrCow->key_frame_number;
		int next_frame = key_frame0 + 1;

		//We hit the end; start over
		if(next_frame == number_of_dancing_frames){
			next_frame = 0;
		}

		//Calculate the inbetweens
		AnimateBetweenKeyFrames(ptrCow, ptrCow->move_type, key_frame0, next_frame, steps, number);
	}
	//Check Stopped Condition
	else if(ptrCow->move_type == 0){
		//just keep redrawing the same standing position
		ptrCow->frame_to_draw = *cow_standing_frame; 
	}

}

void AnimateBetweenKeyFrames(struct cow_object *ptrCow, int move_type, int keyframe0, int keyframe1, int number_of_steps, int step_number){
	//struct cow_object thiscow = *ptrCow;
	struct cow_frame out_frame; //could we just hand this the full ptr to the cow skeleton?
	double* output;
	struct cow_frame cf0; 
	struct cow_frame cf1;

	//Walking
	if(move_type == 1){
		cf0 = *walking_frames[keyframe0];
		cf1 = *walking_frames[keyframe1];
	}
	else{
		cf0 = *dancing_frames[keyframe0];
		cf1 = *dancing_frames[keyframe1];
	}
	//Dancing??

	//Calculate between angles
	output = AnglesBetweenLimbs(cf0.LeftLeg, cf1.LeftLeg);
	out_frame.LeftLeg.ULX = output[0]/number_of_steps * 1.0 * step_number + cf0.LeftLeg.ULX;
	out_frame.LeftLeg.ULY = output[1]/number_of_steps * 1.0 * step_number + cf0.LeftLeg.ULY;
	out_frame.LeftLeg.LLX = output[2]/number_of_steps * 1.0 * step_number + cf0.LeftLeg.LLX;
	out_frame.LeftLeg.LLY = output[3]/number_of_steps * 1.0 * step_number + cf0.LeftLeg.LLY;

	output = AnglesBetweenLimbs(cf0.RightLeg, cf1.RightLeg);
	out_frame.RightLeg.ULX = output[0]/number_of_steps * 1.0 * step_number + cf0.RightLeg.ULX;;
	out_frame.RightLeg.ULY = output[1]/number_of_steps * 1.0 * step_number + cf0.RightLeg.ULY;;
	out_frame.RightLeg.LLX = output[2]/number_of_steps * 1.0 * step_number + cf0.RightLeg.LLX;;
	out_frame.RightLeg.LLY = output[3]/number_of_steps * 1.0 * step_number + cf0.RightLeg.LLY;;

	output = AnglesBetweenLimbs(cf0.LeftArm, cf1.LeftArm);
	out_frame.LeftArm.ULX = output[0]/number_of_steps * 1.0 * step_number + cf0.LeftArm.ULX;;
	out_frame.LeftArm.ULY = output[1]/number_of_steps * 1.0 * step_number + cf0.LeftArm.ULY;;
	out_frame.LeftArm.LLX = output[2]/number_of_steps * 1.0 * step_number + cf0.LeftArm.LLX;;
	out_frame.LeftArm.LLY = output[3]/number_of_steps * 1.0 * step_number + cf0.LeftArm.LLY;;

	output = AnglesBetweenLimbs(cf0.RightArm, cf1.RightArm);
	out_frame.RightArm.ULX = output[0]/number_of_steps * 1.0 * step_number + cf0.RightArm.ULX;;
	out_frame.RightArm.ULY = output[1]/number_of_steps * 1.0 * step_number + cf0.RightArm.ULY;;
	out_frame.RightArm.LLX = output[2]/number_of_steps * 1.0 * step_number + cf0.RightArm.LLX;;
	out_frame.RightArm.LLY = output[3]/number_of_steps * 1.0 * step_number + cf0.RightArm.LLY;;
	//Finished inbetween frame calculation
	//Hand over the next frame
	ptrCow->frame_to_draw = out_frame;
}

double* AnglesBetweenLimbs(struct cow_limb_angles L1, struct cow_limb_angles L2){
	static double retvals[4];
	retvals[0] = L2.ULX - L1.ULX;
	retvals[1] = L2.ULY - L1.ULY;
	retvals[2] = L2.LLX - L1.LLX;
	retvals[3] = L2.LLY - L1.LLY;
	return retvals;
}

void createWalkingFrames(){
	walking_frames = (struct cow_frame**)malloc(sizeof(struct cow_frame*) * number_of_walking_frames);
	struct cow_frame walking_frame_0;
	struct cow_frame walking_frame_1;
	struct cow_frame walking_frame_2;
	struct cow_frame walking_frame_3;
	struct cow_frame walking_frame_4;
	struct cow_frame walking_frame_5;
	struct cow_frame walking_frame_6;
	struct cow_frame walking_frame_7;
	struct cow_frame walking_frame_8;
	struct cow_frame walking_frame_9;
	struct cow_frame walking_frame_10;
	struct cow_frame walking_frame_11;

	walking_frame_0.LeftLeg.ULX = 0;
	walking_frame_0.LeftLeg.ULY = -30;
	walking_frame_0.LeftLeg.LLX = 0;
	walking_frame_0.LeftLeg.LLY = 30;

	walking_frame_0.RightLeg.ULX = 0;
	walking_frame_0.RightLeg.ULY = 0;
	walking_frame_0.RightLeg.LLX = 0;
	walking_frame_0.RightLeg.LLY = 0;

	walking_frame_0.RightArm = walking_frame_0.LeftLeg;
	walking_frame_0.LeftArm = walking_frame_0.RightLeg;

	walking_frame_1.LeftLeg.ULX = 0;
	walking_frame_1.LeftLeg.ULY = -40;
	walking_frame_1.LeftLeg.LLX = 0;
	walking_frame_1.LeftLeg.LLY = 0;

	walking_frame_1.RightLeg.ULX = 0;
	walking_frame_1.RightLeg.ULY = 0;
	walking_frame_1.RightLeg.LLX = 0;
	walking_frame_1.RightLeg.LLY = 0;

	walking_frame_1.RightArm = walking_frame_1.LeftLeg;
	walking_frame_1.LeftArm = walking_frame_1.RightLeg;

	walking_frame_2.LeftLeg.ULX = 0;
	walking_frame_2.LeftLeg.ULY = -30;
	walking_frame_2.LeftLeg.LLX = 0;
	walking_frame_2.LeftLeg.LLY = -15;

	walking_frame_2.RightLeg.ULX = 0;
	walking_frame_2.RightLeg.ULY = 15;
	walking_frame_2.RightLeg.LLX = 0;
	walking_frame_2.RightLeg.LLY = 0;

	walking_frame_2.RightArm = walking_frame_2.LeftLeg;
	walking_frame_2.LeftArm = walking_frame_2.RightLeg;

	walking_frame_3.LeftLeg.ULX = 0;
	walking_frame_3.LeftLeg.ULY = -10;
	walking_frame_3.LeftLeg.LLX = 0;
	walking_frame_3.LeftLeg.LLY = 0;

	walking_frame_3.RightLeg.ULX = 0;
	walking_frame_3.RightLeg.ULY = 30;
	walking_frame_3.RightLeg.LLX = 0;
	walking_frame_3.RightLeg.LLY = 15;

	walking_frame_3.RightArm = walking_frame_3.LeftLeg;
	walking_frame_3.LeftArm = walking_frame_3.RightLeg;

	walking_frame_4.LeftLeg.ULX = 0;
	walking_frame_4.LeftLeg.ULY = 0;
	walking_frame_4.LeftLeg.LLX = 0;
	walking_frame_4.LeftLeg.LLY = 0;

	walking_frame_4.RightLeg.ULX = 0;
	walking_frame_4.RightLeg.ULY = 35;
	walking_frame_4.RightLeg.LLX = 0;
	walking_frame_4.RightLeg.LLY = 25;

	walking_frame_4.RightArm = walking_frame_4.LeftLeg;
	walking_frame_4.LeftArm = walking_frame_4.RightLeg;

	walking_frame_5.LeftLeg.ULX = 0;
	walking_frame_5.LeftLeg.ULY = 0;
	walking_frame_5.LeftLeg.LLX = 0;
	walking_frame_5.LeftLeg.LLY = 0;

	walking_frame_5.RightLeg.ULX = 0;
	walking_frame_5.RightLeg.ULY = -20;
	walking_frame_5.RightLeg.LLX = 0;
	walking_frame_5.RightLeg.LLY = 45;

	walking_frame_5.RightArm = walking_frame_5.LeftLeg;
	walking_frame_5.LeftArm = walking_frame_5.RightLeg;

	//Beginning Repeat on other leg
	walking_frame_6.RightLeg = walking_frame_0.LeftLeg;
	walking_frame_7.RightLeg = walking_frame_1.LeftLeg;
	walking_frame_8.RightLeg = walking_frame_2.LeftLeg;
	walking_frame_9.RightLeg = walking_frame_3.LeftLeg;
	walking_frame_10.RightLeg = walking_frame_4.LeftLeg;
	walking_frame_11.RightLeg = walking_frame_5.LeftLeg;

	walking_frame_6.LeftLeg = walking_frame_0.RightLeg;
	walking_frame_7.LeftLeg = walking_frame_1.RightLeg;
	walking_frame_8.LeftLeg = walking_frame_2.RightLeg;
	walking_frame_9.LeftLeg = walking_frame_3.RightLeg;
	walking_frame_10.LeftLeg = walking_frame_4.RightLeg;
	walking_frame_11.LeftLeg = walking_frame_5.RightLeg;

	walking_frame_6.RightArm = walking_frame_6.LeftLeg;
	walking_frame_6.LeftArm = walking_frame_6.RightLeg;
	walking_frame_7.RightArm = walking_frame_7.LeftLeg;
	walking_frame_7.LeftArm = walking_frame_7.RightLeg;
	walking_frame_8.RightArm = walking_frame_8.LeftLeg;
	walking_frame_8.LeftArm = walking_frame_8.RightLeg;
	walking_frame_9.RightArm = walking_frame_9.LeftLeg;
	walking_frame_9.LeftArm = walking_frame_9.RightLeg;
	walking_frame_10.RightArm = walking_frame_10.LeftLeg;
	walking_frame_10.LeftArm = walking_frame_10.RightLeg;
	walking_frame_11.RightArm = walking_frame_11.LeftLeg;
	walking_frame_11.LeftArm = walking_frame_11.RightLeg;

	//Hand to the memory thing
	for (int i =0; i < number_of_walking_frames; i++){
		struct cow_frame *my_cow_frame_ptr = (struct cow_frame*)malloc(sizeof(struct cow_frame));
		if(i==0)
			*my_cow_frame_ptr = walking_frame_0;
		else if(i==1)
			*my_cow_frame_ptr = walking_frame_1;
		else if(i==2)
			*my_cow_frame_ptr = walking_frame_2;
		else if(i==3)
			*my_cow_frame_ptr = walking_frame_3;
		else if(i==4)
			*my_cow_frame_ptr = walking_frame_4;
		else if(i==5)
			*my_cow_frame_ptr = walking_frame_5;
		else if(i==6)
			*my_cow_frame_ptr = walking_frame_6;
		else if(i==7)
			*my_cow_frame_ptr = walking_frame_7;
		else if(i==8)
			*my_cow_frame_ptr = walking_frame_8;
		else if(i==9)
			*my_cow_frame_ptr = walking_frame_9;
		else if(i==10)
			*my_cow_frame_ptr = walking_frame_10;
		else if(i==1)
			*my_cow_frame_ptr = walking_frame_11;
		walking_frames[i] = my_cow_frame_ptr;
	}
}

void createStandingFrame(){
	struct cow_frame standing_frame;
	standing_frame.LeftLeg.ULX = 0;
	standing_frame.LeftLeg.ULY = 0;
	standing_frame.LeftLeg.LLX = 0;
	standing_frame.LeftLeg.LLY = 0;
	standing_frame.RightLeg.ULX = 0;
	standing_frame.RightLeg.ULY = 0;
	standing_frame.RightLeg.LLX = 0;
	standing_frame.RightLeg.LLY = 0;
	standing_frame.LeftArm.ULX = 0;
	standing_frame.LeftArm.ULY = 0;
	standing_frame.LeftArm.LLX = 0;
	standing_frame.LeftArm.LLY = 0;
	standing_frame.RightArm.ULX = 0;
	standing_frame.RightArm.ULY = 0;
	standing_frame.RightArm.LLX = 0;
	standing_frame.RightArm.LLY = 0;

	cow_standing_frame = malloc(sizeof(struct cow_frame));
	*cow_standing_frame = standing_frame;
}

void createDancingFrame(){
	dancing_frames = (struct cow_frame**)malloc(sizeof(struct cow_frame*) * number_of_dancing_frames);
	struct cow_frame dancing_frame_0;
	struct cow_frame dancing_frame_1;
	struct cow_frame dancing_frame_2;
	struct cow_frame dancing_frame_3;
	struct cow_frame dancing_frame_4;
	struct cow_frame dancing_frame_5;
	struct cow_frame dancing_frame_6;
	struct cow_frame dancing_frame_7;
	struct cow_frame dancing_frame_8;
	struct cow_frame dancing_frame_9;

	dancing_frame_0.LeftLeg.ULX = 0;
	dancing_frame_0.LeftLeg.ULY = 90;
	dancing_frame_0.LeftLeg.LLX = 0;
	dancing_frame_0.LeftLeg.LLY = 90;

	dancing_frame_0.RightLeg = dancing_frame_0.LeftLeg;

	dancing_frame_1.LeftLeg.ULX = 0;
	dancing_frame_1.LeftLeg.ULY = 30;
	dancing_frame_1.LeftLeg.LLX = 0;
	dancing_frame_1.LeftLeg.LLY = 90;

	dancing_frame_1.RightLeg = dancing_frame_0.LeftLeg;

	dancing_frame_2.LeftLeg.ULX = 0;
	dancing_frame_2.LeftLeg.ULY = 30;
	dancing_frame_2.LeftLeg.LLX = 0;
	dancing_frame_2.LeftLeg.LLY = 40;

	dancing_frame_2.RightLeg = dancing_frame_0.LeftLeg;

	dancing_frame_3.LeftLeg.ULX = 0;
	dancing_frame_3.LeftLeg.ULY = 60;
	dancing_frame_3.LeftLeg.LLX = 0;
	dancing_frame_3.LeftLeg.LLY = 50;

	dancing_frame_3.RightLeg = dancing_frame_0.LeftLeg;

	dancing_frame_4.LeftLeg.ULX = 0;
	dancing_frame_4.LeftLeg.ULY = 90;
	dancing_frame_4.LeftLeg.LLX = 0;
	dancing_frame_4.LeftLeg.LLY = 90;

	dancing_frame_4.RightLeg = dancing_frame_0.LeftLeg;

	//Repeat Leg Pattern with other foot

	dancing_frame_5.RightLeg = dancing_frame_0.LeftLeg;
	dancing_frame_6.RightLeg = dancing_frame_1.LeftLeg;
	dancing_frame_7.RightLeg = dancing_frame_2.LeftLeg;
	dancing_frame_8.RightLeg = dancing_frame_3.LeftLeg;
	dancing_frame_9.RightLeg = dancing_frame_4.LeftLeg;

	dancing_frame_5.LeftLeg = dancing_frame_0.LeftLeg;
	dancing_frame_6.LeftLeg = dancing_frame_0.LeftLeg;
	dancing_frame_7.LeftLeg = dancing_frame_0.LeftLeg;
	dancing_frame_8.LeftLeg = dancing_frame_0.LeftLeg;
	dancing_frame_9.LeftLeg = dancing_frame_0.LeftLeg;

	//Arm Pattern
	dancing_frame_0.LeftArm.ULX = -50;
	dancing_frame_0.LeftArm.ULY = 55;
	dancing_frame_0.LeftArm.LLX = 0;
	dancing_frame_0.LeftArm.LLY = 0;

	dancing_frame_0.RightArm.ULX = 50;
	dancing_frame_0.RightArm.ULY = 55;
	dancing_frame_0.RightArm.LLX = 0;
	dancing_frame_0.RightArm.LLY = 0;

	dancing_frame_1.LeftArm.ULX = -50;
	dancing_frame_1.LeftArm.ULY =  55;
	dancing_frame_1.LeftArm.LLX = 0;
	dancing_frame_1.LeftArm.LLY = 0;

	dancing_frame_1.RightArm.ULX = 50;
	dancing_frame_1.RightArm.ULY = -20;
	dancing_frame_1.RightArm.LLX = 67;
	dancing_frame_1.RightArm.LLY = 40;

	dancing_frame_2.LeftArm.ULX = -50;
	dancing_frame_2.LeftArm.ULY =  55;
	dancing_frame_2.LeftArm.LLX = 0;
	dancing_frame_2.LeftArm.LLY = 0;

	dancing_frame_2.RightArm.ULX = 77;
	dancing_frame_2.RightArm.ULY = -36;
	dancing_frame_2.RightArm.LLX = 90;
	dancing_frame_2.RightArm.LLY = -35;

	dancing_frame_3.LeftArm.ULX = -50;
	dancing_frame_3.LeftArm.ULY =  55;
	dancing_frame_3.LeftArm.LLX = 0;
	dancing_frame_3.LeftArm.LLY = 0;

	dancing_frame_3.RightArm = dancing_frame_1.RightArm;
	dancing_frame_3.LeftArm = dancing_frame_3.LeftArm;
	dancing_frame_4.RightArm = dancing_frame_0.RightArm;
	dancing_frame_4.LeftArm = dancing_frame_3.LeftArm;

	dancing_frame_5.LeftArm.ULX = -50;
	dancing_frame_5.LeftArm.ULY = 55;
	dancing_frame_5.LeftArm.LLX = 0;
	dancing_frame_5.LeftArm.LLY = 0;

	dancing_frame_5.RightArm.ULX = 50;
	dancing_frame_5.RightArm.ULY = 55;
	dancing_frame_5.RightArm.LLX = 0;
	dancing_frame_5.RightArm.LLY = 0;

	dancing_frame_6.LeftArm.ULX = -50;
	dancing_frame_6.LeftArm.ULY = -20;
	dancing_frame_6.LeftArm.LLX = -67;
	dancing_frame_6.LeftArm.LLY = 40;

	dancing_frame_6.RightArm.ULX = 50;
	dancing_frame_6.RightArm.ULY = 55;
	dancing_frame_6.RightArm.LLX = 0;
	dancing_frame_6.RightArm.LLY = 0;

	dancing_frame_7.LeftArm.ULX = -77;
	dancing_frame_7.LeftArm.ULY = -36;
	dancing_frame_7.LeftArm.LLX = -90;
	dancing_frame_7.LeftArm.LLY = -35;

	dancing_frame_7.RightArm.ULX = 50;
	dancing_frame_7.RightArm.ULY = 55;
	dancing_frame_7.RightArm.LLX = 0;
	dancing_frame_7.RightArm.LLY = 0;

	dancing_frame_8.LeftArm = dancing_frame_6.LeftArm;
	dancing_frame_9.LeftArm = dancing_frame_5.LeftArm;
	dancing_frame_8.RightArm = dancing_frame_7.RightArm;
	dancing_frame_9.RightArm = dancing_frame_7.RightArm;

	for (int i =0; i < number_of_dancing_frames; i++){
		struct cow_frame *my_cow_frame_ptr = (struct cow_frame*)malloc(sizeof(struct cow_frame));
		if(i==0)
			*my_cow_frame_ptr = dancing_frame_0;
		else if(i==1)
			*my_cow_frame_ptr = dancing_frame_1;
		else if(i==2)
			*my_cow_frame_ptr = dancing_frame_2;
		else if(i==3)
			*my_cow_frame_ptr = dancing_frame_3;
		else if(i==4)
			*my_cow_frame_ptr = dancing_frame_4;
		else if(i==5)
			*my_cow_frame_ptr = dancing_frame_5;
		else if(i==6)
			*my_cow_frame_ptr = dancing_frame_6;
		else if(i==7)
			*my_cow_frame_ptr = dancing_frame_7;
		else if(i==8)
			*my_cow_frame_ptr = dancing_frame_8;
		else if(i==9)
			*my_cow_frame_ptr = dancing_frame_9;
		dancing_frames[i] = my_cow_frame_ptr;
	}

}