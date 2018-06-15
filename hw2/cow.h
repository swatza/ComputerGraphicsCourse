#ifndef COW_H
#define COW_H
//Structs
typedef struct cow_leg_skeleton cow_leg_skeleton;
typedef struct cow_skeleton cow_skeleton;
typedef struct cow_object cow_object;
typedef struct cow_frame cow_frame;

//Prototypes
void drawCowTest(int angle1, int angle2);
void drawCowLeg(struct cow_leg_skeleton leg);
void drawCowHead();
void drawCowTorso();
void drawHorns();
void drawEars();
void calculateCowSkeleton(struct cow_frame frame_angles, struct cow_skeleton thisCow);
void calculateCowLegSkeleton(double upper_leg_angle, double lower_leg_angle, struct cow_leg_skeleton *leg);



#endif