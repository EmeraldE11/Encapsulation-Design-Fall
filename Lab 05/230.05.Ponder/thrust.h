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
   double rotation() const;

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const;

   // reflect what is firing
   bool isMain()    const;
   bool isClock()   const;
   bool isCounter() const;

   // set the thrusters
   void set(const Interface * pUI);

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
