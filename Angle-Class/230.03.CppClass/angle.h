/*************************************************************
 * 1. Name:
 *      -your name-
 * 2. Assignment Name:
 *      Practice 03: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      -a paragraph or two about how the assignment went for you-
 * 5. How long did it take for you to complete the assignment?
 *      -total time in hours: reading the assignment, submitting, etc.
 **************************************************************/

#pragma once

#define TWO_PI 6.28318530718

#include <math.h>    // for floor()
#include <iostream>  // for cout
#include <cassert>   // for assert()
using namespace std;

class TestAngle;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
   friend TestAngle;
   // will the TestAngle class provide the angle attribute?
   // if not, the line would be:
   // double radianAngle;
private:
	
	void normalize(double r) {/*redefine r to the equivalent of 0-360 degrees, which is a range between 0 and 2pi. Doesn't return anything*/} 
	double convertToDegrees(double r) { return /*degrees*/;}
	double convertToRadians(double d) { return /*radians*/;}
	
public:
	// returns the angle in degrees
	double getDegrees() const { return convertToDegrees(radians); }

	//returns the angle in radians
	double getRadians() const { return radians; }

	//Takes a degrees as a parameter and updates the attribute with the passed parameter. 
	void setDegrees(double degrees) { radians = convertToDegrees(degrees); }

	void setRadians(double r) {}

	void display(/* iostream i, cout c ??? */) 
	{
		// cout.setf(ios::fixed);     // "fixed" means don't use scientific notation
		// cout.setf(ios::showpoint); // "showpoint" means always show the decimal point
		// cout.precision(1);         // Set the precision to 1 decimal place of accuracy.
	}
};


