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
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   pos.setX(-99.9);
   return Acceleration();
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   pos.setX(-99.9);
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
