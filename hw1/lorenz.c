/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 * Original by Professor
 */

#include <stdio.h>
#include "lorenz.h"

/*  Lorenz Parameters  */
double lorenz_parameter_s  = 10;
double lorenz_parameter_b  = 2.6666;
double lorenz_parameter_r  = 28;

double** getLorenzPoints(int numberOfIntegrations){
  //loop through all the coordinates
  int i;
  double Coords[3];
  double output[numberOfIntegrations][3]
  Coords[0] = 1; // x
  Coords[1] = 1; // y 
  Coords[2] = 1; // z
  //print debug output
  /* time step */
  double dt = 0.001; //integration
  //Loop through all euler integration
  for (i=0;i<numberOfIntegrations;i++){
    Coords = getNextLorenzPoint(Coords,dt);
    //How are we gonna store these
    output[i] = Coords; //i have no idea if this right 
  }
}

double* getNextLorenzPoint(double[] previousCoords, double timestep){
  //first calculate the derivative points
  double dx = lorenz_parameter_s*(y-x);
  double dy = x*(lorenz_parameter_r-z)-y;
  double dz = x*y - lorenz_parameter_b*z;
  //Next integrate basic
  previousCoords[0] += timestep * dx;
  previousCoords[1] += timestep * dy; 
  previousCoords[2] += timestep * dz;
  //Return teh array of coordinates
  return previousCoords;
}

/*
 *  Main
 */
int test()
{
   int i;
   /*  Coordinates  */
   double x = 1;
   double y = 1;
   double z = 1;
   /*  Time step  */
   double dt = 0.001;

   printf("%5d %8.3f %8.3f %8.3f\n",0,x,y,z);
   /*
    *  Integrate 50,000 steps (50 time units with dt = 0.001)
    *  Explicit Euler integration
    */
   for (i=0;i<50000;i++)
   {
      double dx = s*(y-x);
      double dy = x*(r-z)-y;
      double dz = x*y - b*z;
      x += dt*dx;
      y += dt*dy;
      z += dt*dz;
      printf("%5d %8.3f %8.3f %8.3f\n",i+1,x,y,z);
   }
   return 0;
}