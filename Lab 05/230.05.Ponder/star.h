/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
public:
   // Constructor
   Star() : pos(Position()), phase(0) {}
   
   // Reset the star to a random position
   void reset(double width, double height);
   
   // Draw the star on the screen
   void draw(ogstream & gout) const;

private:
   Position pos;        // Position of the star
   unsigned char phase; // Phase for twinkling effect
};
