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
   void reset(double width, double height)
   {
      pos.setX(random(0.0, width));
      pos.setY(random(0.0, height));
      phase = random(0, 255); // Start twinkle out of phase
      framecount = random(0, 60); // create a desync
   }
   
   // Draw the star on the screen
   void draw(ogstream & gout)
   {
      framecount++;
      if (framecount >= 60)
      {
         phase++;
         framecount = 0;
      }
      gout.drawStar(pos, phase);
   }

private:
   Position pos;        // Position of the star
   unsigned char phase; // Phase for twinkling effect
   int framecount;      // Counts the number of frames to slow down twinkling stars
};
