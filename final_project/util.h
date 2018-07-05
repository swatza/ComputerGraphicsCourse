#ifndef UTIL_H
#define UTIL_H

//INCLUDES
#include <math.h>
#include <stdlib.h>

//Struct Definitions
typedef struct vector3 vector3;
typedef struct mesh_collider mesh_collider;

//Prototypes
double* RotationMatrix1(double angle, struct vector3 vector);
double* RotationMatrix2(double angle, struct vector3 vector);
double* RotationMatrix3(double angle, struct vector3 vector);
double* Rotation321(double angle1, double angle2, double angle3, struct vector3 vectorIn);
double* Rotation123(double angle1, double angle2, double angle3, struct vector3 vectorIn);

double* stereographicProjection_Sphere2Plane(double x, double y, double z);
double* stereographicProjection_Plane2Sphere(double X, double Y);

double distance(struct vector3 b, struct vector3 a);

double* spherical2cartesianCoords(double r, double theta, double phi, double rx,double ry,double rz);
double* polar2cartesianCoords(double r, double theta);
double deg2rad(double deg);
double rad2deg(double rad);
long random_at_most(long max);

struct vector3 normalizeVector(struct vector3 a);
struct vector3 cross_product(struct vector3 a, struct vector3 b);
double dot_product(struct vector3 a, struct vector3 b);

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