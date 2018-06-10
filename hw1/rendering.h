#ifndef RENDERING_H
#define RENDERING_H

//#define GL_GLEXT_PROTOTYPES
extern int number_of_points;

//Functions
void display(); //function prorotype for rendering
void draw3DLine(double* values, int size);
void drawAxis();
void printAngles();
void printVariables();
void drawPyramid(); //function prototype for drawing a pyramid
void Print(const char* format, ...);
void ErrCheck(char* where); //function prototype for sanity checking GL errors

#endif
