#ifndef KEYBOARD_H
#define KEYBOARD_H

#define GL_GLEXT_PROTOTYPES

//Global variables used in this file 
extern int x_rotation_angle;
extern int z_rotation_angle;
extern int view_mode;
extern double camera_x;
extern double camera_y;
extern double camera_z;
extern double camera_roll;
extern double camera_pitch;
extern double camera_yaw;

//Prototypes
void special(int key, int x, int y); //prototype for dealing with GLUT special keys 
void key(unsigned char ch, int x, int y); //prototype for dealing with GLUT regular keys

#endif
