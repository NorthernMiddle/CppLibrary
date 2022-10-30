/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       smootDrive.cpp                                            */
/*    Author:       NMS_RP                                                    */
/*    Created:      01 Oct 2022                                               */
/*    Description:  Operation control file for all driver functions           */
/*                  and thread calls                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// VEX V5 C++ Project
#include "vex.h"

using namespace vex;

// tank drive variables
double l_joyStickValue, r_joyStickValue, ceil_JoyStickInputValue,
       ceil_l_joyStickValue, ceil_r_joyStickValue, 
       smoothDrive_lval, smoothDrive_rval, result01, result02,
       velocityCurveSetting;

/** --- Power Scale Factor Functions for Velocity Adjustment --- 
  * Description: 
  *    Functions used to achieve more sensitivity at low motor velocity
  *    used for precise movements while still being able to use 100% velocity
  @ ceiling functions
  @ function defintions
  @ calls for left & right joysticks
  */

/**
  * Motor Velocity Acceleration Smoothing Function
  *
  * Ref: See _Colossus VEX Forum Sept. 2019
  * Ref: 'What do you think is a more efficient way to drive your robot?'
  * Ref: Post 41/47
  *
  @ PARAM base value --> joystick input value
  @ PARAM exponent value --> expValue selected smoothing velocity curve
  */ 
double motorVelocitySmoothValues(double ceil_l_joyStickValue, double ceil_r_joyStickValue, int expValue){
  smoothDrive_lval = ( (pow(ceil_l_joyStickValue, expValue)) / (pow( 100, (expValue - 1))) );
  smoothDrive_rval = ( (pow(ceil_r_joyStickValue, expValue)) / (pow( 100, (expValue - 1))) );
  return 0;
}

/** --- tankDrive_f is a callback function ---
  * Description:
  *   Function for tank drive. Function to be registered to a thread for continuous use.
  *   Function registered to thread tankdrive_t
  */
int tankDrive_f(){

  const int Deadband = 5; 
  int count, velocityCurveSetting;

  count = 0;
  while(true){
    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("TankDrive has iterated %d times", count);
    count++;

    // tank drive variable declare & intialize
    l_joyStickValue = Controller1.Axis2.position();   // left-joystick tank drive control
    r_joyStickValue = Controller1.Axis3.position();   // right-joystick tank drive control

    // display velocity values
    Brain.Screen.setCursor(3,1);
    Brain.Screen.print("l_joystick: %3.2f ", l_joyStickValue);
    Brain.Screen.setCursor(4,1);
    Brain.Screen.print("r_joystick: %3.2f ", r_joyStickValue);

    // deadband, set to 0 if below the deadband value
    // fabs --> floating absolute value -- C++11
    if( fabs( l_joyStickValue ) < Deadband ) l_joyStickValue = 0;
    if( fabs( r_joyStickValue ) < Deadband ) r_joyStickValue = 0;
  
    // ceiling up joystick input values
    ceil_l_joyStickValue = ceil(l_joyStickValue);
    ceil_r_joyStickValue = ceil(r_joyStickValue);

    // display velocity values
    Brain.Screen.setCursor(6,1);
    Brain.Screen.print("ceil_l_joystick: %3.2f ", ceil_l_joyStickValue);
    Brain.Screen.setCursor(7,1);
    Brain.Screen.print("ceil_r_joystick: %3.2f ", ceil_r_joyStickValue);
 
    // acceleration smoothing function call and variable assignment
    // acceleration curve is using a cubic function model
    velocityCurveSetting = 3;
    motorVelocitySmoothValues(ceil_l_joyStickValue, ceil_r_joyStickValue, velocityCurveSetting);
    
    // display velocity values
    Brain.Screen.setCursor(9,1);
    Brain.Screen.print("l_motors -->   %Raw: %3.2f   Fix: %3.2f", l_joyStickValue, smoothDrive_lval );
    Brain.Screen.setCursor(10,1);
    Brain.Screen.print("r_motors -->   %Raw: %3.2f   Fix: %3.2f", r_joyStickValue, smoothDrive_rval );

    /* --- send velocity value to motors --- */
    // left tank motors
    LFmotor.spin( directionType::fwd, smoothDrive_lval, velocityUnits::pct );
    LBmotor.spin( directionType::fwd, smoothDrive_lval, velocityUnits::pct );

    // right tank motors
    RFmotor.spin( directionType::fwd, smoothDrive_rval, velocityUnits::pct );
    RBmotor.spin( directionType::fwd, smoothDrive_rval, velocityUnits::pct );


    /* You must sleep threads by using the 'this_thread::sleep_for(unit in
      msec)' command to prevent this thread from using all of the CPU's
      resources. */
    this_thread::sleep_for( 25 );
  }

/* A threads's callback must return an int, even though the code will never
  get here. You must return an int here. Threads can exit, but this one does not. */
return 0;
}
