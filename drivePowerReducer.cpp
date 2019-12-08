#include "robot-config.h"

/*---------------------------------------------------------------------------------------------------
robot-config.h
using namespace vex;
vex::brain Brain;
vex::motor LeftMotorFront  (vex::PORT1, vex::gearSetting::ratio18_1, false);
vex::motor LeftMotorBack  (vex::PORT2, vex::gearSetting::ratio18_1, false);
vex::motor RightMotorFront (vex::PORT9, vex::gearSetting::ratio18_1, true);
vex::motor RightMotorBack (vex::PORT10, vex::gearSetting::ratio18_1, true);
vex::controller Controller1 = vex::controller();

Robot Configuration:
[Smart Port]    [Name]        		[Type]           [Description]       		[Reversed]
Motor Port 1    LeftMotorFront     	V5 Smart Motor   Left side Front motor     	false
Motor Port 2	LeftMotorBack		V5 Smart Motor	 Left side Back motor		false
Motor Port 9    RightMotorFront    	V5 Smart Motor   Right side Front motor    	true
Motor Port 10	RightMotorBack		V5 Smart Motor	 Right side Back motor
---------------------------------------------------------------------------------------------------*/


/*+++++++++++++++++++++++++++++++++++++++++++++| Notes |++++++++++++++++++++++++++++++++++++++++++++++
Topic: 		 Tank Drive Control for Joysticks with a Power Reducer Percentage
Description: This program will instruct your robot to move forward at a reduced power percentage of
			 the user choosing based on power reducer variable (PRV).
			 Program does not set velocity of motors directly.
			 There is a two second pause at the beginning of the program.
----------------------------------------------------------------------------------------------------*/

float PRV = 0.70; // Power Reduction Factor. Power set to 70% of MAX.


int main() {
	// Wait 2 seconds or 2000 milliseconds before starting the program.
    task::sleep(2000); 
	// Print to the screen that the program has started.	
    Brain.Screen.print("Drive Power Reducer Program has Started.");        

	/*---------- THIS PROGRAM DOES NOT USE THIS METHOD ----------*\
   	// Set the velocity of the left and right motor to 50% power. 
	// This command will not make the motor spin.
    LeftMotorFront.setVelocity(50, vex::velocityUnits::pct);
	LeftMotorBack.setVelocity(50, vex::velocityUnits::pct);
    RightMotorFront.setVelocity(50, vex::velocityUnits::pct);
	RightMotorBack.setVelocity(50, vex::velocityUnits::pct);
	/*------------------------------------------------------------*/

    while(true) {
	// Commands from Joysticks to controll motors	
    LeftMotorFront.spin(vex::directionType::fwd, Controller1.Axis3.value() *PRV, vex::velocityUnits::pct); 	// (Axis3+Axis4)/2
    LeftMotorBack.spin(vex::directionType::fwd, Controller1.Axis3.value() *PRV, vex::velocityUnits::pct); 		// (Axis3+Axis4)/2
	RightMotorFront.spin(vex::directionType::fwd, Controller1.Axis2.value() *PRV, vex::velocityUnits::pct);	// (Axis3-Axis4)/2
	RightMotorBack.spin(vex::directionType::fwd, Controller1.Axis2.value() *PRV, vex::velocityUnits::pct);		// (Axis3-Axis4)/2
	
    // Print to the brain's screen that the program has ended.
    Brain.Screen.newLine();	// Move the cursor to a new line on the screen.
    Brain.Screen.print("Drive Power Reducer Program has Ended.");

    // Prevent main from exiting with an infinite loop.
    while(1) {
      vex::task::sleep(100);	// Sleep the task for a short amount of time to prevent wasted resources.
    }
}
