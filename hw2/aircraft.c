
#include "aircraft.h"

initializeLoiterDrone(struct aircraft* my_aircraft_ptr,double alt, double rad, double airspeed_factor){
	struct aircraft my_aircraft = *my_aircraft_ptr;
	//initialize position
	my_aircraft.position.x = rad;
	my_aircraft.position.y = 0;
	my_aircraft.position.z = alt;
	double theta = rad2deg(atan(x/y));
	//initialize orientation
	my_aircraft.orientation.x = 0;
	my_aircraft.orientation.y = 0;
	my_aircraft.orientation.z = theta;
	//initialize velocity
	my_aircraft.airspeed = (rad*rad*3.1415)/(10*airspeed_factor);
	*my_aircraft_ptr = my_aircraft;
}


moveAirplaneOneFrame(struct aircraft* my_aircraft_ptr){
	struct aircraft my_aircraft = *my_aircraft_ptr;

	//calculate new position
	my_aircraft.position.x += my_aircraft.airspeed * cos(deg2rad(theta));
	my_aircraft.position.y += my_aircraft.airspeed * sin(deg2rad(theta));

	//Calculate new heading
	my_aircraft.orientation.z = rad2deg(atan(x/y));
	*my_aircraft_ptr = my_aircraft;
}

renderAircraftObject(struct aircraft* my_aircraft_ptr){
	struct aircraft my_aircraft = *my_aircraft_ptr;
	drawAircraft(my_aircraft);
}


drawAircraft(struct aircraft my_plane){
	
}
