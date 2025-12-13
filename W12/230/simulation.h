/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "ground.h"
#include "howitzer.h"
#include "projectile.h"

// Forward declaration
class Interface;

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight);

   // handle user input
   void input(const Interface* pUI);
   
   // advance the simulation
   void update(double time);
   
   // draw everything
   void draw(ogstream& gout) const;

private:
   Ground ground;
   Howitzer howitzer;
   Projectile projectile;
   Position posUpperRight;
   double simulationTime;
   
   // helper methods
   bool isProjectileInFlight() const;
   Position getProjectilePosition() const;
   bool checkGroundCollision() const;
   double getFlightTime() const;
};
