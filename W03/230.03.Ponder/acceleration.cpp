/***********************************************************************
 * Source File:
 *    ACCELERATION 
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <cmath>

 /*********************************************
  * ACCELERATION : Constructors
  *  Default - sets ddx and ddy to 0
  *  Parameterized - sets ddx and ddy to the passed parameters
  *********************************************/

Acceleration::Acceleration()
{
	ddx = 0.0;
	ddy = 0.0;
}

Acceleration::Acceleration(double x, double y)
{
	ddx = x;
	ddy = y;
}


/*********************************************
 * ACCELERATION : ADD DDX
 *  add value to ddx component
 *********************************************/
void Acceleration::addDDX(double deltaX)
{
	//change in the values of ddx
   ddx += deltaX;
}

/*********************************************
 * ACCELERATION : ADD DDY
 *  add value to ddy component
 *********************************************/
void Acceleration::addDDY(double deltaY)
{
	//change in the values of ddy
   ddy += deltaY;
}

/*********************************************
 * ACCELERATION : ADD
 *  a += a
 *********************************************/
void Acceleration::add(const Acceleration& acceleration)
{
   ddx += acceleration.ddx;
   ddy += acceleration.ddy;
}

/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle & angle, double magnitude)
{
	double radians = angle.getDegrees() * M_PI / 180.0; // cos and sin need doubles, this uses the angle to pull the radians we need.
	ddx = magnitude * std::cos(radians);
	ddy = magnitude * std::sin(radians);
}

/*********************************************
 * ACCELERATION : Getters
 *  pulls the value for ddx and ddy
 *********************************************/
double Acceleration::getDDX() const
{
	return ddx;
}

double Acceleration::getDDY() const
{
	return ddy;
}

/*********************************************
 * ACCELERATION : Setters
 *  updates the values of ddx and ddy
 *********************************************/
void Acceleration::setDDX(double x)
{
	ddx = x;
}

void Acceleration::setDDY(double y)
{
	ddy = y;
}