#ifndef UTIL_H
#define UTIL_H

//INCLUDES
#include <math.h>
#include <stdlib.h>

//Struct Definitions
typedef struct vector3 vector3;
typedef struct mesh_collider mesh_collider;

//Prototypes
double* spherical2cartesianCoords(double r, double theta, double phi, double rx,double ry,double rz);
double* polar2cartesianCoords(double r, double theta);
double deg2rad(double deg);
double rad2deg(double rad);
long random_at_most(long max);

//Struct Implementations
struct vector3{
	double x;
	double y;
	double z;
};

struct mesh_collider{
	//RECTANGLE
	double d;
	double w;
	double h;
};

#endif