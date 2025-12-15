/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

 /************************************
  * ANGLE : NORMALIZE
  * Normalize radians to [0, 2π)
  ************************************/
double Angle::normalize(double radians) const
{
   // Use fmod to wrap within [0, 2π)
   double TWO_PI = 2.0 * M_PI;
   radians = fmod(radians, TWO_PI);
   if (radians < 0.0)
      radians += TWO_PI;
   return radians;
}



