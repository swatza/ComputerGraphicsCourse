#ifndef KEYBOARD_H
#define KEYBOARD_H

#define GL_GLEXT_PROTOTYPES
#include <stdlib.h>

//Global variables used in this file 

extern int obj_viewer;
extern int flash_light_toggle;
extern int dance_party_toggle;

//Camera Movement Variables
extern double camera_x;
extern double camera_y; 
extern double camera_z; //default height of the camera
extern double camera_roll;
extern double camera_pitch;
extern double camera_yaw;

//Camera Rotation Variables
extern int x_rotation_angle;
extern int y_rotation_angle;
extern int z_rotation_angle;

//Animation Tool Variables
extern int left_knee_angle_x; //q
extern int left_knee_angle_y; //a
extern int left_knee_angle_z; //z

extern int left_ankle_angle_x; //w
extern int left_ankle_angle_y; //s
extern int left_ankle_angle_z; //x

extern int right_knee_angle_x; //e
extern int right_knee_angle_y; //d
extern int right_knee_angle_z; //c

extern int right_ankle_angle_x; //r
extern int right_ankle_angle_y; //f
extern int right_ankle_angle_z; //v

extern int left_hip_angle; //unsure if needed
extern int right_hip_angle; //unsure if needed

extern int cow_body_angle; //s / S
extern int cow_head_angle; //w / W

extern int left_elbow_angle_x; //q / Q
extern int left_elbow_angle_y;
extern int left_elbow_angle_z;

extern int right_elbow_angle_x; // e / E
extern int right_elbow_angle_y;
extern int right_elbow_angle_z;

extern int left_wrist_angle_x; // r / R
extern int left_wrist_angle_y;
extern int left_wrist_angle_z;

extern int right_wrist_angle_x; // t / T
extern int right_wrist_angle_y;
extern int right_wrist_angle_z;

//Prototypes
void Projection();
void special(int key, int x, int y); //prototype for dealing with GLUT special keys 
void key(unsigned char ch, int x, int y); //prototype for dealing with GLUT regular keys
void mouse_movement(int x, int y);
void saveAnimation();
void movementTool(unsigned char ch);
void animationKeyTool(unsigned char ch);


#endif
