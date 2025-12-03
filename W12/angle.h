/*************************************************************
 * 1. Name:
 *      Noah McCarthy, Spencer Palmer, Roberto Sanchez Molina
 * 2. Module
 *      ANGLE
 * 3. Assignment Description:
 *      A class to represent an angle
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

public:
    // Default constructor
    Angle() : radians(0.0) {}
    Angle(const Angle& rhs) : radians(rhs.radians) {}
    Angle(double degrees) : radians(convertToRadians(degrees)) {}

    // Getters
    // returns the angle in degrees
    double getDegrees() const
    {
        return convertToDegrees(radians);
    }

    //returns the angle in radians
    double getRadians() const
    {
        return radians;
    }

    // Setters
    //Takes a degrees as a parameter and updates the attribute with the passed parameter.
    void setDegrees(double degrees)
    {
        radians = convertToRadians(degrees);
    }

    // Takes the radians and passes it to the normalizer and sets the radians
    void setRadians(double r)
    {
        radians = normalize(r);
    }

    // Display
    void display(ostream& out) const
    {
        out.setf(ios::fixed);     // "fixed" means don't use scientific notation
        out.setf(ios::showpoint); // "showpoint" means always show the decimal point
        out.precision(1);         // Set the precision to 1 decimal place of accuracy.

        out << getDegrees() << "degrees"; // display degrees
    }

private:
    // Convert functions
    double convertToDegrees(double r) const
    {
        r = normalize(r);
        return r * 180 / M_PI; // convert to degrees
    }

    double convertToRadians(double d) const
    {
        // Normalize the result to [0, 2?)
        return normalize(d * (M_PI / 180));
    }

    // Normalize
    double normalize(double r) const
    {
        // If radians are greater than 2? subtract 2?
        while (r > 2 * M_PI)
            r -= 2 * M_PI;

        // If radians are less than 0 add 2?
        while (r < 0)
            r += 2 * M_PI;

        return  r;
    }

    double radians;
};
