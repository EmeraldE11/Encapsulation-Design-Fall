// Artillery.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

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
