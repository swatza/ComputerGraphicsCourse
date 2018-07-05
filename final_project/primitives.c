//A library for drawing unit primitives that can then be transformed, scaled and rotated with the position at teh center poitn of teh shape

//---------
//INCLUDES!
//---------
#include "primitives.h"
#include "helper.h"
#include "util.h"

//Constants for rendering

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
	//ErrCheck("Draw Vertex");
}

/*
* Draw a 2D Plane
*/
void drawPlanewTexture(unsigned int text){
	glBindTexture(GL_TEXTURE_2D,text);
	glBegin(GL_QUADS);
	glNormal3f(0,0,1);
	glTexCoord2f(0.0,0.0); glNormal3f(0,0,1); glVertex3f(-1,-1,0);
	glTexCoord2f(0.0,1.0); glNormal3f(0,0,1); glVertex3f(-1,1,0);
	glTexCoord2f(1.0,1.0); glNormal3f(0,0,1); glVertex3f(1,1,0);
	glTexCoord2f(1.0,0.0); glNormal3f(0,0,1); glVertex3f(1,-1,0);
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
* Draw a cylinder
*/
void drawCylinder(){
	int th;
	int d = 5;
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

void drawCylinderFacewTexture(int unsigned text){
	double* xyz;
	int th;
	int r = 1;
	int d = 5;
	glBindTexture(GL_TEXTURE_2D,text);
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(0.5,0.5); glNormal3f(0,0,1); glVertex3f(0,0,0);
	for(th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r,th);
		glTexCoord2f(xyz[0]*0.5 + 0.5,xyz[1]*0.5+0.5); glNormal3f(0,0,1); glVertex3f(xyz[0],xyz[1],0);
	}
	glEnd();
}


/*
* Like a cylinder, except that there is no caps and there is no thickness
*/
void drawPipewTexture(int unsigned text, float rep){
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
		glTexCoord2f(th/360.0*rep,0.0); glVertex3f(xyz[0],xyz[1],h/2);
		glTexCoord2f(th/360.0*rep,1.0); glVertex3f(xyz[0],xyz[1],-h/2);
	}
	glEnd();
	ErrCheck("Draw Pipe w Texture");
}

void drawPipe(){
	double r = 1; double h = 1;
	int th; int d = 5;
	double* xyz;
	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	for(th=0;th<=360;th+=d){
		xyz = polar2cartesianCoords(r,th);
		glNormal3f(xyz[0],xyz[1],0);
		glVertex3f(xyz[0],xyz[1],h/2);
		glVertex3f(xyz[0],xyz[1],-h/2);
	}
	glEnd();
	glPopMatrix();

	ErrCheck("Draw Pipe");
}

//Draw Sphere (is a specific type of an ellipsoid)
void drawSpherewTexture(unsigned int text){
	drawEllipsoidwTexture(1,1,1,text,0);
}

void drawSphere(){
	drawEllipsoid(1,1,1);
}

/*
* Draw Ellipsoid
* Original by Willem A. (Vlakkies) Schreuder
*/
void drawEllipsoidwTexture(double a, double b, double c, unsigned int text, int textmode){
	int th,ph;
	int d = 5;
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
	glPopMatrix();
	ErrCheck("draw Ellipsoid w txt");
}

void drawEllipsoid(double a, double b, double c){
	int th, ph;
	int d =5;
	glPushMatrix();
	glScaled(a,b,c);
	for(ph=-90;ph<90;ph+=d){
		glBegin(GL_QUAD_STRIP);
		for(th=0;th<=360;th+=d){
			float s = 0.5 + ph/180.0;
			float s2 = 0.5 + (ph+d)/180.0;
			drawVertex(th,ph,s,0);
			drawVertex(th,ph+d,s2,0);
		}
		glEnd();
	}
	glPopMatrix();
	ErrCheck("draw Ellipsoid");
}

void drawSkyBoxModified(double dimensions, unsigned int face1, unsigned int face2, unsigned int face34, unsigned int face5, unsigned int face6){
	double D = 8*dimensions;
	double top = 2*dimensions;
	glColor3f(1,1,1);
	//Start with the four sides
	glBindTexture(GL_TEXTURE_2D,face1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.00,0); glVertex3f(-D,0,-D);
	glTexCoord2f(1,0); glVertex3f(+D,0,-D);
	glTexCoord2f(1,1); glVertex3f(+D,top,-D);
	glTexCoord2f(0.00,1); glVertex3f(-D,top,-D);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,face2);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(+D,-1,-D);
	glTexCoord2f(1,0); glVertex3f(+D,-1,+D);
	glTexCoord2f(1,1); glVertex3f(+D,top,+D);
	glTexCoord2f(0,1); glVertex3f(+D,top,-D);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,face34);
	glBegin(GL_QUADS);
	glTexCoord2f(0,0); glVertex3f(+D,-1,+D);
	glTexCoord2f(0.5,0); glVertex3f(-D,-1,+D);
	glTexCoord2f(0.5,1); glVertex3f(-D,top,+D);
	glTexCoord2f(0,1); glVertex3f(+D,top,+D);

	glTexCoord2f(0.5,0); glVertex3f(-D,-1,+D);
	glTexCoord2f(1.00,0); glVertex3f(-D,-1,-D);
	glTexCoord2f(1.00,1); glVertex3f(-D,top,-D);
	glTexCoord2f(0.5,1); glVertex3f(-D,top,+D);
	glEnd();

	//Top
	glBindTexture(GL_TEXTURE_2D,face5);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0,0); glVertex3f(+D,top,-D);
	glTexCoord2f(1,0); glVertex3f(+D,top,+D);
	glTexCoord2f(1,1); glVertex3f(-D,top,+D);
	glTexCoord2f(0.0,1); glVertex3f(-D,top,-D);
	glEnd();

	//Bottom (this looks slightly wrong)
	glBindTexture(GL_TEXTURE_2D,face6);
	glBegin(GL_QUADS);
	glTexCoord2f(1,0); glVertex3f(-D,-1,+D);
	glTexCoord2f(1,1); glVertex3f(+D,-1,+D);
	glTexCoord2f(0,1); glVertex3f(+D,-1,-D);
	glTexCoord2f(0,0); glVertex3f(-D,-1,-D);
	glEnd();
	ErrCheck("Draw SkyBox Modified");

}