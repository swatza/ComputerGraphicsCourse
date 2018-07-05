#ifndef RENDERING_H
#define RENDERING_H

//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GL/glut.h> 		//linux impl.
#include "keyboard.h" 		//keyboard interface
#include "util.h"			//useful math tools
#include "primitives.h"		//primitive drawing functions
#include "cow.h"			//drawing and tools for a cow object (CLASS)
#include "fence.h"			//drawing adn tools for a fence object (CLASS)
#include "helper.h"			//A set of helper functions like printing errors 
#include "lighting.h"		//tools for a light object (CLASS)
#include "materials.h"		//tools for setting materials
//#include "aircraft.h"
#include "main.h"
#define GL_GLEXT_PROTOTYPES

//Global variables
int number_of_cows;

//Prototypes
void display(); 
void drawAxis();
//void printAngles();
void printSettings();
void printModes();
void printCameraPosition();
void Print(const char* format, ...);

void createObjects();
void cleanObjects();


#endif
