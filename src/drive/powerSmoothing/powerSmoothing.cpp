/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       rightArcadeDrive.cpp                                      */
/*    Author:       LoJac10                                                   */
/*    Created:      29 Nov 2022                                               */
/*    Description:  Power Smoothing w/ Right Joystick Arcade Drive            */
/*                  This program uses power smoothing on a a 4-motor          */
/*                  V5 drivetrain using a right joystick arcade control       */
/*                  method.                                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Con                  controller          
// LeftFront            motor         11
// LeftBack             motor         20
// RightFront           motor         1
// RightBack            motor         10          
// Drivetrain           drivetrain    11, 20, 1, 10, 2
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

// Deadband stops the motors when Axis values are close to zero.
const int DEADBAND = 8;

// Function Prototyping
void getExpoOutputValues(int leftMotorSpeed, int rightMotorSpeed, int arr[]);

// Arcade Drive: Right Joystick
void arcadeDrive_right(){
  while (true) {

    // motorspeed variables
    int leftMotorSpeed, rightMotorSpeed, arr[2];

    // Get the velocity percentage of the left motor. (Axis2 + Axis1)
    // Get the velocity percentage of the right motor. (Axis2 - Axis1)
    leftMotorSpeed = Controller1.Axis2.position() + Controller1.Axis1.position();
    rightMotorSpeed = Controller1.Axis2.position() - Controller1.Axis1.position();
    
    // smoothing function involuted
    getExpoOutputValues(leftMotorSpeed, rightMotorSpeed, arr);

    // Set the speed of the left front motor. 
    // If the value of the joystick is less than the deadband threshold, set the motor velocity to zero.
    if (abs(leftMotorSpeed) < DEADBAND ) {
      // Set the speed to zero.
      LeftFront.setVelocity(0, percent);
    } 
    else {
      // Set the speed to leftMotorOutput
      LeftFront.setVelocity(arr[0], percent);
    }

    // Set the speed of the left back motor.
    // If the value of the joystick is less than the deadband threshold, set the motor velocity to zero.
    if (abs(leftMotorSpeed) < DEADBAND ) {
      // Set the speed to zero.
      LeftBack.setVelocity(0, percent);
    } 
    else {
      // Set the speed to leftMotorOutput
      LeftBack.setVelocity(arr[0], percent);
    }

    // Set the speed of the right front motor. 
    // If the value of the joystick is less than the deadband threshold, set the motor velocity to zero.
    if (abs(rightMotorSpeed) < DEADBAND ) {
      // Set the speed to zero
      RightFront.setVelocity(0, percent);
    } 
    else {
      // Set the speed to rightMotorOutput
      RightFront.setVelocity(arr[1], percent);
    }

    // Set the speed of the right back motor. 
    // If the value of the joystick is less than the deadband threshold, set the motor velocity to zero.
    if (abs(rightMotorSpeed) < DEADBAND ) {
      // Set the speed to zero
      RightBack.setVelocity(0, percent);
    } 
    else {
      // Set the speed to rightMotorOutput
      RightBack.setVelocity(arr[1], percent);
    }

    // Spin motors in the forward direction.
    LeftBack.spin(forward);
    LeftFront.spin(forward);
    RightBack.spin(forward);
    RightFront.spin(forward);

    wait(25, msec);
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

// drive power smoothing
void getExpoOutputValues(int leftMotorSpeed, int rightMotorSpeed, int arr[])
{
  
  int leftMotorOutput, rightMotorOutput, directionLeft, directionRight;
  double magicNumber = 1.0356;
      
  leftMotorOutput = 0;
  rightMotorOutput = 0;

  // ignore joystick input if it's too small
  if(abs(leftMotorSpeed) > DEADBAND){
  // direction is either 1 or -1, based on joystick value
  directionLeft = abs(leftMotorSpeed) / leftMotorSpeed;
  // plug joystick value into exponential function
  leftMotorOutput = directionLeft * (1.2 * pow(magicNumber, abs(leftMotorSpeed)) - 1.2 + 0.2 * abs(leftMotorSpeed));
  }
  // output smoothed power to left motor
  arr[0] = leftMotorOutput;

   // ignore joystick input if it's too small
  if(abs(rightMotorSpeed) > DEADBAND){
  // direction is either 1 or -1, based on joystick value
  directionRight = abs(rightMotorSpeed) / rightMotorSpeed;
  // plug joystick value into exponential function
  rightMotorOutput = directionRight * (1.2 * pow(magicNumber, abs(rightMotorSpeed)) - 1.2 + 0.2 * abs(rightMotorSpeed));
  }
  // output smoothed power to right motor
  arr[1] = rightMotorOutput;

  // the output is then used with whatever type of driver control layout (tank, arcarde, etc.)
  // using acrade drive
}
