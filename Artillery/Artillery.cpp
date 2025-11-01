/*
EQUATIONS TO USE FOR THE PROJECT

PROJECTILE EQUATIONS
Drag Force Equation: d = force in Newtons (N), c = drag coefficient, p = density of the fluid/gas, v = velocity of the projectile, a = surface area
d = 0.5 * c * p * v * v * a

Area of a circle: a = area of a circle (m^2), r = radius of a circle
a = PI * r * r

Newton's 2nd Law: f = force in Newtons (N), m = mass in kgs, a = acceleration (m/s^2)
f = m * a

GEOMETRY/PHYSICS
Degrees and Radians: r = angle in radians, d = angle in degrees
(r / (2 * PI)) = (d / 360)
r = d * (PI / 180)
d = r * (180 / PI)

Vertical speed component: dy = vertical speed component (m/s), s = overall speed (m/s), a = direction of travel where 0 is pointing up (radians)
dy = s * cos(a)

Horizontal speed component: dx = horizontal speed component (m/s), s = overall speed (m/s), a = direction of travel where 0 is pointing up (radians)
dx = s * sin(a)

Distance Formula: s = distance (meters), i = initial distance (meters), v = velocity (m/s), t = time (seconds), a = acceleration (m/s^2)
s = i + v * t + 0.5 * a * t * t

Kinematics Equation: v = velocity, i = initial velocity, a = acceleration, t = time
v = i + a * t

Angle from components: a = direction of travel where 0 points up (radians), dx = horizontal speed component (m/s), dy = vertical speed component (m/s)
a = atan2(dx, dy)

Pythagorean Theorem: dx and dy = horizontal/vertical speed components, s = overall speed
dx * dx + dy * dy = s * s
s = sqrt(dx * dx + dy * dy)

Linear Interpolation: ax, ay = coordinates of one point, zx, zy = coordinates of a second point, mx, my = coordinates of a point in the middle, t = fraction of space between frames
(my - ay)/(mx - ax) == (zy - ay)/(zx - ax)
mx = ax + (zx - ax) * t
my = ay + (zy - ay) * t

*/

#include <iostream>
#include <cmath>   // for sin, cos, etc.

using namespace std;

const double PI = 3.14159265358979323846;

class Howitzer {
public:
    // Member variables
    double angleDegrees = 0.0;
    double angleRadians = 0.0;
    double time = 0.0;              // simulation time
    double altitude = 0.0;          // vertical position (y)
    double distance = 0.0;          // horizontal position (x)
    double dx = 0.0;                // horizontal velocity
    double dy = 0.0;                // vertical velocity
    double velocity = 827.0;        // total velocity
    double acceleration = -9.8;

    // Constructor
    Howitzer() {}

    // Member methods
    void getUserInput() {
        cout << "What is the angle of the Howitzer where 0 is up? ";
        cin >> angleDegrees;
        angleRadians = angleDegrees * (PI / 180.0); // convert to radians
    }

    void splitVelocity(double speed) { // initializes velocity, and also splits speed into horizontal/vertical components
        velocity = speed;
        dy = speed * cos(angleRadians);
        dx = speed * sin(angleRadians);
    }

    void updatePosition(double time, double acceleration) {
        distance += dx * time; // distance formula, NO acceleration because x isn't affected by gravity. dx as velocity to find horizontal distance
        altitude += dy * time + 0.5 * acceleration * time * time; // distance formula, dy as velocity to find vertical distance
    }

    void updateVelocity(double speed, double acceleration, double time) {
        // kinematics equation for y component of velocity, x isn't affected by gravity.
        dy += acceleration * time;
    }

    void printStatus() {
        cout << "Time: " << time
            << "s, Distance: " << distance
            << "m, Altitude: " << altitude << "m" << endl;
    }
};

int main() {
    Howitzer pew;

    pew.getUserInput();

    double initialSpeed = 827.0;
    double oneAcceleration = -9.8;

    pew.splitVelocity(initialSpeed);

    double deltaTime = 1.0;       // Step 1 uses 1-second increments

    // Step 1: loop 20 iterations (inertia test)
    for (int i = 0; i < 20; ++i) {
        pew.updatePosition(deltaTime, oneAcceleration);
        pew.updateVelocity(pew.velocity, oneAcceleration, deltaTime);
        pew.time += deltaTime;
        pew.printStatus();
    }

    return 0;
}

/* 
Now introduce gravity at a constant - 9.8m / s2.This will require you to update the velocity 
based on the acceleration due to gravity. First, update the position using the distance formula.
Next, after the position is updated, update the velocity. Use the distance formula and the kinematics 
equation to compute the new position(with(x, y) instead of s) and velocity(with(dx, dy) instead of v).
Notice how our horizontal distance is unaffected, but our altitude has decreased significantly.
*/