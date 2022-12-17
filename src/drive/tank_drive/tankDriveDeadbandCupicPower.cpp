/*----------------------------------------------------------------------------------------*/
/*                                                                                        */
/*   	Module:       tankDrive.cpp                                                        */
/*   	Author:       NMS_RP: 650N                                                         */
/*   	Created:      16 Dec 2019                                                          */
/*  	Description:  tank drive with deadband and cubic power input for VEX V5            */
/*                                                                                        */
/*----------------------------------------------------------------------------------------*/

// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

// deadband threshold
const int deadband = 15; 

/** 
  * --- Cubic Scale Factor Functions for Power Adjustment --- 
  * Description: Functions used to achieve more sensitivity at low motor power
  * used for precise movements while still being able to use 100% power
  *
  */
// ceiling function, function definition, function call
double ceil_drive_lval( double drive_lval ){
  return ceil(drive_lval);
}

double ceil_drive_rval( double drive_rval ){
  return ceil(drive_rval);
}

// cube function, function definition, function call
double cube_drive_lval( double ceildrive_lval ){			// tank drive cube scale factor left joy
    return  pow(ceildrive_lval/100.0, 3.0)*100.0;
}

double cube_drive_rval( double ceildrive_rval ){				// tank drive cube scale factor right joy
    return  pow(ceildrive_rval/100.0, 3.0)*100.0;
}

/**
  * --- tankDrive_f is a callback function ---
  * func to be registered to a thread
  * func registered to thread tankdrive_t
  *
  */
int tankDrive_f(){
  int count = 0;
    while(true){
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("TankDrive has iterated %d times", count);
      count++;

      // tank drive func --- variable intializations
      double drive_lval = Controller1.Axis3.position();          // tank drive control
      double drive_rval = Controller1.Axis2.position();          // tank drive control

      // deadband, set to 0 if below the deadband value
      if( fabs( drive_lval ) < deadband ) drive_lval = 0;
      if( fabs( drive_rval ) < deadband ) drive_rval = 0;

      double ceildrive_lval = ceil_drive_lval( drive_lval );
      double ceildrive_rval = ceil_drive_rval( drive_rval );

      double cubedrive_lval = cube_drive_lval( ceildrive_lval );
      double cubedrive_rval = cube_drive_rval( ceildrive_rval );
    
      // just for fun, display the values
      Brain.Screen.setCursor(3,1);
      Brain.Screen.print("Raw %6.2f cube %6.2f", drive_lval, cubedrive_lval );
      Brain.Screen.setCursor(4,1);
      Brain.Screen.print("Raw %6.2f cube %6.2f", drive_rval, cubedrive_rval );

      /* --- send to motors --- */
      // left tank motors
      LFmotor.spin( directionType::fwd, cubedrive_lval, velocityUnits::pct );
      LBmotor.spin( directionType::fwd, cubedrive_lval, velocityUnits::pct );
      // right tank motors
      RFmotor.spin( directionType::fwd, cubedrive_rval, velocityUnits::pct );
      RBmotor.spin( directionType::fwd, cubedrive_rval, velocityUnits::pct );

      /* You must sleep threads by using the 'this_thread::sleep_for(unit in
        msec)' command to prevent this thread from using all of the CPU's
        resources. */
      this_thread::sleep_for( 25 );
    }
  /* A threads's callback must return an int, even though the code will never
    get here. You must return an int here. Threads can exit, but this one does not. */
  return 0;
}
