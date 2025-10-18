/***********************************************************************
 * Source File:
 *    Star : A single star that twinkles
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A star that twinkles
 ************************************************************************/

#include "star.h"

/***************************************************************
 * RESET
 * Reset the star to a random position within the given bounds
 ***************************************************************/


void Star::reset(double width, double height)
{
   // Generate random position within the given bounds
   pos.setX(random(0.0, width));
   pos.setY(random(0.0, height));
   
   // Reset phase to a random point for variety in twinkling
   phase = random(0, 255);
}

/***************************************************************
 * DRAW
 * Draw the star on the screen and increment phase for twinkling
 ***************************************************************/
void Star::draw(ogstream & gout) const
{
   // Increment the star phases
   const_cast<Star*>(this)->phase++;
 
   // Draw the star at its current position with current phase
   gout.drawStar(pos, phase);
   
}
