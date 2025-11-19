/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

/************************************
 * ANGLE : NORMALIZE
 ************************************/
double Angle::normalize(double radians) const
{
   const double twoPi = 2.0 * M_PI;

   // If radians are greater than or equal to 2pi subtract 2pi
   while (radians >= twoPi)
       radians -= twoPi;

   // If radians are less than 0 add 2pi
   while (radians < 0.0)
       radians += twoPi;

    return radians;
}



