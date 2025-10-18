/***********************************************************************
 * Source File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#include "thrust.h"

/***************************************************************
 * ROTATION
 * Get rotation in radians per second
 ***************************************************************/
double Thrust::rotation() const
{
   // If both clockwise and counterclockwise are on, they cancel out
   if (clockwise && counterClockwise)
      return 0.0;
   
   // If only clockwise is on, return 0.1 radians per frame
   if (clockwise)
      return 0.1;
   
   // If only counterclockwise is on, return -0.1 radians per frame
   if (counterClockwise)
      return -0.1;
   
   // If neither is on, return 0
   return 0.0;
}

/***************************************************************
 * MAIN ENGINE THRUST
 * Get main engine thrust in m/s^2
 * Thrust = 45,000 N, Mass = 15,103 kg
 * Acceleration = Force / Mass = 45,000 / 15,103 = 2.97954048864 m/s^2
 ***************************************************************/
double Thrust::mainEngineThrust() const
{
   // If main engine is on, return the calculated acceleration
   if (mainEngine)
      return 45000.0 / 15103.0;  // 2.97954048864 m/s^2
   
   // If main engine is off, return 0
   return 0.0;
}

/***************************************************************
 * IS MAIN
 * Check if main engine is firing
 ***************************************************************/
bool Thrust::isMain() const
{
   return mainEngine;
}

/***************************************************************
 * IS CLOCK
 * Check if clockwise thruster is firing
 ***************************************************************/
bool Thrust::isClock() const
{
   return clockwise;
}

/***************************************************************
 * IS COUNTER
 * Check if counterclockwise thruster is firing
 ***************************************************************/
bool Thrust::isCounter() const
{
   return counterClockwise;
}

/***************************************************************
 * SET
 * Set the thrusters based on user input
 ***************************************************************/
void Thrust::set(const Interface * pUI)
{
   // Check if down arrow is pressed for main engine
   mainEngine = pUI->isDown();
   
   // Check if right arrow is pressed for clockwise rotation
   clockwise = pUI->isRight();
   
   // Check if left arrow is pressed for counterclockwise rotation
   counterClockwise = pUI->isLeft();
}
