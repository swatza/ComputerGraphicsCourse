#ifndef RENDERING_H
#define RENDERING_H

//#define GL_GLEXT_PROTOTYPES
extern int number_of_points;

//Functions
void display(); //function prorotype for rendering
void Vertex(double th, double ph);
void drawOval(double cx, double cy, double cz, double r);
void printAngles();
void drawPyramid(); //function prototype for drawing a pyramid
void Print(const char* format, ...);
void ErrCheck(char* where); //function prototype for sanity checking GL errors


#endif
