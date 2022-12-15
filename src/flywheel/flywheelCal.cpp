/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       DK 7700                                                   */
/*    Created:      May 13, 2022                                              */
/*    Description:  Speed Control for 2 motor Flywheel testing                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// F1                   motor         12              
// F2                   motor         21              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
double OldError = 0.0;
double TBHval = 0.0;
double FWDrive = 0.0;

void spinFlywheel(double speed) {
  speed = speed * 120; // speed is in percentage so convert to mV 100% = 12000
                       // mV
  F1.spin(forward, speed, voltageUnits::mV);
  F2.spin(forward, speed, voltageUnits::mV);
}

void controlFlywheelSpeed(double target) {
  double kI = .025;
  double speed = F1.velocity(percent);
  double error = target - speed;
  double fwDrive = FWDrive + kI * error;
// :D
   Brain.Screen.printAt(1, 40, " speed = %.2f ", speed);
  // Keep drive between 0 to 100%
  if (fwDrive > 100)
    fwDrive = 100;
  if (fwDrive < 0)
    fwDrive = 0;
  // Check for zero crossing
  if (error * OldError < 0) {
    fwDrive = 0.5 * (fwDrive + TBHval);
    TBHval = fwDrive;
  }
  

  Brain.Screen.printAt(180, 40, "fwdrive %.1f  ", fwDrive);
  spinFlywheel(fwDrive);

  FWDrive = fwDrive;
  OldError = error;
}

void flywheelMonitor() {
  double current1 = F1.current();
  double current2 = F2.current();
  double t1 = F1.temperature(celsius);
  double t2 = F2.temperature(celsius);

  Brain.Screen.printAt(1, 60, "F1 current = %.1f   Temp = %.1f   ", current1, t1);
  Brain.Screen.printAt(1, 80, "F2 current = %.1f   Temp = %.1f   ", current2, t2);
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {

  double targetSpeed = 0.0;
  bool alg = true;
  bool flag = true;
  while (true) {

    if (Controller1.ButtonA.pressing())
      targetSpeed = 0;

    if (Controller1.ButtonB.pressing())
      targetSpeed = 17;

    if (Controller1.ButtonY.pressing())
      targetSpeed = 34;
    if (Controller1.ButtonX.pressing())
      targetSpeed = 68;
    if (Controller1.ButtonUp.pressing())
      targetSpeed = 100;
    Brain.Screen.printAt(1, 20, "target speed = %.2f ", targetSpeed);
    if(Controller1.ButtonDown.pressing() && flag){
      flag = false;
      alg = !alg;
    }
    if (!Controller1.ButtonDown.pressing()){
      flag = true;
    }
    if (alg){
      controlFlywheelSpeed(targetSpeed);
      Brain.Screen.printAt(1, 120, "controlled speed    ");
    }
    else {
      spinFlywheel(targetSpeed);
        double speed = F1.velocity(percent);

      Brain.Screen.printAt(1, 120, "not controlled     ");
      Brain.Screen.printAt(1, 40, " speed = %.2f ", speed);
    }

    
      
  //targetSpeed = targetSpeed / 6.0;
  // ew
  // help 
  // currently suffering from secondhand smoking
  // i am now a potted potato
  // "secondhand potato" - aidan 
 // h
 // the mitochondria is the powerhouse of the cell losers
 //  
   //spinFlywheel(targetSpeed);
   // pogchamp
   // ur mom
   // deez nuts
   // lmao
   // hkgtckutxkrtyghv
    flywheelMonitor();
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
