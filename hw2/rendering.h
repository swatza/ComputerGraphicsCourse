#ifndef RENDERING_H
#define RENDERING_H

//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <GL/glut.h> //linux 
#include "keyboard.h"
#include "util.h"
#include "primitives.h"
#include "cow.h"
#include "fence.h"
#include "helper.h"
//#include "aircraft.h"
#include "main.h"
#define GL_GLEXT_PROTOTYPES

//Global variables
int number_of_cows;

//Prototypes
void display(); 
void drawAxis();
//void printAngles();
void printModes();
void printCameraPosition();
void Print(const char* format, ...);

void createObjects();
void cleanObjects();


#endif
