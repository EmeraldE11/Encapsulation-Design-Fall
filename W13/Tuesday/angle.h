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
#include <iostream>  // for cout, istream, ostream
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
    virtual void display(ostream& out) const
    {
        out.setf(ios::fixed);     // "fixed" means don't use scientific notation
        out.setf(ios::showpoint); // "showpoint" means always show the decimal point
        out.precision(1);         // Set the precision to 1 decimal place of accuracy.

        out << getDegrees(); // display degrees
    }

    // Assignment operator
    Angle& operator=(const Angle& rhs)
    {
        if (this != &rhs)
        {
            radians = rhs.radians;
        }
        return *this;
    }

    // Prefix increment operator
    Angle& operator++()
    {
        radians = normalize(radians + (M_PI / 180.0)); // add 1 degree
        return *this;
    }

    // Postfix increment operator
    virtual Angle operator++(int)
    {
        Angle temp(*this);
        radians = normalize(radians + (M_PI / 180.0)); // add 1 degree
        return temp;
    }

    // Prefix decrement operator
    Angle& operator--()
    {
        radians = normalize(radians - (M_PI / 180.0)); // subtract 1 degree
        return *this;
    }

    // Postfix decrement operator
    virtual Angle operator--(int)
    {
        Angle temp(*this);
        radians = normalize(radians - (M_PI / 180.0)); // subtract 1 degree
        return temp;
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

/************************************
 * NEGATIVE OPERATOR
 * Returns a new Angle that is 180° from the original
 ************************************/
inline Angle operator-(const Angle& rhs)
{
    Angle result;
    result.setRadians(rhs.getRadians() + M_PI);
    return result;
}

/************************************
 * EQUALS OPERATOR
 * Compares two angles for equality
 ************************************/
inline bool operator==(const Angle& lhs, const Angle& rhs)
{
    return lhs.getRadians() == rhs.getRadians();
}

/************************************
 * NOT-EQUALS OPERATOR
 * Compares two angles for inequality
 ************************************/
inline bool operator!=(const Angle& lhs, const Angle& rhs)
{
    return !(lhs == rhs);
}

/************************************
 * INSERTION OPERATOR
 * Displays the angle in degrees
 ************************************/
inline ostream& operator<<(ostream& out, const Angle& rhs)
{
    rhs.display(out);
    return out;
}

/************************************
 * EXTRACTION OPERATOR
 * Reads degrees from input and sets the angle
 ************************************/
inline istream& operator>>(istream& in, Angle& rhs)
{
    double degrees;
    in >> degrees;
    if (!in.fail())
    {
        rhs.setDegrees(degrees);
    }
    return in;
}

class AngleRadians : public Angle {
public:
    // Default constructor
    AngleRadians() : Angle() {}
    AngleRadians(const Angle& rhs) : Angle(rhs) {}

    void display(ostream& out) const
    {
        out.setf(ios::fixed);     // "fixed" means don't use scientific notation
        out.setf(ios::showpoint); // "showpoint" means always show the decimal point
        out.precision(1);         // Set the precision to 1 decimal place of accuracy.

        out << getRadians(); // display degrees
    }

    Angle operator++(int)
    {
        AngleRadians temp(*this);
        setRadians(getRadians() + (M_PI / 8));
        return temp;
    }

    Angle operator--(int)
    {
        AngleRadians temp(*this);
        setRadians(getRadians() - (M_PI / 8));
        return temp;
    }

};