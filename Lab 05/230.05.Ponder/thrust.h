/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface

class TestLander;
class TestThrust;
class TestImplementation;
class TestSimpleImplementation;
class TestThrustOnly;

 /*****************************************************
  * THRUST
  * Represents activation of thrusters
  *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;
   friend TestImplementation;
   friend TestSimpleImplementation;
   friend TestThrustOnly;
   
public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per second
   double rotation() const
   {
      if (clockwise && !counterClockwise)
         return 0.1; // Rotate right
      else if (!clockwise && counterClockwise)
         return -0.1; // Rotate left
      else
         return 0.0; // No rotation
   }

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const
   {
      return mainEngine ? 45000.0 / 15103.0 : 0.0;
   }

   // reflect what is firing
   bool isMain()    const { return mainEngine; }
   bool isClock()   const { return clockwise; }
   bool isCounter() const { return counterClockwise; }

   // set the thrusters
   void set(const Interface * pUI)
   {
      mainEngine = pUI->isDown();
      clockwise = pUI->isLeft();
      counterClockwise = pUI->isRight();
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
