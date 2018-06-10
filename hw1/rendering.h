#ifndef RENDERING_H
#define RENDERING_H

extern double lorenz_parameter_s;
extern double lorenz_parameter_b;
extern double lorenz_parameter_r;
extern int variable_selector;
extern int scale; 

//Functions
void display(); //function prorotype for rendering
void draw3DLine(double** values, int size);
void drawAxis();
void printAngles();
void drawPyramid(); //function prototype for drawing a pyramid
void Print(const char* format, ...);
void ErrCheck(char* where); //function prototype for sanity checking GL errors

#endif
