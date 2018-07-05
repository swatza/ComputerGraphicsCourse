/*
* File for drawing the windmill structure with water pump
*
*/

#include "windmill.h"
#include "materials.h"

//Drawing Parameters
const double water_offset = 0.5;
const double container_bot_offset = 0.2;
const double container_height = 0.7;
const double container_outer_radius = 1.25;
const double container_inner_radius = 1.0;
//----------------
const float pump_structure_height = 10.0;
const float pump_structure_width = .75;
const float pump_strut_width = 1.0;
const float pump_tower_bot_width = 5.0; //inner limits
const float pump_tower_top_width = 1.5; //inner limits
const float pump_tower_top_height = 0.5;
//---------------
const float fan_length = 2.0;
const float fan_width = 0.75;
const float fan_thickness = 0.1;
const float rudder_length = 2.5;
const float rudder_height_f = 2.0;
const float rudder_height_b = 3.75;
//------------------
const float fan_tube_length = 2.7;
const float fan_tube_width = 1.2;


//const int d = 5; 
const int r = 1; const int h = 1;

//Draw a cylindrical container for storing water for the cows
void drawWaterContainer(unsigned int bot_text, unsigned int side_text, unsigned int inside_text){
	setMaterialForMetal();
	int th;
	int d = 5;
	float rep = 5;
	double * xyz;
	glPushMatrix();
	//Draw outer edge using cylinder method
	glBindTexture(GL_TEXTURE_2D,side_text);
	glBegin(GL_QUAD_STRIP);
	for (th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r*container_outer_radius,th);
		glTexCoord2f(1.0,th/360.0*rep); glNormal3f(xyz[0],xyz[1],0); glVertex3f(xyz[0],xyz[1],container_height);
		glTexCoord2f(0.0,th/360.0*rep); glNormal3f(xyz[0],xyz[1],0); glVertex3f(xyz[0],xyz[1],0);
	}
	glEnd();
	glPopMatrix();

	glPushMatrix();
	//Draw inner edge using cylinder method
	glBindTexture(GL_TEXTURE_2D,inside_text);
	glBegin(GL_QUAD_STRIP);
	for(th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r*container_inner_radius,th);
		glTexCoord2f(th/360.0*rep,0.0); glNormal3f(-xyz[0],-xyz[1],0); glVertex3f(xyz[0],xyz[1],container_bot_offset); 
		glTexCoord2f(th/360.0*rep,1.0); glNormal3f(-xyz[0],-xyz[1],0); glVertex3f(xyz[0],xyz[1],container_height);
	}
	glEnd();
	glPopMatrix();

	//Draw top Edge using Cylinder method 
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,bot_text);
	glBegin(GL_QUAD_STRIP);
	for (th=0; th<=360; th+=d){ //might want to move to 2
		xyz = polar2cartesianCoords(r*container_inner_radius,th); //inner
		//Since its the top edge ring
		glTexCoord2f(th/360.0*rep,0.0); glNormal3f(0,0,1); glVertex3f(xyz[0],xyz[1],container_height);
		xyz = polar2cartesianCoords(r*container_outer_radius,th); //outer
		glTexCoord2f(th/360.0*rep,1.0); glNormal3f(0,0,1); glVertex3f(xyz[0],xyz[1],container_height);
	}
	glEnd();
	glPopMatrix();

	//Draw inside bottom
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,inside_text);
	glScaled(container_inner_radius,container_inner_radius,1);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5,0.5); glNormal3f(0,0,1); glVertex3f(0,0,container_bot_offset); //Normal should point down
	for (th = 0; th <=360; th+=d){
		xyz = polar2cartesianCoords(r,th);
		glTexCoord2f(0.5+0.5*xyz[0], 0.5+0.5*xyz[1]); glNormal3f(0,0,1); glVertex3f(xyz[0],xyz[1],container_bot_offset);
	}
	glEnd();
	glPopMatrix();

	//Draw absolute bottom //no texture?
	
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,bot_text);
	glScaled(container_outer_radius,container_outer_radius,0); //scale it this way??
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5,0.5); glNormal3f(0,0,-1); glVertex3f(0,0,0); //Normal should point down
	for (th = 0; th <=360; th+=d){
		xyz = polar2cartesianCoords(r,th);
		glTexCoord2f(0.5+0.5*xyz[0], 0.5+0.5*xyz[1]); glNormal3f(0,0,-1); glVertex3f(xyz[0],xyz[1],0);
	}
	glEnd();
	glPopMatrix();

	ErrCheck("Draw water container");
}

//Draw a circle plane and then texture with water
//TODO! Make it transparent
void drawWater(unsigned int water_texture){
	setMaterialForWater();
	int th;
	int d = 5;
	double * xyz;
	glEnable(GL_BLEND);
	glColor4f(1,1,1,0.3);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(0);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,water_texture);
	glScaled(container_inner_radius,container_inner_radius,1);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5,0.5); glNormal3f(0,0,1); glVertex3f(0,0,water_offset);
	for (th = 0; th <=360; th+=d){
		xyz = polar2cartesianCoords(r,th);
		glTexCoord2f(0.5+0.5*xyz[0], 0.5+0.5*xyz[1]); glNormal3f(0,0,1); glVertex3f(xyz[0],xyz[1],water_offset);
	}
	glEnd();
	glPopMatrix();
	ErrCheck("Draw Water");
	glDepthMask(1);
	glDisable(GL_BLEND);
}

//==============================================================================================
//================================== WINDMILL PORTION ==========================================
//==============================================================================================
//This will draw all the parts and then make sure they are all positioned relative to each other
void drawWindmill(unsigned int support_text_1, unsigned int support_text_2, unsigned int tube_text, unsigned int platform_text, unsigned int metal_text1, unsigned int metal_text2){
	//Location and orientation??

	setMaterialForMetal();
	//Draw all of teh supporting structure first
	glPushMatrix();
	glTranslated(0,0,pump_structure_height);
	drawTopPlatform(platform_text,support_text_1);
	glPopMatrix();
	//Draw four supports
	glPushMatrix();
	drawMainWMSupport(support_text_1,support_text_2);
	glRotated(90,0.0,0.0,1.0);
	drawMainWMSupport(support_text_1,support_text_2);
	glRotated(90,0.0,0.0,1.0);
	drawMainWMSupport(support_text_1,support_text_2);
	glRotated(90,0.0,0.0,1.0);
	drawMainWMSupport(support_text_1,support_text_2);
	glPopMatrix();

	drawCrossBeamSupport(tube_text);
	//Now draw the top piece
	glPushMatrix();
	glTranslated(0,0,pump_structure_height+2.5);
	drawSwivelTube(tube_text);
	glTranslated(0,0,2.5);
	drawFanStructure(tube_text,metal_text1,metal_text2); //enclosed function to handle everything
	glPopMatrix();

	//Lastly add the fan 
	glPushMatrix();
	glTranslated(0,-4,pump_structure_height+5);
	glRotated(random_at_most(359),0,1,0);
	drawFan(metal_text1);
	glPopMatrix();
	
	ErrCheck("Draw Windmill");
}

//Draw a simple fan structure
void drawFanStructure(unsigned int tube_text, unsigned int metal_text, unsigned int scratched_metal){
	glRotated(90,1.0,0.0,0.0);
	glPushMatrix();
	//Draw a cylinder
	glScaled(fan_tube_width,fan_tube_width,3*fan_tube_length); 
	//glScaled(3,3,3);
	drawPipewTexture(tube_text,1);
	glPopMatrix();

	//Draw a regular cone
	glPushMatrix();
	glTranslated(0,0,-fan_tube_length*1.5);
	glRotated(180,1.0,0.0,0.0); // flip
	drawFanTailCone(tube_text);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0,fan_tube_length*1.5);
	drawFanNoseCone(tube_text);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0,-fan_tube_length-8);
	glScaled(0.05,0.05,10); //need to verify this size
	drawPipewTexture(metal_text,1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,0,-fan_tube_length-12);
	drawFanRudder(scratched_metal);
	glPopMatrix();

	//Finish
	ErrCheck("Draw Fan Structure");
}

void drawFanTailCone(unsigned int text){
	int r = 1;
	int h = 1;
	int d = 5; int th;
	double * xyz;
	glScaled(fan_tube_width,fan_tube_width,fan_tube_length);
	//using center point X distance away; draw a bunch of triangles to the center point 
	glBindTexture(GL_TEXTURE_2D,text);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5,0.5); glVertex3f(0,0,h);
	for (th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r,th);
		glNormal3f(xyz[0],xyz[1],sin(deg2rad(45))); //TODO Verify
		glTexCoord2f(th/360.0,0); glVertex3f(xyz[0],xyz[1],0);
	}
	glEnd();
	ErrCheck("Draw Fan Tail Cone");
}

//Draw a nose cone in front of teh blades on the fan structure
void drawFanNoseCone(unsigned int text){
	//TODO Draw a spherical cone
	glScaled(fan_tube_width,fan_tube_width,fan_tube_width);
	drawSpherewTexture(text);
	ErrCheck("Draw Fan Nose Cone");
}

//Draw the fan rudder at the tail end of the structure
void drawFanRudder(unsigned int text){
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,text);
	glRotated(90,1.0,0.0,0.0);
	glBegin(GL_QUAD_STRIP);
	//TODO! Not what i want
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(0,rudder_length/2,-rudder_height_f/2);
	glTexCoord2f(1,0); glVertex3f(0,rudder_length/2,rudder_height_f/2);
	glTexCoord2f(0,1); glVertex3f(0,-rudder_length/2,-rudder_height_b/2);
	glTexCoord2f(1,1); glVertex3f(0,-rudder_length/2,rudder_height_b/2);
	glEnd();
	glPopMatrix();
	ErrCheck("Draw Fan Rudder");
}

//Draw all the fan blades
void drawFan(unsigned int fanblade_text){
	int th;
	double* xyz;
	for (th=0;th<360;th+=60){
		xyz = polar2cartesianCoords(.85*fan_tube_width,th);
		glPushMatrix();
		//Rotate
		glTranslated(xyz[0],0,xyz[1]);
		glRotated(-th,0,1.0,0.0);
		glRotated(45,1.0,0.0,0.0);
		//Draw the blade
		drawFanBlade(fanblade_text);
		glPopMatrix();
	}
	ErrCheck("Draw Fan");
}

//Draw a small cylindrical beam: DEPRECIATED
void drawFanBeam(){
	glPushMatrix();
	glScaled(0.02,0.02,1.0);
	drawCylinder();
	glPopMatrix();
	ErrCheck("Fan Beam");
}

//Draw a single fan blade; Do experiments with drawing this!
void drawFanBlade(unsigned int texture){
	float hw = fan_width/2;
	//make sure to texture and set material to both sides for lighting
	glColor3f(0.3,0.0,0.0);
	glBindTexture(GL_TEXTURE_2D,texture);
	glPushMatrix();
	//Got set fix this object design 
	glBegin(GL_QUADS);
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(0,0,-hw);
	glTexCoord2f(0,1); glVertex3f(fan_length,0,-hw);
	glTexCoord2f(1,1); glVertex3f(fan_length,0,hw);
	glTexCoord2f(1,0); glVertex3f(0,0,hw);
	glEnd();
	glPopMatrix();
	ErrCheck("Draw Fan Blade");
	glColor3f(1.0,1.0,1.0);
}

//draw the tube that connects the fan part to the support structure
void drawSwivelTube(unsigned int text){
	glPushMatrix();
	glScaled(0.5,0.5,5);
	drawPipewTexture(text, 1);
	glPopMatrix();
	ErrCheck("Draw Swivel Tube");
}

//Draw teh little support platform at the top of the structure
void drawTopPlatform(unsigned int platform_text, unsigned int side_text){
	glPushMatrix();
	glScaled(pump_tower_top_width*2,pump_tower_top_width*2,pump_tower_top_height);
	
	glBindTexture(GL_TEXTURE_2D,platform_text);
	glBegin(GL_QUADS);
	//  Front
	glNormal3f(0,0,1);
	glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
	glTexCoord2f(0,1); glVertex3f(+1,-1, 1);
	glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
	glTexCoord2f(1,0); glVertex3f(-1,+1, 1);
	//  Back
	glNormal3f(0,0,-1);
	glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
	glTexCoord2f(0,1); glVertex3f(-1,-1,-1);
	glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
	glTexCoord2f(1,0); glVertex3f(+1,+1,-1);
	glEnd();
	//  Right
	glBindTexture(GL_TEXTURE_2D, side_text);
	glBegin(GL_QUADS);
	glNormal3f(1,0,0);
	glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
	glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
	glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
	glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
	//  Left
	glNormal3f(-1,0,0);
	glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
	glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
	glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
	glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
	//  Top
	glNormal3f(0,1,0);
	glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
	glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
	glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
	glTexCoord2f(1,0); glVertex3f(-1,+1,-1);
	//  Bottom
	glNormal3f(0,-1,0);
	glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
	glTexCoord2f(0,1); glVertex3f(+1,-1,-1);
	glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
	glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
	glEnd();
	//  End
	ErrCheck("Draw Platform");
	glPopMatrix();
}

//Draw cross beam supports using cylinders?
void drawCrossBeamSupport(unsigned int text){
	float height1 = 3;
	float height2 = 7;
	//calculate the angle between bottom to top of support; then figure out the Z location and the x/y to determine width
	float rad = 1.2341; //Could use arctan to do this
	//Calculate beam information at height 1
	float new_width = 5.5 + (3.5 - cos(rad)*height1);
	float x = 3.0 + cos(rad)*height1;
	float y = 3.0 + cos(rad)*height1;
	float z = height1;
	//Mirror around center of object
	for (int i =0; i < 4; i++){
		glPushMatrix();
		//glScaled(pump_strut_width,pump_strut_width,new_width);
		if (i == 0){
			glTranslated(0,y,z);
			glRotated(90,0.0,1.0,0.0);
		}
		else if (i == 1){
			glTranslated(0,-y,z);
			glRotated(90,0.0,1.0,0.0);
		}
		else if (i == 2){
			glTranslated(x,0,z);
			glRotated(90,1.0,0.0,0.0);
		}
		else if (i == 3){
			glTranslated(-x,0,z);
			glRotated(90,1.0,0.0,0.0);
		}
		
		glScaled(pump_strut_width/2,pump_strut_width/2,new_width);
		drawPipewTexture(text,1); //how do we not hand it a texture and still draw
		glPopMatrix();
	}
	//Calculate beam information at height 2
	x = 0.5 + cos(rad)*height2;
	y = 0.5 + cos(rad)*height2;
	z = height2;
	new_width = 5.0 + (3.5 - cos(rad)*height2);
	//Mirror around center of object
	for (int i =0; i < 4; i++){
		glPushMatrix();
		//glScaled(pump_strut_width,pump_strut_width,new_width);
		if (i == 0){
			glTranslated(0,y,z);
			glRotated(90,0.0,1.0,0.0);
		}
		else if (i == 1){
			glTranslated(0,-y,z);
			glRotated(90,0.0,1.0,0.0);
		}
		else if (i == 2){
			glTranslated(x,0,z);
			glRotated(90,1.0,0.0,0.0);
		}
		else if (i == 3){
			glTranslated(-x,0,z);
			glRotated(90,1.0,0.0,0.0);
		}
		
		glScaled(pump_strut_width/2,pump_strut_width/2,new_width);
		drawPipewTexture(text, 1); //how do we not hand it a texture and still draw
		glPopMatrix();
	}

	ErrCheck("Draw Cross Beam Supports");
}

//Draw one of the support structures 
void drawMainWMSupport(unsigned int beam1, unsigned int beam2){
	//TODO: add in a sign change depending on which support it is; or just mirror this x4 (look at teapot example)
	float botA_x = pump_tower_bot_width;
	float botB_x = pump_tower_bot_width + pump_structure_width;
	float botC_x = pump_tower_bot_width + pump_structure_width;
	float botD_x = pump_tower_bot_width;

	float topA_x = pump_tower_top_width;
	float topB_x = pump_tower_top_width + pump_structure_width;
	float topC_x = pump_tower_top_width + pump_structure_width;
	float topD_x = pump_tower_top_width;

	float botA_y = pump_tower_bot_width;
	float botB_y = pump_tower_bot_width;
	float botC_y = pump_tower_bot_width + pump_structure_width;
	float botD_y = pump_tower_bot_width + pump_structure_width;

	float topA_y = pump_tower_top_width;
	float topB_y = pump_tower_top_width;
	float topC_y = pump_tower_top_width + pump_structure_width;
	float topD_y = pump_tower_top_width + pump_structure_width;

	//Draw four quads that go up to the center point
	//glColor3f(1.0,0.0,0.0);
	struct vector3 L1;
	L1.x = topA_x - botA_x;
	L1.y = topA_y - botA_y;
	L1.z = pump_structure_height;
	struct vector3 L2; 
	L2.x = botB_x - botA_x;
	L2.y = botB_y - botA_y;
	L2.z = 0;
	struct vector3 L3;
	L3 = cross_product(L2,L1);
	L3 = normalizeVector(L3);

	glBindTexture(GL_TEXTURE_2D, beam1);
	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0,0); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(botA_x,botA_y,0.0); //bottom inside
	glTexCoord2f(1,0); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(botB_x,botB_y,0.0); //bottom outside
	glTexCoord2f(0,1); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(topA_x,topA_y,pump_structure_height); //top inside
	glTexCoord2f(1,1); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(topB_x,topB_y,pump_structure_height); //top outside
	glEnd();

	L1.x = topB_x - botB_x;
	L1.y = topB_y - botB_y;
	L1.z = pump_structure_height;
	L2.x = botC_x - botB_x;
	L2.y = botC_y - botB_y;
	L2.z = 0;
	L3 = cross_product(L2,L1);
	L3 = normalizeVector(L3);

	glBindTexture(GL_TEXTURE_2D, beam2);
	//glColor3f(0.0,1.0,0.0);
	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0,0); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(botB_x,botB_y,0.0);
	glTexCoord2f(1,0); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(botC_x,botC_y,0.0);
	glTexCoord2f(0,1); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(topB_x,topB_y,pump_structure_height);
	glTexCoord2f(1,1); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(topC_x,topC_y,pump_structure_height);
	glEnd();

	L1.x = topC_x - botC_x;
	L1.y = topC_y - botC_y;
	L1.z = pump_structure_height;
	L2.x = botD_x - botC_x;
	L2.y = botD_y - botC_y;
	L2.z = 0;
	L3 = cross_product(L2,L1);
	L3 = normalizeVector(L3);

	glBindTexture(GL_TEXTURE_2D, beam1);
	//glColor3f(0.0,0.0,1.0);
	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0,0); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(botC_x,botC_y,0.0);
	glTexCoord2f(1,0); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(botD_x,botD_y,0.0);
	glTexCoord2f(0,1); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(topC_x,topC_y,pump_structure_height);
	glTexCoord2f(1,1); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(topD_x,topD_y,pump_structure_height);
	glEnd();

	L1.x = topD_x - botD_x;
	L1.y = topD_y - botD_y;
	L1.z = pump_structure_height;
	L2.x = botA_x - botD_x;
	L2.y = botA_y - botD_y;
	L2.z = 0;
	L3 = cross_product(L2,L1);
	L3 = normalizeVector(L3);

	glBindTexture(GL_TEXTURE_2D, beam2);
	//glColor3f(1.0,1.0,0.0);
	glBegin(GL_QUAD_STRIP);
	glTexCoord2f(0,0); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(botD_x,botD_y,0.0);
	glTexCoord2f(1,0); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(botA_x,botA_y,0.0);
	glTexCoord2f(0,1); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(topD_x,topD_y,pump_structure_height);
	glTexCoord2f(1,1); glNormal3f(L3.x,L3.y,L3.z); glVertex3f(topA_x,topA_y,pump_structure_height);
	glEnd();
}

//=======================================================

void drawHayBale(unsigned int texture_face, unsigned int texture_side){
	setMaterialForGrass();
	int width = 5;
	int length = 5;
	glPushMatrix();
	glScaled(width,width,length*2);
	drawPipewTexture(texture_side,3);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0,length);
	glScaled(width,width,0);
	drawCylinderFacewTexture(texture_face);
	glPopMatrix();
	glPushMatrix();
	glTranslated(0,0,-length);
	glRotated(180,1.0,0.0,0.0); //flip face
	glScaled(width,width,0);
	drawCylinderFacewTexture(texture_face);
	glPopMatrix();
}