#ifndef AIRCRAFT_H
#define AIRCRAFT_H

//INCLUDES
#include "util.h"
#include "primitives.h"

//STRUCT DEFINITIONS
typedef struct aircraft aircraft;

//PROTOTYPES
initializeLoiterDrone(struct aircraft* my_aircraft_ptr,double alt, double rad, double airspeed_factor);
moveAirplaneOneFrame(struct aircraft* my_aircraft_ptr);

//STRUCT IMPLEMENTATIOn
struct aircraft{
	vector3 position;
	vector3 orientation;
	double airspeed;
}


#endif