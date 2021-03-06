
/*
* Converting a spherical coordinate to cartesian coordinate
*/
#include "util.h"

//WEIRD BEHAVIOR AT CERTAIN POINTS; 90s 
/*
* Function to convert spherical to cartesian coordinates
*/
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

/*
* function to convert polar to cartesian coordinates
*/
double* polar2cartesianCoords(double r, double theta){
	theta = deg2rad(theta);
	double x = r * cos(theta);
	double y = r * sin(theta);

	static double retval[3];
	retval[0] = x;
	retval[1] = y;
	retval[2] = 0;

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

// Assumes 0 <= max <= RAND_MAX
// Returns in the closed interval [0, max]
// Author: Ryan Reich from Stackoverflow
long random_at_most(long max) {
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}

/*
* Cross Product Vector Calculation of A x B
*/

struct vector3 normalizeVector(struct vector3 a){
	double mag = (a.x*a.x) + (a.y*a.y) + (a.z * a.z);
	static struct vector3 norm;
	norm.x = a.x/mag;
	norm.y = a.y/mag;
	norm.z = a.z/mag;
	return norm;
}

struct vector3 cross_product(struct vector3 a, struct vector3 b){
	static struct vector3 c;
	c.x = a.y*b.z - a.z*b.y; //j x k
	c.y = a.z*b.x - a.x*b.z; //k x i
	c.z = a.x*b.y - a.y*b.x; //i x j
	return c;
}

double dot_product(struct vector3 a, struct vector3 b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}