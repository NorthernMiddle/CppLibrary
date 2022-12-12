/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Wed Dec 04 2019                                           */
/*    Description:  This program will use the Inertial Sensor to              */
/*                  display pitch, acceleration of the y axis, and            */
/*                  the gyro rate of the y axis. The example will             */
/*                  also print the current heading and rotation in degrees    */
/*                  of the Inertial Sensor.                                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Inertial20           inertial      20
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Inertial20.calibrate();
  // waits for Inertial Sensor to calibrate 
  while (Inertial20.isCalibrating()) {
    wait(100, msec);
  }

  while (true) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);

    // Prints the pitch ( rotation around the side to side axis)
    Brain.Screen.print("Pitch Orientation (deg): ");
    Brain.Screen.print((Inertial20.orientation(pitch, degrees)));
    Brain.Screen.newLine();

    // Prints the acceleration of the y axis.
    Brain.Screen.print("Y-axis Acceleration (G): ");
    Brain.Screen.print(Inertial20.acceleration(yaxis));
    Brain.Screen.newLine();

    // Prints the gyro rate of the y axis
    Brain.Screen.print("Y-axis Gyro Rate (DPS): ");
    Brain.Screen.print(Inertial20.gyroRate(yaxis, dps));
    Brain.Screen.newLine();

    // Print the current heading in degrees
    Brain.Screen.print("Inertial Sensor's current heading (deg): ");
    Brain.Screen.print(Inertial20.heading());
    Brain.Screen.newLine();

    // Print the current angle of rotation in degrees
    Brain.Screen.print("Inertial Sensor's current angle of rotation (deg): ");
    Brain.Screen.print(Inertial20.rotation());
    wait( 25, msec );
  }
}
