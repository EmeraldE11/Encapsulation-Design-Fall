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
	 // flightPath[last]
	 auto lastMoment = flightPath.back();

	 // define last positions and velocity
	 double x = lastMoment.pos.getMetersX();
	 double y = lastMoment.pos.getMetersY();
	 double dx = lastMoment.v.getDX();
	 double dy = lastMoment.v.getDY();
	 double t0 = lastMoment.t;

	 double deltaTime = simulationTime - t0;

	 Acceleration a;
	 double ddx = a.getDDX();
	 double ddy = a.getDDY();
	 
	 PositionVelocityTime nextMoment;

	 // calculate new positions and velocity
	 // velocity update
	 double newDX = dx + ddx * deltaTime;
	 double newDY = dy + ddy * deltaTime;


	 // position update
	 double newX = x + dx * deltaTime + 0.5 * ddx * deltaTime * deltaTime;
	 double newY = y + dy * deltaTime + 0.5 * ddy * deltaTime * deltaTime;

	 
	 // define new positions and velocity
	 nextMoment.pos.setMetersX(newX);
	 nextMoment.pos.setMetersY(newY);
	 nextMoment.v.setDX(newDX);
	 nextMoment.v.setDY(newDY);
	 nextMoment.t = simulationTime;

	 // append to end of flightPath[]
	 flightPath.push_back(nextMoment);

 }
