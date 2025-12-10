/**********************************************************************
 * Source File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION
#include "uiDraw.h"

/**********************************************************************
 * SIMULATOR : CONSTRUCTOR
 * Initialize the simulator with ground and howitzer
 ************************************************************************/
Simulator::Simulator(const Position & posUpperRight) 
   : ground(posUpperRight), posUpperRight(posUpperRight)
{
   // Generate a position for the howitzer
   howitzer.generatePosition(posUpperRight);
   
   // Reset the ground (which will set the howitzer's Y position based on ground elevation)
   ground.reset(howitzer.getPositionRef());
}

/**********************************************************************
 * SIMULATOR : DRAW
 * Draw the ground and howitzer
 ************************************************************************/
void Simulator::draw(ogstream& gout) const
{
   // Draw the ground
   ground.draw(gout);
   
   // Draw the howitzer (flightTime is 0.0 since we're not firing yet)
   howitzer.draw(gout, 0.0);
}
