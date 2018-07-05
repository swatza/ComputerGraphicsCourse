#ifndef FENCE_H
#define FENCE_H

//prototypes
void createFence(int x_posts, int y_posts, double max_x, double min_x, double max_y, double min_y, unsigned int postT1, unsigned int postT2, unsigned int beamT1, unsigned int beamT2);
void drawBeam(unsigned int beamside, unsigned int beamtop);
void drawPost(unsigned int postSide, unsigned int postTop);

#endif