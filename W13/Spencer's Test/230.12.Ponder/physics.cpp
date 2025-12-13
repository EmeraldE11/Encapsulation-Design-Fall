/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/
  
 #include "physics.h"  // for the prototypes
 
 /*********************************************************
 * LINEAR INTERPOLATION
 * From a list of domains and ranges, linear interpolate
 *********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
    if (numMapping <= 0)
        return 0.0;

    if (domain <= mapping[0].domain)
        return mapping[0].range;

    if (domain >= mapping[numMapping - 1].domain)
        return mapping[numMapping - 1].range;

    for (int i = 0; i < numMapping - 1; ++i)
    {
        const Mapping& a = mapping[i];
        const Mapping& b = mapping[i + 1];

        if (domain >= a.domain && domain <= b.domain)
        {
            const double t =
                (domain - a.domain) / (b.domain - a.domain);

            return a.range + t * (b.range - a.range);
        }
    }

    return mapping[numMapping - 1].range;
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
   const Mapping gravityMapping[] =
   {
       { 0.0      , 9.8066500 }, // Sea level
       { 1000.0   , 9.8035700 },
       { 2000.0   , 9.8004900 },
       { 5000.0   , 9.7912700 },
       { 10000.0  , 9.7759400 },
       { 15000.0  , 9.7607000 },
       { 20000.0  , 9.7455600 },
       { 30000.0  , 9.7157700 },
       { 40000.0  , 9.6862600 },
       { 50000.0  , 9.6569900 },
       { 100000.0 , 9.5159500 }, // Edge of atmosphere
       { 200000.0 , 9.2218900 },
       { 400000.0 , 8.6884300 }  // ISS orbit range
   };
   
   double gravity = linearInterpolation(gravityMapping, sizeof(gravityMapping) / sizeof(gravityMapping[0]), altitude);
   return gravity;
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
   const Mapping densityMapping[] =
   {
      { 0.0     , 1.2250000 },
      { 1000.0  , 1.1120000 },
      { 2000.0  , 1.0070000 },
      { 3000.0  , 0.9093000 },
      { 4000.0  , 0.8194000 },
      { 5000.0  , 0.7364000 },
      { 6000.0  , 0.6601000 },
      { 7000.0  , 0.5900000 },
      { 8000.0  , 0.5258000 },
      { 9000.0  , 0.4671000 },
      { 10000.0 , 0.4135000 },
      { 15000.0 , 0.1948000 },
      { 20000.0 , 0.0889100 },
      { 25000.0 , 0.0400800 },
      { 30000.0 , 0.0184100 },
      { 40000.0 , 0.0039960 },
      { 50000.0 , 0.0010270 },
      { 60000.0 , 0.0003097 },
      { 70000.0 , 0.0000828 },
      { 80000.0 , 0.0000185 }
   };
   
   double density = linearInterpolation(densityMapping, sizeof(densityMapping) / sizeof(densityMapping[0]), altitude);
   return density;
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
   const Mapping speedSoundMapping[] =
   {
       { 0.0     , 340.29 },
       { 1000.0  , 336.43 },
       { 2000.0  , 332.53 },
       { 3000.0  , 328.58 },
       { 4000.0  , 324.59 },
       { 5000.0  , 320.54 },
       { 6000.0  , 316.45 },
       { 7000.0  , 312.30 },
       { 8000.0  , 308.10 },
       { 9000.0  , 303.84 },
       { 10000.0 , 299.53 },
       { 11000.0 , 295.07 },
       { 15000.0 , 295.07 },
       { 20000.0 , 295.07 },
       { 25000.0 , 295.07 },
       { 30000.0 , 295.07 }
   };
   
   double speedSound = linearInterpolation(speedSoundMapping, sizeof(speedSoundMapping) / sizeof(speedSoundMapping[0]), altitude);
   return speedSound;
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
   const Mapping dragMapping[] =
   {
      { 0.0  , 0.150 },
      { 0.20 , 0.155 },
      { 0.40 , 0.160 },
      { 0.60 , 0.165 },
      { 0.80 , 0.180 },
      { 0.90 , 0.220 },
      { 1.00 , 0.295 },
      { 1.05 , 0.330 },
      { 1.10 , 0.360 },
      { 1.20 , 0.345 },
      { 1.50 , 0.310 },
      { 2.00 , 0.275 },
      { 2.50 , 0.255 },
      { 3.00 , 0.245 },
      { 4.00 , 0.240 },
      { 5.00 , 0.235 }
   };
   
   double drag = linearInterpolation(dragMapping, sizeof(dragMapping) / sizeof(dragMapping[0]), speedMach);
   return drag;
}

