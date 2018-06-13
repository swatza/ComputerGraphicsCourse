
/*
* Converting a spherical coordinate to cartesian coordinate
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "util.h"

double* spherical2cartesianCoords(double r,double theta, double phi, double rx, double ry, double rz){
	theta = deg2rad(theta);
	phi = deg2rad(phi);
	//convert a spherical coordinate point into cartesian using a reference x,y,z
	double x = r * sin(theta)*cos(phi) + rx;
	double y = r * sin(theta)*sin(phi) + ry;
	double z = r * cos(theta) + rz;

	static double retval[3];
	retval[0] = x;
	retval[1] = y;
	retval[2] = z;

	return retval; 
}

double deg2rad(double deg){
	double rad = deg * 3.1415927/180;
	return rad;
}

double rad2deg(double rad){
	double deg = rad * 180/3.1415927;
	return deg;
}