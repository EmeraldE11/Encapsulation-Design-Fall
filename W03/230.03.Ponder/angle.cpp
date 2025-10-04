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
    // If radians are greater than 2π subtract 2π
    while (radians > 2 * M_PI)
        radians -= 2 * M_PI;
    
    // If radians are less than 0 add 2π
    while (radians < 0)
        radians += 2 * M_PI;
    
    return radians;
}



