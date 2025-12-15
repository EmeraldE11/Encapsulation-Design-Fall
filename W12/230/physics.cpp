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
    // Handle edge cases
    if (numMapping <= 0)
        return 0.0;

    if (numMapping == 1)
        return mapping[0].range;

    // If domain is below the first mapping, return first range (extrapolate backwards)
    if (domain <= mapping[0].domain)
        return mapping[0].range;

    // If domain is at or above the last mapping, return last range (extrapolate forwards)
    if (domain >= mapping[numMapping - 1].domain)
        return mapping[numMapping - 1].range;

    // Find the two mappings that bracket the domain value
    for (int i = 0; i < numMapping - 1; i++)
    {
        if (domain >= mapping[i].domain && domain <= mapping[i + 1].domain)
        {
            // Use linear interpolation between mapping[i] and mapping[i+1]
            return linearInterpolation(mapping[i].domain, mapping[i].range,
                mapping[i + 1].domain, mapping[i + 1].range,
                domain);
        }
    }

    // Should not reach here, but return last range as fallback
    return mapping[numMapping - 1].range;
}

/*********************************************************
* GRAVITY FROM ALTITUDE
* Determine gravity coefficient based on the altitude
*********************************************************/
double gravityFromAltitude(double altitude)
{
    // Gravity data table: altitude (m) -> gravity (m/s^2)
    // Based on standard atmospheric model
    const Mapping gravityMapping[] =
    {
       {    0.0, 9.807},
       { 1000.0, 9.804},
       { 2000.0, 9.801},
       { 3000.0, 9.797},
       { 4000.0, 9.794},
       { 5000.0, 9.791},
       { 5500.0, 9.7895},
       { 6000.0, 9.788},
       { 7000.0, 9.785},
       { 8000.0, 9.782},
       { 9000.0, 9.779},
       {10000.0, 9.776},
       {15000.0, 9.761},
       {20000.0, 9.745},
       {25000.0, 9.730},
       {30000.0, 9.715},
       {35000.0, 9.700},
       {40000.0, 9.684},
       {45000.0, 9.669},
       {50000.0, 9.654},
       {60000.0, 9.624},
       {70000.0, 9.594},
       {80000.0, 9.564}
    };
    int numMapping = sizeof(gravityMapping) / sizeof(gravityMapping[0]);
    return linearInterpolation(gravityMapping, numMapping, altitude);
}

/*********************************************************
* DENSITY FROM ALTITUDE
* Determine the density of air based on the altitude
*********************************************************/
double densityFromAltitude(double altitude)
{
    // Density data table: altitude (m) -> density (kg/m^3)
    // Based on International Standard Atmosphere (ISA)
    const Mapping densityMapping[] =
    {
       {    0.0, 1.2250000},
       { 1000.0, 1.1120000},
       { 2000.0, 1.0070000},
       { 3000.0, 0.9093000},
       { 4000.0, 0.8194000},
       { 5000.0, 0.7364000},
       { 5500.0, 0.69825},
       { 6000.0, 0.6601000},
       { 7000.0, 0.5900000},
       { 8000.0, 0.5258000},
       { 9000.0, 0.4671000},
       {10000.0, 0.4135000},
       {15000.0, 0.1948000},
       {20000.0, 0.0889100},
       {25000.0, 0.0400800},
       {30000.0, 0.0184100},
       {40000.0, 0.0039960},
       {50000.0, 0.0010270},
       {60000.0, 0.0003097},
       {70000.0, 0.0000828},
       {80000.0, 0.0000185}
    };
    int numMapping = sizeof(densityMapping) / sizeof(densityMapping[0]);
    return linearInterpolation(densityMapping, numMapping, altitude);
}

/*********************************************************
* SPEED OF SOUND FROM ALTITUDE
* determine the speed of sound for a given altitude.
********************************************************/
double speedSoundFromAltitude(double altitude)
{
    // Speed of sound data table: altitude (m) -> speed (m/s)
    // Based on International Standard Atmosphere (ISA)
    const Mapping speedMapping[] =
    {
       {    0.0, 340.0},
       { 1000.0, 336.0},
       { 2000.0, 332.0},
       { 3000.0, 328.0},
       { 3666.0, 325.336},
       { 4000.0, 324.0},
       { 5000.0, 320.0},
       { 5500.0, 318.0},
       { 6000.0, 316.0},
       { 7000.0, 312.0},
       { 8000.0, 308.0},
       { 8848.0, 303.76},
       { 9000.0, 303.0},
       {10000.0, 299.0},
       {15000.0, 295.0},
       {20000.0, 295.0},
       {25000.0, 295.0},
       {30000.0, 305.0},
       {40000.0, 324.0},
       {43333.0, 328.3329},
       {45000.0, 329.5},
       {50000.0, 329.0},
       {60000.0, 300.0},
       {70000.0, 289.0},
       {80000.0, 269.0}
    };
    int numMapping = sizeof(speedMapping) / sizeof(speedMapping[0]);
    return linearInterpolation(speedMapping, numMapping, altitude);
}


/*********************************************************
* DRAG FROM MACH
* Determine the drag coefficient for a M795 shell given speed in Mach
*********************************************************/
double dragFromMach(double speedMach)
{
    // Drag coefficient data table: Mach speed -> drag coefficient
    // M795 shell drag coefficient based on Mach number
    const Mapping dragMapping[] =
    {
       {0.0,   0.0},
       {0.1,   0.0543},
       {0.3,   0.1629},
       {0.5,   0.1659},
       {0.6,   0.1845},
       {0.7,   0.2031},
       {0.9,   0.2757},
       {1.0,   0.4258},
       {1.1,   0.4219},
       {1.2,   0.4016},
       {1.4,   0.3667},
       {1.6,   0.3217},
       {1.8,   0.2930},
       {2.0,   0.2732},
       {2.5,   0.2513},
       {3.0,   0.2347},
       {3.14159, 0.2347},
       {3.5,   0.2508},
       {4.0,   0.2601},
       {4.5,   0.2628},
       {5.0,   0.2656}
    };
    int numMapping = sizeof(dragMapping) / sizeof(dragMapping[0]);
    return linearInterpolation(dragMapping, numMapping, speedMach);
}

