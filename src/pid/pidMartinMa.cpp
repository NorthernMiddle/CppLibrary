// header

#include "vex.h"
using namespace vex;

// define PI
#define PI = 3.14159265359;

// define V5 Motor Gearing
#define BLUE_MOTOR_CARTRIDGE 2.4   // turbo
#define GREEN_MOTOR_CARTRIDGE 1.6  // highspeed
#define RED_MOTOR_CARTRIDGE 1      // torque


/**
 * Converts inches to quadrature encoder ticks, for the purpose of setting targets in PIDs
 * Usage:
 *  inchesToTicks(10, 3.25, 1, BLUE_MOTOR_CARTRIDGE);
 *
 * @param float unit The number inches to convert to ticks
 * @param float wheelDiameter The diameter of the wheel, in inches
 * @param float gearing The external gear ration (Speed Up => x, Torque Up => 1/x)
 * @param float motorGear The internal gear ratio of the motor (constants TURBO, HIGHSPEED, and TORQUE have been specified)
 */
float inchesToTicks(float unit, float wheelDiameter, float gearing, float motorGear) 
{
    return (
        (unit / (motorGear * gearing)) / // Cancel out gear ratio
        (wheelDiameter * PI) // Divide by circumfrence to solve for rotations
    ) * 360; // 360 ticks in a rotation
}


/**
  * 
  *
  * 
  */
void moveBase(double speed)
{
  SmartDrive.setDriveVelocity( speed, velocityUnits::rpm );
}


/**
  * 
  *
  * 
  */
void pidBaseControl(double target)
{
  // ...
  // ...
  
  while(true)
  {
    wait( 40, msec );
  }
}



//////////////////////////////////
//
// main
//
///////////////////////////////////////////////
task main()
{
  while( true )
  {
    wait( 20, msec );
  }
}
