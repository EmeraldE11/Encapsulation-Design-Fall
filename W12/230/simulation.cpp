/**********************************************************************
 * Source File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#include "simulation.h"  // for SIMULATION
#include "uiDraw.h"
#include "uiInteract.h"

/**********************************************************************
 * SIMULATOR : CONSTRUCTOR
 * Initialize the simulator with ground and howitzer
 ************************************************************************/
Simulator::Simulator(const Position & posUpperRight) 
   : ground(posUpperRight), posUpperRight(posUpperRight), simulationTime(0.0)
{
   // Generate a position for the howitzer
   howitzer.generatePosition(posUpperRight);
   
   // Reset the ground (which will set the howitzer's Y position based on ground elevation)
   ground.reset(howitzer.getPositionRef());
}

/**********************************************************************
 * SIMULATOR : INPUT
 * Handle user input to control the howitzer
 ************************************************************************/
void Simulator::input(const Interface* pUI)
{
   // Only allow input if projectile is not in flight
   if (!isProjectileInFlight())
   {
      // Rotate howitzer left/right
      if (pUI->isLeft())
         howitzer.rotate(-0.05);  // rotate counter-clockwise
      if (pUI->isRight())
         howitzer.rotate(0.05);   // rotate clockwise
      
      // Raise/lower howitzer
      if (pUI->isUp())
         howitzer.raise(0.05);    // raise (point more up)
      if (pUI->isDown())
         howitzer.raise(-0.05);   // lower (point more down)
      
      // Fire the projectile
      if (pUI->isSpace())
      {
         Position pos = howitzer.getPosition();
         Angle angle = howitzer.getElevation();
         double velocity = howitzer.getMuzzleVelocity();
         projectile.fire(pos, simulationTime, angle, velocity);
      }
   }
}

/**********************************************************************
 * SIMULATOR : UPDATE
 * Advance the simulation by one frame
 ************************************************************************/
void Simulator::update(double time)
{
   simulationTime = time;
   
   // Advance the projectile if it's in flight
   if (isProjectileInFlight())
   {
      projectile.advance(simulationTime);
      
      // Check for ground collision
      if (checkGroundCollision())
      {
         // Projectile hit the ground - reset it
         projectile.reset();
      }
   }
}

/**********************************************************************
 * SIMULATOR : DRAW
 * Draw the ground, howitzer, and projectile
 ************************************************************************/
void Simulator::draw(ogstream& gout) const
{
   // Draw the ground
   ground.draw(gout);
   
   // Draw the howitzer with appropriate flight time
   double flightTime = getFlightTime();
   howitzer.draw(gout, flightTime);
   
   // Draw the projectile if it's in flight
   if (isProjectileInFlight())
   {
      Position pos = getProjectilePosition();
      double age = getFlightTime();
      gout.drawProjectile(pos, age);
      
      // Draw the flight path (trail)
      if (projectile.flightPath.size() > 1)
      {
         auto it = projectile.flightPath.begin();
         Position prevPos = it->pos;
         ++it;
         for (; it != projectile.flightPath.end(); ++it)
         {
            gout.drawLine(prevPos, it->pos, 0.8, 0.8, 0.8);
            prevPos = it->pos;
         }
      }
   }
}

/**********************************************************************
 * SIMULATOR : IS PROJECTILE IN FLIGHT
 * Check if the projectile is currently in flight
 ************************************************************************/
bool Simulator::isProjectileInFlight() const
{
   return !projectile.flightPath.empty();
}

/**********************************************************************
 * SIMULATOR : GET PROJECTILE POSITION
 * Get the current position of the projectile
 ************************************************************************/
Position Simulator::getProjectilePosition() const
{
   if (!projectile.flightPath.empty())
   {
      return projectile.flightPath.back().pos;
   }
   return Position(0.0, 0.0);
}

/**********************************************************************
 * SIMULATOR : CHECK GROUND COLLISION
 * Check if the projectile has hit the ground
 ************************************************************************/
bool Simulator::checkGroundCollision() const
{
   if (!isProjectileInFlight())
      return false;
   
   Position pos = getProjectilePosition();
   double groundElevation = ground.getElevationMeters(pos);
   
   // Check if projectile is below or at ground level
   return pos.getMetersY() <= groundElevation;
}

/**********************************************************************
 * SIMULATOR : GET FLIGHT TIME
 * Get the time since the projectile was fired
 ************************************************************************/
double Simulator::getFlightTime() const
{
   if (!projectile.flightPath.empty())
   {
      double fireTime = projectile.flightPath.front().t;
      return simulationTime - fireTime;
   }
   return 0.0;
}
