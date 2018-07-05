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
#include "cow.h"			//drawing and tools for a cow object (CLASS)S
#include "helper.h"			//A set of helper functions like printing errors 
#include "main.h"
#define GL_GLEXT_PROTOTYPES

//Global variables
int number_of_cows;

//Prototypes
void display(); 
void drawAxis();
void printCowAngles();
void printViewing();
void Print(const char* format, ...);

void createObjects();
void cleanObjects();


#endif
