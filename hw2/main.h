#ifndef MAIN_H
#define MAIN_H

extern int fov;       //  Field of view (for perspective)
extern double asp;     //  Aspect ratio
extern double dim;   //  Size of world
extern int mode;       //  Projection mode

//Prototypes
void reshape(int width,int height);
static void Projection();

#endif