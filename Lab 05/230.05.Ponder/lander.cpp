/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"
#include <cmath>     // for sin, cos
#include <cassert>   // for assert


 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   status = PLAYING;
   pos = Position(posUpperRight.getX() / 2.0, posUpperRight.getY() - 20.0);
   velocity = Velocity();
   angle = Angle();
   fuel = 500.0;


   status = PLAYING;
   pos = Position(posUpperRight.getX() / 2.0, posUpperRight.getY() - 20.0);
   velocity = Velocity();
   angle = Angle();
   fuel = 500.0;

   angle.setRadians(0.0);               // straight up
   status = PLAYING;                    // make sure we are playing
   fuel = 5000.0;                        // start fuel
   velocity.setDX(random(-10.0, -4.0)); // random horizontal velocity
   velocity.setDY(random(-2.0, 2.0));   // random vertical velocity
   pos.setX(posUpperRight.getX() - 1.0);                     // 1 pixel from right edge
   pos.setY(random(posUpperRight.getY() * 0.75,               // between 75% and
             posUpperRight.getY() * 0.95));             // 95% of screen height

}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander::draw(const Thrust& thrust, ogstream& gout) const
{
    // Convert Angle object to radians for drawing
    double a = angle.getRadians();  // or angle.getRadians() depending on your Angle class

    // Draw the lander body
    gout.drawLander(pos, a);

    // Determine which flames to draw
    bool bottom = thrust.isMain();      // main engine (down arrow)
    bool left = thrust.isClock();     // clockwise rotation -> LEFT flame
    bool right = thrust.isCounter();   // counterclockwise rotation -> RIGHT flame

    // Draw flames if any thruster is on
    if (bottom || left || right)
        gout.drawLanderFlames(pos, a, bottom, left, right);
}



/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/

Acceleration Lander::input(const Thrust& thrust, double gravity)
{
    Acceleration accel;
   
    // start with gravity vertical accel
    accel.addDDY(gravity);
   
    if(fuel == 0.0)
       return accel;

    // get the engine thrust magnitude (m/s^2)
    double engine = thrust.mainEngineThrust();

    // apply main engine thrust in the direction of the current angle (if engine on and we have fuel)
    if (thrust.isMain())
    {
        // compute direction from angle's radians
        double a = angle.getRadians();

        // x component = cos(theta), y component = sin(theta)
        accel.addDDX(engine * -sin(a));
        accel.addDDY(engine * cos(a));
       
        // Burn fuel proportional to thrust
        fuel -= 10;
    }
   
    if (thrust.isClock())
    {
       angle.add(0.1);
       fuel -= 1;
    }

    if (thrust.isCounter())
    {
       angle.add(-0.1);
       fuel -= 1;
    }
   
    if (fuel < 0.0)
       fuel = 0.0;
   
    return accel;
}



/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   
   // update position
   pos.add(acceleration, velocity, time);
   
   // update velocity
   velocity.add(acceleration, time);

}

/***************************************************************
 * LAND
 * Straighten the lander and change the status to SAFE
 ***************************************************************/
void Lander::land()
{
    angle.setRadians(0.0);   // straighten up
    status = SAFE;           // landed safely
}

/***************************************************************
 * CRASH
 * Flip the lander upside down and change the status to DEAD
 ***************************************************************/
void Lander::crash()
{
    angle.setRadians(M_PI);  // upside down
    status = DEAD;           // destroyed
}



/***************************************************************
 * IS DEAD
 * Check if the lander is dead
 ***************************************************************/
bool Lander::isDead() const
{
   return status == DEAD;
}

/***************************************************************
 * IS LANDED
 * Check if the lander has landed safely
 ***************************************************************/
bool Lander::isLanded() const
{
   return status == SAFE;
}

/***************************************************************
 * IS FLYING
 * Check if the lander is currently flying
 ***************************************************************/
bool Lander::isFlying() const
{
   return status == PLAYING;
}

/***************************************************************
 * GET POSITION
 * Get the current position of the lander
 ***************************************************************/
Position Lander::getPosition() const
{
   return pos;
}

/***************************************************************
 * GET SPEED
 * Get the current speed of the lander
 ***************************************************************/
double Lander::getSpeed() const
{
   return velocity.getSpeed();
}

/***************************************************************
 * GET FUEL
 * Get the current fuel level
 ***************************************************************/
int Lander::getFuel() const
{
   return (int)fuel;
}

/***************************************************************
 * GET WIDTH
 * Get the width of the lander (20 meters)
 ***************************************************************/
int Lander::getWidth() const
{
   return 20;
}

/***************************************************************
 * GET MAX SPEED
 * Get the maximum safe landing speed (4 m/s)
 ***************************************************************/
double Lander::getMaxSpeed() const
{
   return 4.0;
}
