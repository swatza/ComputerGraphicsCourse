#ifndef UTIL_H
#define UTIL_H

//Structs
typedef struct vector3 vector3;
struct vector3{
	double x;
	double y;
	double z;
};

//Prototypes
double* spherical2cartesianCoords(double r, double theta, double phi, double rx,double ry,double rz);
double* polar2cartesianCoords(double r, double theta);
double deg2rad(double deg);
double rad2deg(double rad);

#endif