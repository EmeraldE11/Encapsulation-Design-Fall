/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/ 

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()
#include <cassert>

/*********************************************
 * VELOCITY : ADD
 *  v = v_0 + a t
 *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
   dx += acceleration.getDDX() * time;
   dy += acceleration.getDDY() * time;
}
void Velocity::add(const Velocity& v)
{
   dx += v.getDX();
   dy += v.getDY();
}

/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *********************************************/
double Velocity::getSpeed() const
{
   return sqrt(dx * dy + dy * dx);
}

/*********************************************
 * VELOCITY : SET
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    /speed
 *     | a /
 *     |  /
 *     | /
 * dy = speed cos a
 * dx = speed sin a
 *********************************************/
void Velocity::set(const Angle & angle, double magnitude)
{
   dx = magnitude * sin(angle.getRadians());
   dy = magnitude * cos(angle.getRadians());
}


/************************************************
 * Velocity :: GET ANGLE
 * Determine the direction things are going
 * where 0 is up. This returns angle (clockwise) in radians
 *        dx
 *     +-------/
 *     |      /
 *  dy |     /
 *     |    /
 *     | a /
 *     |  /
 *     | /
 ************************************************/
Angle Velocity::getAngle() const
{
   Angle a;
   a.setDxDy(dx, dy);
   return a;
}
Angle VelocityDummy::getAngle() const
{
   assert(false); 
   return Angle();
}

void Velocity::reverse()
{
   dx = -dx;
   dy = -dy;
}
