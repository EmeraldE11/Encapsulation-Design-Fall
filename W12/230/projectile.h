/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile;
class Simulator; 

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT), radius(DEFAULT_PROJECTILE_RADIUS) {}



   // advance the round forward until the next unit of time
   void advance(double simulationTime);

   // clear the flight path and reset the member variables
   void reset();

   // based on a provided position, simulator time, angle, and muzzle velocity, put the first element in the flight path
   void fire(const Position& pos, double simulationTime, const Angle& angle, double muzzleVelocity);

   // check if projectile is currently flying
   bool flying() const { return !flightPath.empty(); }

   // get the current position of the projectile
   Position getPosition() const;

   // get the current altitude (y position in meters)
   double getAltitude() const;

   // get the current speed (magnitude of velocity in m/s)
   double getSpeed() const;

   // get the flight time (time since fired)
   double getFlightTime(double currentTime) const;

   // draw the projectile and its flight path
   void draw(ogstream& gout) const;


private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      Position pos;
      Velocity v;
      double t;
   };

   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;
   
   // Make Simulator a friend so it can access flightPath for drawing
   friend class Simulator;
};