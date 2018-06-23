#ifndef MAIN_H
#define MAIN_H

extern int fov;       //  Field of view (for perspective)
extern double asp;     //  Aspect ratio
extern double dim;   //  Size of world
extern int mode;       //  Projection mode
extern double last_time_frame; // time since last new frame
extern int main_new_frame; //flag saying its time to render a new animation key frame
extern int zh;

//Prototypes
void reshape(int width,int height);
void idle();

#endif