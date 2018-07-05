
/*
* Converting a spherical coordinate to cartesian coordinate
*/
#include "util.h"


double* RotationMatrix3(double angle, struct vector3 vector){
	double ca = cos(deg2rad(angle));
	double sa = sin(deg2rad(angle));
	static double retval[3];
	retval[0] = vector.x * ca + vector.y * sa;
	retval[1] = -vector.x * sa + vector.y * ca;
	retval[2] = vector.z;
	return retval;
}

double* RotationMatrix2(double angle, struct vector3 vector){
	double ca = cos(deg2rad(angle));
	double sa = sin(deg2rad(angle));
	static double retval[3];
	retval[0] = vector.x * ca - vector.z * sa;
	retval[1] = vector.y;
	retval[2] = vector.x * sa + vector.z * ca;
	return retval;
}

double* RotationMatrix1(double angle, struct vector3 vector){
	double ca = cos(deg2rad(angle));
	double sa = sin(deg2rad(angle));
	static double retval[3];
	retval[0] = vector.x;
	retval[1] = vector.y * ca + vector.z * sa;
	retval[2] = -vector.y * sa + vector.z * ca;
	return retval;
}

double* Rotation123(double angle1, double angle2, double angle3, struct vector3 vectorIn){
	double* xyz;
	static double retval[3];
	xyz = RotationMatrix1(angle1,vectorIn);
	vectorIn.x = xyz[0];
	vectorIn.y = xyz[1];
	vectorIn.z = xyz[2];
	xyz = RotationMatrix2(angle2,vectorIn);
	vectorIn.x = xyz[0];
	vectorIn.y = xyz[1];
	vectorIn.z = xyz[2];
	xyz = RotationMatrix3(angle3,vectorIn);
	retval[0] = xyz[0];
	retval[1] = xyz[1];
	retval[2] = xyz[2];
	return retval;
}

double* Rotation321(double angle1, double angle2, double angle3, struct vector3 vectorIn){
	double* xyz;
	static double retval[3];
	xyz = RotationMatrix3(angle1,vectorIn);
	vectorIn.x = xyz[0];
	vectorIn.y = xyz[1];
	vectorIn.z = xyz[2];
	xyz = RotationMatrix2(angle2,vectorIn);
	vectorIn.x = xyz[0];
	vectorIn.y = xyz[1];
	vectorIn.z = xyz[2];
	xyz = RotationMatrix1(angle3,vectorIn);
	retval[0] = xyz[0];
	retval[1] = xyz[1];
	retval[2] = xyz[2];
	return retval;
}

double* stereographicProjection_Sphere2Plane(double x, double y, double z){
	static double retval[2];
	retval[0] = x / (1-z);
	retval[1] = y / (1-z);
	return retval;
}

double* stereographicProjection_Plane2Sphere(double X, double Y){

	double bottom = 1 + X*X + Y*Y;	
	static double retval[3];
	retval[0] = 2*X/bottom;
	retval[1] = 2*Y/bottom;
	retval[2] = (-1 + X*X + Y*Y)/bottom;
	return retval;
}

double distance(struct vector3 b, struct vector3 a){
	return sqrt( (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z));
}

//WEIRD BEHAVIOR AT CERTAIN POINTS; 90s 
/*
* Function to convert spherical to cartesian coordinates
*/
double* spherical2cartesianCoords(double r, double theta, double phi, double rx, double ry, double rz){
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

//A x B
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