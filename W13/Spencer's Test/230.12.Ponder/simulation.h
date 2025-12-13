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

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired.
  *********************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight);
   
   void reset();

   // draw everything
   void draw(ogstream& gout) const;

private:
   Ground ground;
   Howitzer howitzer;
   Position posUpperRight;
   Projectile projectile;
};
