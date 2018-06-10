#ifndef LORENZ_H
#define LORENZ_H

extern double lorenz_parameter_s;
extern double lorenz_parameter_b;
extern double lorenz_parameter_r;

//Functions
double** getLorenzPoints(int numberOfIntegrations);
double* getNextLorenzPoint(double* previousCoords, double timestep);
int test(); 

#endif