/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       hal.h                                                     */
/*    Author:       NMS_RP                                                    */
/*    Created:      8 Dec 2019                                                */
/*    Description:  Hardware Abstraction layer. Abstacts motors &             */
/*                  sensors into a set of accessor functions                  */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LBmotor              Green Motor    2              
// LFmotor              Green Motor    1              
// RBmotor              Green Motor    10              
// RFmotor              Green Motor    9                         
// ---- END VEXCODE CONFIGURED DEVICES ----

/*
// VEX V5 C++ Project
#include "vex.h"
#include "motor.h"
#include "util.h"
#include "pid.h"
#include "profile.h"
using namespace vex;
*/

/*----------------------------------------------------------------------------*/
// define the motor groups
// the motors should have been setup with correct the gear cartridge ratios
// and the reverse flag set as necessary so they rotate in the correct direction
// when commanded to more forwards

// left hand side of the robot has two motors
   motor_group   leftDrive( LBmotor, LFmotor );

// right hand side of the robot has two motors
   motor_group   rightDrive( RBmotor, RFmotor );

/*----------------------------------------------------------------------------*/
// define the drivetrain
// this one is a smart drive which uses the gyro
// gyro and all motors were defined using graphical config
// we have 4 inch wheels
// drive is 16 inches wide between the wheels
// drive has a 16 inch wheelbase (between front and back wheel axles)
//
// smartdrive    robotDrive( leftDrive, rightDrive, GyroA, 12.56, 16, 16, distanceUnits::in );
// this is how the above definition would be if no gyro is used
// drivetrain    robotDrive( leftDrive, rightDrive, 12.56, 16, 16, distanceUnits::in );


/*----------------------------------------------------------------------------*/

/* A task that just displays motor velocity and position
// The motors that are part of a motor group and/or drivetrain can still be accessed
// directly.
//
int displayTask() {
    while(1) {
      // display some useful info
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print( "  LBmotor    speed: %4.0f   position: %6.2f", LBmotor.velocity( percent ), LBmotor.position( rev ) );
      Brain.Screen.newLine();
      Brain.Screen.print( "  LFmotor    speed: %4.0f   position: %6.2f", LFmotor.velocity( percent ), LFmotor.position( rev ));
      Brain.Screen.newLine();
      Brain.Screen.print( "  RBmotor    speed: %4.0f   position: %6.2f", RBmotor.velocity( percent ), RBmotor.position( rev ));
      Brain.Screen.newLine();
      Brain.Screen.print( "  RFmotor    speed: %4.0f   position: %6.2f", RFmotor.velocity( percent ), RFmotor.position( rev ));
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
}*/
/*----------------------------------------------------------------------------*/


// Section 1: Drive 
void drive(int left, int right) {
  robot.leftDrive = left;
  robot.rightDrive = right;
}



void driveReset() {                  // resetRotation(void)
  leftDrive.resetRoation();          // Resets the rotation of the left drive motor encoders to zero  
  rightDrive.resetRoation();         // Resets the rotation of the right drive motor encoders to zero       
}

int driveOffset() {
  // return SensorValue[leftDrive] - SensorValue[rightDrive];
  return leftDrive.encoder.rotation() - rightDrive.encoder.rotion();  
}

/*
void driveHandle() {
    motorTarget[port4] = -robot.leftDrive;
    motorTarget[port6] = -robot.leftDrive;
    motorTarget[port8] = -robot.leftDrive;
    motorTarget[port5] = robot.rightDrive;
    motorTarget[port7] = robot.rightDrive;
    motorTarget[port9] = robot.rightDrive;
}
*/

/**
  * Drives a set number of specified inches
  */
 /*
pidConfiguration drivePID;
void driveDistance(int inches) {
    pidConfigure(drivePID, 0, 0, 0);
    pidReset(drivePID);
    int targetTicks = inchesToTicks(inches, 3.25, 3, TORQUE);
    while(SensorValue[leftDrive] != targetTicks || SensorValue[rightDrive] != targetTicks) {
        int syncspeed = pidCalculate(drivePID, driveOffset()),
            basespeed = 90 * profileTrapezoid(targetTicks, SensorValue[leftDrive], 1/8); 
        drive(basespeed - syncspeed, basespeed + syncspeed);
    }
    // Stop the drive after we've completed the distance
    drive(0, 0);
}
*/

// Section 2: tray Lift 
/*
void traySet(int value) {
    motorTarget[port8] = value;
}
void trayHandle() {
    if(robot.tray == UP && SensorValue[TLmotor] > 150) {
        traySet(100);
    } else if (robot.mogo == DOWN && SensorValue[TLmotor] < 2400) {
        traySet(-100);
    } else {
        traySet(0);
    }
}
void trayUp() {
    robot.tray = UP;
}
void mogoDown() {
    robot.tray = DOWN;
}
task handleAll() {
    while(true) {
        trayHandle();
        driveHandle();
        motorHandle();
        wait1Msec(20);
    }
}
*/
