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
    double hangTime = 0.0;          // time projectile is in the air

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
        cout << "Distance: " << distance
            << "m   Altitude: " << altitude
            << "m   Hang Time: " << hangTime << "s" << endl;
    }
};

// Gravity lookup table: altitude (m) -> gravity (m/s^2)
const int GRAVITY_TABLE_SIZE = 8;
const double altitudeTable[GRAVITY_TABLE_SIZE] = {
    0.0, 1000.0, 2000.0, 3000.0, 4000.0, 5000.0, 6000.0, 7000.0
};
const double gravityTable[GRAVITY_TABLE_SIZE] = {
    -9.807, -9.804, -9.801, -9.797, -9.794, -9.791, -9.788, -9.785
};

// Linear interpolation for gravity based on altitude
double getGravity(double altitude) {
    // Clamp altitude to table range
    if (altitude <= altitudeTable[0]) {
        return gravityTable[0];
    }
    if (altitude >= altitudeTable[GRAVITY_TABLE_SIZE - 1]) {
        return gravityTable[GRAVITY_TABLE_SIZE - 1];
    }
    
    // Find the two altitudes to interpolate between
    int i = 0;
    while (i < GRAVITY_TABLE_SIZE - 1 && altitude >= altitudeTable[i + 1]) {
        i++;
    }
    
    // Linear interpolation: my = ay + (zy - ay) * t
    double t = (altitude - altitudeTable[i]) / (altitudeTable[i + 1] - altitudeTable[i]);
    return gravityTable[i] + (gravityTable[i + 1] - gravityTable[i]) * t;
}

double airDensity(double altitude, double projectileMass)
{
   double m = altitude;
   double kg = projectileMass;
   
   return kg / (m * m);
}

// f = dragForce, p = airDenstiy, v = velocity, a = area.
double dragCoefficient(double f, double p, double v, double a)
{
   return 2 * f / p * (v * v) * a;
}

// x = Projectile's x position, y = Projectile's y position, t = time
void hitTheGround(double prevX, double prevY, double prevT, double x, double y, double t)
{
    // After updating, check if we hit the ground
    if (y <= 0.0)
    {
       // Linear interpolation to find where y = 0 exactly
       double f = prevY / (prevY - y);  // fraction between prev and current
       double xImpact = prevX + f * (x - prevX);
       double tImpact = prevT + f * (t - prevT);

       cout << "Distance: " << xImpact << "m" << "   Hang Time: " << tImpact << "s\n";
    }
}

int main() {
    Howitzer pew;

    pew.getUserInput();

    double initialSpeed = 827.0;
    pew.splitVelocity(initialSpeed);

    // Constants for simulation
    double deltaTime = 0.01;       // 0.01 second timestep for accuracy
    
    // Drag constants
    const double dragCoefficient = 0.3;
    const double airDensity = 0.6;
    const double projectileDiameter = 0.15489;  // 154.89 mm in meters
    const double projectileMass = 46.7;         // kg (typical artillery shell mass)
    const double area = PI * (projectileDiameter / 2.0) * (projectileDiameter / 2.0);

    // Main simulation loop - continue until ground impact
    while (pew.altitude >= 0.0) {
        // Calculate current velocity magnitude
        pew.velocity = sqrt(pew.dx * pew.dx + pew.dy * pew.dy);
        
        // Calculate drag force: d = 0.5 * c * p * v * v * a
        double dragForce = 0.5 * dragCoefficient * airDensity * pew.velocity * pew.velocity * area;
        
        // Convert drag force to acceleration: f = m * a, so a = f / m
        double dragAcceleration = dragForce / projectileMass;
        
        // Get direction of travel using atan2
        double travelAngle = atan2(pew.dx, pew.dy);
        
        // Convert drag acceleration to horizontal/vertical components
        // Drag opposes velocity direction
        double ddx = -dragAcceleration * sin(travelAngle);
        double ddy = -dragAcceleration * cos(travelAngle);
        
        // Get gravity based on current altitude
        double gravity = getGravity(pew.altitude);
        
        // Total accelerations
        double totalAccelerationX = ddx;
        double totalAccelerationY = gravity + ddy;
        
        // Update position using distance formula with total accelerations
        pew.distance += pew.dx * deltaTime + 0.5 * totalAccelerationX * deltaTime * deltaTime;
        pew.altitude += pew.dy * deltaTime + 0.5 * totalAccelerationY * deltaTime * deltaTime;
        
        // Update velocity using kinematics equation with total accelerations
        pew.dx += totalAccelerationX * deltaTime;
        pew.dy += totalAccelerationY * deltaTime;
        
        pew.time += deltaTime;
        pew.hangTime = pew.time;
    }
    
    // Print final status
    pew.printStatus();

    return 0;
}

/* 
Now introduce gravity at a constant - 9.8m / s2.This will require you to update the velocity 
based on the acceleration due to gravity. First, update the position using the distance formula.
Next, after the position is updated, update the velocity. Use the distance formula and the kinematics 
equation to compute the new position(with(x, y) instead of s) and velocity(with(dx, dy) instead of v).
Notice how our horizontal distance is unaffected, but our altitude has decreased significantly.
*/
