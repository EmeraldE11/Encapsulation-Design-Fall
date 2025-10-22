/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

/************************************
 * ANGLE
 ************************************/
class Angle
{
public:
    friend TestAcceleration;
    friend TestVelocity;
    friend TestAngle;
    friend TestLander;

    // Constructors
    Angle() : radians(0.0) {}
    Angle(const Angle& rhs) : radians(rhs.radians) {}
    Angle(double degrees) : radians(M_PI) {}

    // Getters
    double getDegrees() const
    {
        return radians * 180 / M_PI; // Converts radians into degrees
    }

    double getRadians() const
    {
        return radians; // Gets the value from the radians variable
    }

    // Setters
    void setDegrees(double degrees)
    {
        radians = normalize(degrees * (M_PI / 180)); // Set radians from given degrees
    }

    void setRadians(double rad)
    {
        radians = normalize(rad); // Set radians from give radian value
    }

    void setUp()
    {
        radians = 0.0; // set radians to 0
    }

    void setDown()
    {
        radians = M_PI; // set radians to reflect 180 degrees
    }

    void setRight()
    {
        radians = M_PI_2; // set radians to reflect 90 degrees
    }

    void setLeft()
    {
        radians = M_PI + M_PI_2; // set radians to reflect 270 degrees
    }

    void reverse()
    {
        radians = M_PI_2 + M_PI;
    }

    // Add to radians
    Angle& add(double delta)
    {
        radians += normalize(delta); // add give value to radians

        return *this;
    }

private:
    double normalize(double radians) const;

    double radians;   // 360 degrees equals 2 PI radians
};

