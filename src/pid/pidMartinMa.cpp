// header

#include "vex.h"
using namespace vex;

/** Define Motor Gearings **/
#define VEX393Torque    627.2
#define VEX393Standard  392.0
#define VEX393Turbo     261.333

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
  * reading: ticks -- 393 motors: VEX393Torque -- 627.2 ticks/rev
  * 1 turn of wheels -- 4 inch wheels -- 627.2 * 2 ticks
  * 1 turn of each wheel 4*PI inches
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
