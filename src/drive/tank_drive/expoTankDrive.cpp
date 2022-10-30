/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       expoTankDrive.cpp                                         */
/*    Author:       VEX                                                       */
/*    Created:      Oct 30th, 2022                                            */
/*    Description:  Exponential Power Tank Drive                              */
/*    This module allows you to control a V5 Robot using both                 */
/*    joystick (Tank Drive). The power level is set using a                   */
/*    exponential power setting. Adjust the deadband value for                */
/*    more accurate movements.                                                */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "tankDrive.h"
using namespace vex;

//tank drive function
int tankDrive_f(){

  // declare count variable for iteration count
  int count = 0;

  // clear V5 screen
  Brain.Screen.clearScreen();

  // deadband threshold - stops the motors when Axis values are close to zero.
  const int deadband = 10;

  //print motor info to screen
  while(true){
    Brain.Screen.printAt(1,1,"Tank Drive has started");
    Brain.Screen.printAt(2,1, "The LBmotor Encoder Pos: %d", LBmotor.position(rev));
    Brain.Screen.printAt(3,1, "The RBmotor Encoder Pos: %d", RBmotor.position(rev));
    Brain.Screen.printAt(4,1, "Battery %.2f%% full", (Brain.Battery.voltage()/Brain.Battery.capacity())*100); 
    count++;

    // Get the velocity percentage of the left motor. (Axis3)
    // Get the velocity percentage of the right motor. (Axis2)
    // exponential motor speed function setup
    int LeftMotorSpeed = ((Controller1.Axis3.value())^2)/(100^(2-1));
    int RightMotorSpeed = ((Controller1.Axis2.value())^2)/(100^(2-1));

    // next two lines are used to get static speed from position
    // int leftMotorSpeed = Controller1.Axis3.position();
    //int rightMotorSpeed = Controller1.Axis2.position();

    // Set the speed of the left motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(LeftMotorSpeed) < deadband) {
      // Set the speed to zero.
      LBmotor.setVelocity(0, percent);
    } else {
      // Set the speed to leftMotorSpeed
      LBmotor.setVelocity(LeftMotorSpeed, percent);
    }

    // Set the speed of the right motor. If the value is less than the deadband,
    // set it to zero.
    if (abs(RightMotorSpeed) < deadband) {
      // Set the speed to zero
      RBmotor.setVelocity(0, percent);
    } else {
      // Set the speed to rightMotorSpeed
      RBmotor.setVelocity(RightMotorSpeed, percent);
    }

    // Spin both motors in the forward direction.
    LBmotor.spin(forward);
    RBmotor.spin(forward);

    wait(25, msec);
  }
}
