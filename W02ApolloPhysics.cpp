
/*************************************************************
 * 1. Name:
 *      -Roberto Sanchez-
 *      -Noah McCarthy-
 * 2. Assignment Name:
 *      Practice 02: Physics simulator
 * 3. Assignment Description:
 *      Compute how the Apollo lander will move across the screen
 * 4. What was the hardest part? Be as specific as possible.
 *      -Roberto: The hardest part for my was to formulate some of the calculations such as: updating position
          before updating velocity, or some trigonometry functions. After some correction with my syntax
          and interpretatio for the equations in C++ I figure it out.-

         - Noah: The toughest part for me was going through all the syntax, as I'm not familiar with this language.-

 * 5. How long did it take for you to complete the assignment?
 *      -Roberto: total time in hours: 3 hours.-
 *      -Noah: 2 hours.-
 *
 * 6. Demo Output:
 *      What is your horizontal velocity (m/s)? 0
What is your vertical velocity (m/s)? -10.3
What is your altitude (m)? 58.2
What is your position (m)? 83
What is the angle of the LM where 0 is up (degrees)? -45
What is the time interval (s)? 1.5
        New position:   (80.63, 43.29)m
        New velocity:   (-3.16, -9.58)m/s
        Total velocity:  10.09m/s

        New position:   (73.52, 29.47)m
        New velocity:   (-6.32, -8.85)m/s
        Total velocity:  10.88m/s

        New position:   (61.67, 16.73)m
        New velocity:   (-9.48, -8.13)m/s
        Total velocity:  12.49m/s

        New position:   (45.08, 5.07)m
        New velocity:   (-12.64, -7.41)m/s
        Total velocity:  14.65m/s

        New position:   (23.74, -5.50)m
        New velocity:   (-15.80, -6.69)m/s
        Total velocity:  17.16m/s


C:\Users\rober\source\repos\Apollo11Functions\x64\Debug\Apollo11Functions.exe (process 7476) exited with code 0 (0x0).
To automatically close the console when debugging stops, enable Tools->Options->Debugging->Automatically close the console when debugging stops.
 **************************************************************/

#include <iostream>  // for CIN and COUT
using namespace std;

#define WEIGHT   15103.000   // Weight in KG
#define GRAVITY     -1.625   // Vertical acceleration due to gravity, in m/s^2
#define THRUST   45000.000   // Thrust of main engine, in Newtons (kg m/s^2)
#define PI          3.14159 // Value of pi

/***************************************************
 * COMPUTE DISTANCE
 * Apply inertia to compute a new position using the distance equation.
 * The equation is:
 *     s = s + v t + 1/2 a t^2
 * INPUT
 *     s : original position, in meters
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     s : new position, in meters
 **************************************************/
double computeDistance(double s, double v, double a, double t)
{
    return s + v * t + 0.5 * a * pow(t, 2);
}

/**************************************************
 * COMPUTE ACCELERATION
 * Find the acceleration given a thrust and mass.
 * This will be done using Newton's second law of motion:
 *     f = m * a
 * INPUT
 *     f : force, in Newtons (kg * m / s^2)
 *     m : mass, in kilograms
 * OUTPUT
 *     a : acceleration, in meters/second^2
 ***************************************************/
double computeAcceleration(double f, double m)
{
    return f / m;
}

/***********************************************
 * COMPUTE VELOCITY
 * Starting with a given velocity, find the new
 * velocity once acceleration is applied. This is
 * called the Kinematics equation. The
 * equation is:
 *     v = v + a t
 * INPUT
 *     v : velocity, in meters/second
 *     a : acceleration, in meters/second^2
 *     t : time, in seconds
 * OUTPUT
 *     v : new velocity, in meters/second
 ***********************************************/
double computeVelocity(double v, double a, double t)
{
    return v + a * t;
}


/***********************************************
 * COMPUTE VERTICAL COMPONENT
 * Find the vertical component of a velocity or acceleration.
 * The equation is:
 *     cos(a) = y / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     y : the vertical component of the total
 ***********************************************/
double computeVerticalComponent(double a, double total)
{
    return total * cos(a);
}


/***********************************************
 * COMPUTE HORIZONTAL COMPONENT
 * Find the horizontal component of a velocity or acceleration.
 * The equation is:
 *     sin(a) = x / total
 * This can be expressed graphically:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    |a/
 *    |/
 * INPUT
 *     a : angle, in radians
 *     total : total velocity or acceleration
 * OUTPUT
 *     x : the vertical component of the total
 ***********************************************/
double computeHorizontalComponent(double a, double total)
{
    return total * sin(a);
}

/************************************************
 * COMPUTE TOTAL COMPONENT
 * Given the horizontal and vertical components of
 * something (velocity or acceleration), determine
 * the total component. To do this, use the Pythagorean Theorem:
 *    x^2 + y^2 = t^2
 * where:
 *      x
 *    +-----
 *    |   /
 *  y |  / total
 *    | /
 *    |/
 * INPUT
 *    x : horizontal component
 *    y : vertical component
 * OUTPUT
 *    total : total component
 ***********************************************/
double computeTotalComponent(double x, double y)
{
    return sqrt(x * x + y * y);
}


/*************************************************
 * RADIANS FROM DEGEES
 * Convert degrees to radians:
 *     radians / 2pi = degrees / 360
 * INPUT
 *     d : degrees from 0 to 360
 * OUTPUT
 *     r : radians from 0 to 2pi
 **************************************************/
double radiansFromDegrees(double d)
{
    return 2 * PI * (d / 360);
}

/**************************************************
 * PROMPT
 * A generic function to prompt the user for a double
 * INPUT
 *      message : the message to display to the user
 * OUTPUT
 *      response : the user's response
 ***************************************************/
double prompt(string prompt)
{
    double input;
    cout << prompt;
    cin >> input;
    return input;
}

/****************************************************************
* MAIN
* Prompt for input, compute new position, and display output
****************************************************************/
int main()
{
    // Prompt for input and variables to be computed
    double dx = prompt("What is your horizontal velocity (m/s)? ");
    double dy = prompt("What is your vertical velocity (m/s)? ");
    double y = prompt("What is your altitude (m)? ");
    // double x = prompt("What is your position (m)? ");
    double aDegrees = prompt("What is the angle of the LM where 0 is up (degrees)? ");
    // double t = prompt("What is the time interval (s)? ");
    double t = 1;
    double aRadians;            // Angle in radians
    double accelerationThrust;  // Acceleration due to thrust 
    double ddxThrust;           // Horizontal acceleration due to thrust
    double ddyThrust;           // Vertical acceleration due to thrust
    double ddx;                 // Total horizontal acceleration
    double ddy;                 // Total vertical acceleration
    double v;                   // Total velocity

    // Convert angle to radians
    aRadians = radiansFromDegrees(aDegrees);

    // Reformat for loop results - second, position (xy), speed (dx dy), angle

    // Go through the simulator five times
    for (int i = 0; i < 5; i++)
    {
        accelerationThrust = computeAcceleration(THRUST, WEIGHT);

        // calculate horizontal and vertical components of the thrust acceleration
        ddxThrust = computeHorizontalComponent(aRadians, accelerationThrust);
        ddyThrust = computeVerticalComponent(aRadians, accelerationThrust);

        //calcualte total acceleration (thrust + gravity)
        ddx = ddxThrust;
        ddy = ddyThrust + GRAVITY;

        //Update position before updating velocity
        double newX = computeDistance(x, dx, ddx, t);
        double newY = computeDistance(y, dy, ddy, t);

        // Update velocity
        dx = computeVelocity(dx, ddx, t);
        dy = computeVelocity(dy, ddy, t);

        //Update position
        x = newX;
        y = newY;

        //calculate total velocity
        v = computeTotalComponent(dx, dy);

        // Output
        cout.setf(ios::fixed | ios::showpoint);
        cout.precision(2);
        cout << "\tNew position:   (" << x << ", " << y << ")m\n";
        cout << "\tNew velocity:   (" << dx << ", " << dy << ")m/s\n";
        cout << "\tTotal velocity:  " << v << "m/s\n\n";
    }

    // Prompt a second angle
    aDegrees = prompt("What is the new angle of the LM where 0 is up (degrees)? ");
    cout << "For the next 5 seconds with the main engine on, the position of the lander is : ";

    // Add another for loop (copy the previous)... implement new angle for next 5 results

    return 0;
}