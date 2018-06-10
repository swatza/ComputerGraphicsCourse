/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 * Original by Professor
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lorenz.h"
#include "keyboard.h"
#include "rendering.h"

/*  Lorenz Parameters  */

double** getLorenzPoints(int numberOfIntegrations){
  //loop through all the coordinates
  int i;
  double Coords[3];
  //double output[numberOfIntegrations][3];
  double output[numberOfIntegrations][3];
  //printf("Initialized Variables inside Lorenz Points\n");
  Coords[0] = 1; // x
  Coords[1] = 1; // y 
  Coords[2] = 1; // z
  //printf("Set the initial coordinates\n");
  //print debug output
  /* time step */
  double dt = 0.001; //integration
  //Loop through all euler integration
  for (i=0;i<numberOfIntegrations;i++){
    double* ptr = getNextLorenzPoint(Coords,dt);
    Coords[0] = ptr[0];
    Coords[1] = ptr[1];
    Coords[2] = ptr[2];
    //printf("Successfully handed the results to coords\n");
    //How are we gonna store these
    output[i][0] = Coords[0]; //i have no idea if this right 
    output[i][1] = Coords[1];
    output[i][2] = Coords[2];
    //printf("Successfully stored outputs\n");
  }
  return &output;
}

double* getNextLorenzPoint(double* previousCoords, double timestep){
  //printf("Starting next lorenz point\n");
  double x = previousCoords[0];
  double y = previousCoords[1];
  double z = previousCoords[2];
  //first calculate the derivative points
  double dx = lorenz_parameter_s*(y-x);
  double dy = x*(lorenz_parameter_r-z)-y;
  double dz = x*y - lorenz_parameter_b*z;
  //printf("Calculated delta values\n");
  //Next integrate basic
  previousCoords[0] += timestep * dx;
  previousCoords[1] += timestep * dy; 
  previousCoords[2] += timestep * dz;
  //Return teh array of coordinates
  //printf("Set new coordinates\n");
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
      double dx = lorenz_parameter_s*(y-x);
      double dy = x*(lorenz_parameter_r-z)-y;
      double dz = x*y - lorenz_parameter_b*z;
      x += dt*dx;
      y += dt*dy;
      z += dt*dz;
      printf("%5d %8.3f %8.3f %8.3f\n",i+1,x,y,z);
   }
   return 0;
}
