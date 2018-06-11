#ifndef KEYBOARD_H
#define KEYBOARD_H

#define GL_GLEXT_PROTOTYPES

//Global variables used in this file 
extern int variable_selector;
extern double scale;
extern double zoom_scale;
extern double lorenz_parameter_s;
extern double lorenz_parameter_b;
extern double lorenz_parameter_r;
extern double z_rotation_angle;
extern double x_rotation_angle;


void special(int key, int x, int y); //prototype for dealing with GLUT special keys 

#endif
