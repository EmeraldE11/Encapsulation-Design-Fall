/*************************************************************
 * 1. Name:
 *      Spencer Palmer, Noah McCarthy
 * 2. Assignment Name:
 *      Practice 03: Angle Class
 * 3. Assignment Description:
 *      A class to represent an angle
 * 4. What was the hardest part? Be as specific as possible.
 *      Spencer - The hardest part was learning how to connect portions of my code to the rest of the project
 *		Noah - Figuring out whether errors were due to my mistakes or components I hadn't grabbed from my classmates yet.
 * 5. How long did it take for you to complete the assignment?
 *      Spencer - Total time spent: 1.5 hours
 *		Noah - Total time spent: 2.5 hours
 **************************************************************/

#pragma once

#define _USE_MATH_DEFINES
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
   double radianAngle;
private:
	double degrees;

	double normalize(double r)
	{
	    // Use fmod to wrap r within [0, TWO_PI)
	    r = fmod(r, TWO_PI);
	    if (r < 0)
	        r += TWO_PI;
	    return r;
	} 

	double convertToDegrees(double r)
    {
        return r * 180 /  M_PI;
    }

	double convertToRadians(double d)
	{
	    // Convert degrees to radians
	    double radians = d * (TWO_PI / 360.0);
	    // Normalize the result to [0, 2π)
	    return normalize(radians);
	}
	
public:
	// returns the angle in degrees
	double getDegrees()
	{
		return convertToDegrees(radianAngle); 
	}

	//returns the angle in radians
	double getRadians() const
	{
		return radianAngle;
	}

	//Takes a degrees as a parameter and updates the attribute with the passed parameter. 
	void setDegrees(double degrees)
	{
		double result = degrees;

		if (degrees < 0 || degrees > 360)
		{
			double r = convertToRadians(degrees);
			r = normalize(r);
			
			result = convertToDegrees(r);
		}

		radianAngle = convertToDegrees(result);
	}

	void setRadians(double radians)
	{
		double result = radians;

		if (radians < 0 || radians > TWO_PI)
		{
			result = normalize(radians);
		}

		radianAngle = result;
	}

	void display(ostream& out) const
        {
            cout.setf(ios::fixed);     // "fixed" means don't use scientific notation
            cout.setf(ios::showpoint); // "showpoint" means always show the decimal point
            cout.precision(1);         // Set the precision to 1 decimal place of accuracy.

            out << degrees << endl;
        }
};



