/**********************************************************************
 * Source File:
 *    HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a howitzer (aka the gun)
 ************************************************************************/

#include "howitzer.h"
#include <math.h>

// Default constructor - initialize position to (0,0) and elevation to 45 degrees
Howitzer::Howitzer() : position(), muzzleVelocity(DEFAULT_MUZZLE_VELOCITY), elevation()
{
   // Initialize position to (0,0) using setters
   position.setMetersX(0.0);
   position.setMetersY(0.0);
   
   // Set elevation to 45 degrees (convert to radians: 45 * PI / 180)
   elevation.setRadians(45.0 * M_PI / 180.0);
}

