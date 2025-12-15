/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    Noah McCarthy
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
 #include "acceleration.h"
 #include "uiDraw.h"
 #include <cmath>
 using namespace std;


 void Projectile::reset()
 {
	 mass = DEFAULT_PROJECTILE_WEIGHT;
	 radius = DEFAULT_PROJECTILE_RADIUS;
	 flightPath.clear();
 }

 void Projectile::fire(const Position& pos, double simulationTime, const Angle& angle, double muzzleVelocity)
 {
	 // reset first
	 flightPath.clear();
	 double dx = muzzleVelocity * sin(angle.getRadians());
	 double dy = muzzleVelocity * cos(angle.getRadians());

	 PositionVelocityTime pvt;
	 pvt.pos = pos;
	 pvt.v.setDX(dx);
	 pvt.v.setDY(dy);
	 pvt.t = simulationTime;

	 flightPath.push_back(pvt);
 }

 void Projectile::advance(double simulationTime)
 {
	 // If flight path is empty, nothing to advance
	 if (flightPath.empty())
	 {
		 return;
	 }

	 // Get the last moment in the flight path
	 auto lastMoment = flightPath.back();

	 // Get current position, velocity, and time
	 double x = lastMoment.pos.getMetersX();
	 double y = lastMoment.pos.getMetersY();
	 double dx = lastMoment.v.getDX();
	 double dy = lastMoment.v.getDY();
	 double t0 = lastMoment.t;

	 double deltaTime = simulationTime - t0;

	 // Compute current velocity magnitude
	 double velocity = sqrt(dx * dx + dy * dy);

	 // Get altitude (y position in meters)
	 double altitude = y;

	 // Compute gravity from altitude
	 double gravity = gravityFromAltitude(altitude);

	 // Compute air density from altitude
	 double density = densityFromAltitude(altitude);

	 // Compute speed of sound from altitude
	 double speedSound = speedSoundFromAltitude(altitude);

	 // Compute Mach number (velocity / speed of sound)
	 double mach = (speedSound > 0.0) ? (velocity / speedSound) : 0.0;

	 // Compute drag coefficient from Mach number
	 double dragCoefficient = dragFromMach(mach);

	 // Compute drag force
	 double dragForce = forceFromDrag(density, dragCoefficient, radius, velocity);

	 // Convert drag force to acceleration
	 double dragAcceleration = accelerationFromForce(dragForce, mass);

	 // Compute direction of travel (angle from velocity components)
	 // Use atan2(dx, dy) where 0 is up
	 double travelAngle = atan2(dx, dy);

	 // Compute drag acceleration components (drag opposes velocity)
	 double dragDDX = -dragAcceleration * sin(travelAngle);
	 double dragDDY = -dragAcceleration * cos(travelAngle);

	 // Total acceleration components
	 // Horizontal: only drag (no gravity in x direction)
	 double ddx = dragDDX;
	 // Vertical: gravity (downward, negative) + drag
	 double ddy = -gravity + dragDDY;

	 // Calculate new velocity
	 double newDX = dx + ddx * deltaTime;
	 double newDY = dy + ddy * deltaTime;

	 // Calculate new position using: s = s0 + v*t + 0.5*a*t^2
	 double newX = x + dx * deltaTime + 0.5 * ddx * deltaTime * deltaTime;
	 double newY = y + dy * deltaTime + 0.5 * ddy * deltaTime * deltaTime;

	 // Create new moment in flight path
	 PositionVelocityTime nextMoment;
	 nextMoment.pos.setMetersX(newX);
	 nextMoment.pos.setMetersY(newY);
	 nextMoment.v.setDX(newDX);
	 nextMoment.v.setDY(newDY);
	 nextMoment.t = simulationTime;

	 // Add new moment to flight path
	 flightPath.push_back(nextMoment);
 }

Position Projectile::getPosition() const
{
   if (flightPath.empty())
      return Position(0.0, 0.0);
   return flightPath.back().pos;
}

double Projectile::getAltitude() const
{
   if (flightPath.empty())
      return 0.0;
   return flightPath.back().pos.getMetersY();
}

double Projectile::getSpeed() const
{
   if (flightPath.empty())
      return 0.0;
   const Velocity& v = flightPath.back().v;
   double dx = v.getDX();
   double dy = v.getDY();
   return sqrt(dx * dx + dy * dy);
}

double Projectile::getFlightTime(double currentTime) const
{
   if (flightPath.empty())
      return 0.0;
   return currentTime - flightPath.front().t;
}

void Projectile::draw(ogstream& gout) const
{
   if (flightPath.empty())
      return;

   // Draw the projectile at its current position
   Position pos = getPosition();
   double age = flightPath.back().t - flightPath.front().t;
   gout.drawProjectile(pos, age);

   // Draw the flight path (trail)
   if (flightPath.size() > 1)
   {
      auto it = flightPath.begin();
      Position prevPos = it->pos;
      ++it;
      for (; it != flightPath.end(); ++it)
      {
         gout.drawLine(prevPos, it->pos, 0.8, 0.8, 0.8);
         prevPos = it->pos;
      }
   }
}