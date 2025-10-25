/***********************************************************************
 * Header File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#pragma once

#include "position.h"  // for POINT
#include "velocity.h"  // for VELOCITY
#include "thrust.h"    // for THRUST
#include "uiDraw.h"    // for DRAW* and RANDOM
#include "angle.h"     // for ANGLE

enum Status { PLAYING, SAFE, DEAD };

class TestLander;

/****************************************************************
 * LANDER
 * The position and status of the lander
 ***************************************************************/
class Lander
{
   friend TestLander;
   
public:
  // to create a lander, we need to know something about the board
  Lander(const Position & posUpperRight) : status(PLAYING), fuel(500.0) 
  { 
     pos = Position(posUpperRight.getX() / 2.0, posUpperRight.getY() - 20.0);
     velocity = Velocity();
     angle = Angle();
  }

  // reset the lander and its position
  void reset(const Position& posUpperRight);

  // get the status of the lander
  bool     isDead()         const;
  bool     isLanded()       const;
  bool     isFlying()       const;
  Position getPosition()    const;
  double   getSpeed()       const;
  int      getFuel()        const;
  int      getWidth()       const;
  double   getMaxSpeed()    const;

  // draw the lander on the screen
  void draw(const Thrust & thrust, ogstream & gout) const; //draw the lander and turn on the flames as necessary.
 
  // handle input
  Acceleration input(const Thrust & thrust, double gravity); //convert thrust and gravity into an acceleration object

  // what happens when we coast?
  void coast(Acceleration & acceleration, double time); //move the lander

  // straighten the lander and put it on the ground, change the status to SAFE
  void land();

  // we are dead. Draw the lander upside downand change the status to DEAD
  void crash();
   
   Angle getAngle()
   {
      return angle;
   }

private:
   Status   status;      // are we dead or not?
   Position pos;         // the location of the lander
   Velocity velocity;    // the speed of the lander
   Angle    angle;       // the orientation of the lander
   double   fuel;        // amount of fuel remaining
};
