//A library for drawing unit primitives that can then be transformed, scaled and rotated with the position at teh center poitn of teh shape

//---------
//INCLUDES!
//---------
#include "primitives.h"
#include "helper.h"
#include "util.h"

//Constants for rendering
const int d = 5;


// Check Normals
// Draw new shapes 
// Texture shapes (Can we actually add texture coordinates to primitives if we don't know how the texture will actually be?)

//draw a vertex in spherical coordinates (Probably just remove this)
/*
* Function to makea 3D vertex with color both based on the angles so it has some kind of appearance
* Original by Willem A. (Vlakkies) Schreuder
*/
void drawVertex(double th,double ph, float s, int mode){
	//Draw Polar vertex
	double* xyz = spherical2cartesianCoords(1,th,ph,0,0,0);
	if(mode){
		glTexCoord2f(s,th/360.0);
	}else{
		glTexCoord2f(th/360.0,s);
	}
	glNormal3f(xyz[0],xyz[1],xyz[2]);
	glVertex3f(xyz[0],xyz[1],xyz[2]);
}

/*
* Draw a 2D Plane
*/
void drawPlanewTexture(unsigned int text){
	glBindTexture(GL_TEXTURE_2D,text);
	
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0,0.0); glVertex3f(-1,-1,0);

	glNormal3f(0,0,1);
	glTexCoord2f(0.0,1.0); glVertex3f(-1,1,0);

	glNormal3f(0,0,1);
	glTexCoord2f(1.0,1.0); glVertex3f(1,1,0);

	glNormal3f(0,0,1);
	glTexCoord2f(1.0,0.0); glVertex3f(1,-1,0);

	glEnd();
	ErrCheck("DrawPlane With Texture");
}

/*
* Draw a Cube 
* Original by Willem A. (Vlakkies) Schreuder
*/
void drawCube(){
	glBegin(GL_QUADS);
	//  Front
	glColor3f(1,0,0);
	glNormal3f(0,0,1);
	glVertex3f(-1,-1, 1);
	glVertex3f(+1,-1, 1);
	glVertex3f(+1,+1, 1);
	glVertex3f(-1,+1, 1);
	//  Back
	glColor3f(0,0,1);
	glNormal3f(0,0,-1);
	glVertex3f(+1,-1,-1);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,+1,-1);
	glVertex3f(+1,+1,-1);
	//  Right
	glColor3f(1,1,0);
	glNormal3f(1,0,0);
	glVertex3f(+1,-1,+1);
	glVertex3f(+1,-1,-1);
	glVertex3f(+1,+1,-1);
	glVertex3f(+1,+1,+1);
	//  Left
	glColor3f(0,1,0);
	glNormal3f(-1,0,0);
	glVertex3f(-1,-1,-1);
	glVertex3f(-1,-1,+1);
	glVertex3f(-1,+1,+1);
	glVertex3f(-1,+1,-1);
	//  Top
	glColor3f(0,1,1);
	glNormal3f(0,1,0);
	glVertex3f(-1,+1,+1);
	glVertex3f(+1,+1,+1);
	glVertex3f(+1,+1,-1);
	glVertex3f(-1,+1,-1);
	//  Bottom
	glColor3f(1,0,1);
	glNormal3f(0,-1,0);
	glVertex3f(-1,-1,-1);
	glVertex3f(+1,-1,-1);
	glVertex3f(+1,-1,+1);
	glVertex3f(-1,-1,+1);
	//  End
	glEnd();
	ErrCheck("DrawCube");
}

/*
* Draw a Pyramid
*/
void drawRectangularPyramid(){
	//TODO
}

/*
* Draw a cylinder
*/
void drawCylinder(){
	int th;
	double h = 1;
	int r = 1;
	double * xyz;
	//Draw Top
	glBegin(GL_TRIANGLE_FAN);
	//Draw center point
	glNormal3f(0,0,1);
	glColor3f(1.0,0.0,0.0);
	glVertex3f(0,0,h/2);
	//loop through
	for(th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r,th);
		glNormal3f(0,0,1);
		glVertex3f(xyz[0],xyz[1],h/2);
	}
	glEnd();
	ErrCheck("Finished Top");

	//Draw Middle *GREEN*
	glBegin(GL_QUAD_STRIP);
	glColor3f(0.0,1.0,0.0);
	for (th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r,th);
		glNormal3f(xyz[0],xyz[1],0); //IS THIS RIGHT?
		glVertex3f(xyz[0],xyz[1],h/2);
		glVertex3f(xyz[0],xyz[1],-h/2);
	}
	glEnd();
	ErrCheck("Finished Middle Portion");
	
	//Draw Bottom  *BLUE*
	glBegin(GL_TRIANGLE_FAN);
	//Draw center point;
	glNormal3f(0,0,-1);
	glColor3f(0.0,0.0,1.0);	
	glVertex3f(0,0,-h/2);
	//Loop through
	for(th=0;th<=360;th+=d){
		//Draw the vertexs
		//Get x and Y position
		xyz = polar2cartesianCoords(r,th);
		glNormal3f(0,0,-1);
		glVertex3f(xyz[0],xyz[1],-h/2);
	}
	glEnd();
	ErrCheck("End of Cylinder");
}


/*
* Like a cylinder, except that there is no caps and there is no thickness
*/
void drawPipewTexture(int unsigned text){
	double r = 1;
	double h = 1;
	double th;
	double* xyz;
	glBindTexture(GL_TEXTURE_2D,text);

	glBegin(GL_QUAD_STRIP);
	for (th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r,th);
		glNormal3f(xyz[0],xyz[1],0);
		glTexCoord2f(th/360.0,0.0); glVertex3f(xyz[0],xyz[1],h/2);
		glTexCoord2f(th/360.0,1.0); glVertex3f(xyz[0],xyz[1],-h/2);
	}
	glEnd();
	ErrCheck("Finished Middle Portion");
}

//Draw Sphere (is a specific type of an ellipsoid)
void drawSpherewTexture(unsigned int text){
	drawEllipsoidwTexture(1,1,1,text,0);
}

/*
* Draw Ellipsoid
* Original by Willem A. (Vlakkies) Schreuder
*/
void drawEllipsoidwTexture(double a, double b, double c, unsigned int text, int textmode){
	int th,ph;
	glPushMatrix();
	glScaled(a,b,c);
	glBindTexture(GL_TEXTURE_2D,text);
	for (ph=-90;ph<90;ph+=d)
	{
		glBegin(GL_QUAD_STRIP);
		for (th=0;th<=360;th+=d)
		{
			float s = 0.5 + ph/180.0;
			float s2 = 0.5 + (ph+d)/180.0;
			drawVertex(th,ph,s,textmode);
			drawVertex(th,ph+d,s2,textmode);
		}
		glEnd();
	}
	ErrCheck("drawEllipsoid");
	glPopMatrix();
}
