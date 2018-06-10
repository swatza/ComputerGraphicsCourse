#ifndef LORENZ_H
#define LORENZ_H

//Functions
double** getLorenzPoints(int numberOfIntegrations);
double* getNextLorenzPoint(double* previousCoords, double timestep);
int test(); 

#endif