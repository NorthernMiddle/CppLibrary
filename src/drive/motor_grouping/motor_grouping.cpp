/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       James Pearman                                             */
/*    Created:      Sat Nov 02 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// MotorLf              motor         1               
// MotorLb              motor         2               
// MotorRb              motor         9               
// MotorRf              motor         10              
// GyroA                gyro          A               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

/*----------------------------------------------------------------------------*/
// define the motor groups
// the motors should have been setup with correct the gear cartridge ratios
// and the reverse flag set as necessary so they rotate in the correct direction
// when commanded to more forwards

motor_group   leftDrive( MotorLb, MotorLf );            // left hand side of the robot has two motors
motor_group   rightDrive( MotorRb, MotorRf );           // right hand side of the robot has two motors

/*----------------------------------------------------------------------------*/
// define the drivetrain
// this one is a smart drive which uses the gyro
// gyro and all motors were defined using graphical config
// we have 4 inch wheels
// drive is 16 inches wide between the wheels
// drive has a 16 inch wheelbase (between fron and back wheel axles)

smartdrive    robotDrive( leftDrive, rightDrive, GyroA, 12.56, 16, 16, distanceUnits::in );
// this is how the above definition would be if no gyro is used
// drivetrain    robotDrive( leftDrive, rightDrive, 12.56, 16, 16, distanceUnits::in );


/*----------------------------------------------------------------------------*/
//
// A task that just displays motor velocity and position
// The motors that are part of a motor group and/or drivetrain can still be accessed
// directly.

int displayTask() {
    while(1) {
      // display some useful info
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print( "  MotorLb    speed: %4.0f   position: %6.2f", MotorLb.velocity( percent ), MotorLb.position( rev ) );
      Brain.Screen.newLine();
      Brain.Screen.print( "  MotorLf    speed: %4.0f   position: %6.2f", MotorLf.velocity( percent ), MotorLf.position( rev ));
      Brain.Screen.newLine();
      Brain.Screen.print( "  MotorRb    speed: %4.0f   position: %6.2f", MotorRb.velocity( percent ), MotorRb.position( rev ));
      Brain.Screen.newLine();
      Brain.Screen.print( "  MotorRf    speed: %4.0f   position: %6.2f", MotorRf.velocity( percent ), MotorRf.position( rev ));
      Brain.Screen.newLine();
      Brain.Screen.newLine();

      // motor group velocity and position is returned for the first motor in the group
      Brain.Screen.print( "  leftDrive  speed: %4.0f   position: %6.2f", leftDrive.velocity( percent ), leftDrive.position( rev ));
      Brain.Screen.newLine();
      Brain.Screen.print( "  rightDrive speed: %4.0f   position: %6.2f", rightDrive.velocity( percent ), rightDrive.position( rev ));
      Brain.Screen.newLine();
      Brain.Screen.newLine();

      // drivetrain velocity is the average of the motor velocities for left and right
      Brain.Screen.print( "  robotDrive speed: %4.0f", robotDrive.velocity( percent ) );
      Brain.Screen.newLine();

      // no need to run this loop too quickly
      wait( 20, timeUnits::msec );
    }

    return 0;
}

//////////////////////////////////////////////////////////////////////
//
// --- MAIN PROGRAM ---
//
//////////////////////////////////////////////////////////////////////
int main() {
    // Initializing Robot Configuration. DO NOT REMOVE!
    vexcodeInit();

    robotDrive.setTimeout(10, seconds);                   // set 10 second timeout for robot drive movements
    robotDrive.setTurnVelocity(50, percent);              // set the speed used for drive turns
    task displayTaskInstance( displayTask );              // start the display task

    // loop forever
    while( true ) {
      // Buitton A is used to rotate drive 90 degrees
      if( Controller1.ButtonA.pressing() ) {
        // tell drivetrain to rotate 90 deg
        robotDrive.turnFor( 90, degrees );
        // wait for it to be done
        while( robotDrive.isMoving() )
          wait( 10, timeUnits::msec );
      }
      else {
        // not rotating, then we can drive using controller

        // read percent from controller axis
        int leftSpeed  = Controller1.Axis3.position();
        int rightSpeed = Controller1.Axis2.position();
        // deadband
        if( abs(leftSpeed)  < 10 ) leftSpeed  = 0;
        if( abs(rightSpeed) < 10 ) rightSpeed = 0;

        // send to motors
        leftDrive.spin( forward, leftSpeed, percent );
        rightDrive.spin( forward, rightSpeed, percent );
      }
          
      // no need to run this loop too quickly
      wait( 20, timeUnits::msec );
    }

    return 0;
}
