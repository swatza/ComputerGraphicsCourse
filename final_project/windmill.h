#ifndef WINDMILL_H
#define WINDMILL_H

//Includes
#include "util.h"
#include "primitives.h"
#include "helper.h"


//Global Variables

//Prototypes
void drawWaterContainer(unsigned int bot_text, unsigned int side_text, unsigned int inside_text);
void drawWater(unsigned int texture);
void drawWindmill(unsigned int support_text_1, unsigned int support_text_2, unsigned int tube_text, unsigned int platform_text, unsigned int metal_text1, unsigned int metal_text2);
void drawFanStructure(unsigned int text1, unsigned int text2, unsigned int text3);
void drawFanTailCone(unsigned int texture);
void drawFanNoseCone(unsigned int texture);
void drawFanRudder(unsigned int texture);
void drawFan(unsigned int texture);
void drawFanBeam();
void drawFanBlade(unsigned int texture);
void drawSwivelTube(unsigned int text);
void drawTopPlatform(unsigned int platform_text, unsigned int side_text);
void drawCrossBeamSupport(unsigned int text);
void drawDiagonalSupports();
void drawDiagonalBeam();
void drawMainWMSupport(unsigned int text1, unsigned text2);
void drawHayBale(unsigned int face, unsigned int edge);


#endif