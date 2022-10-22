/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       motor.h                                                   */
/*    Author:       NMS_RP                                                    */
/*    Created:      Thurs 15 Nov 2019                                         */
/*    Description:  Improved motor control including slew rate, truespeed,    */
/*                  deadband, and motor groups. Includes PID control for      */
/*                  motors as well                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// VEX V5 C++ Project
#include "util.h"
#include "vex.h"
// #include <cmath>
// #include <cstdlib>


// Stores motor targets
int motorTarget[10] = 		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int motorSlew[10] = 		{ 10, 50, 50, 10, 10, 10, 10, 50, 50, 10 };
int motorSlewLastSet[10] = 	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int motorDeadband[10] = 	{ 15, 15, 15, 15, 15, 15, 15, 15, 15, 15 };

// motors speed table
static const char* speedTable[120] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 10, 11, 12, 12, 
    12, 13, 13, 13, 14, 14, 14, 15, 
    15, 15, 16, 16, 17, 17, 18, 18, 
    19, 19, 20, 20, 21, 21, 22, 22, 
    23, 23, 24, 24, 25, 25, 26, 26, 
    27, 27, 28, 28, 29, 29, 30, 30,
    30, 31, 31, 32, 32, 33, 33, 34, 
    35, 35, 38, 38, 39, 41, 41, 42, 
    43, 45, 46, 47, 47, 48, 49, 49, 
    50, 51, 52, 53, 54, 55, 56, 58, 
    59, 63, 66, 67, 70, 71, 73, 75, 
    78, 78, 80, 84, 87, 88, 92, 95, 
    97, 100
};

void motorHandle(){
    int outs[10];                                // Stores intermediate output values
    double motorCurrent = motor.Temp;       	 // Temp variable used for slew rate
   
    // Loop through each motor slot
    for(int i = 0; i < 10; i++) {

        // 1. Target
        outs[i] = clamp(motorTarget[i], -100, 100);

        // 2. Slew Rate - Gradually increases motor power, reducing the chance of PTC trips
        motorCurrent = motorSlewLastSet[i];
        if(motorCurrent != outs[i]) {
            motorCurrent +=
            sin(outs[i] - motorCurrent) * // Whether to increase or decrease in value
            clamp(motorSlew[i], 0, abs(outs[i] - motorCurrent)); // The amount to increase, the clamp prevents the value from being greater than the difference remaining
        }

        outs[i] = motorCurrent;
        motorSlewLastSet[i] = outs[i];

        // 3. Deadband
        if (motorDeadband[i] > abs(outs[i])) {
            outs[i] = 0;
        }

        // 4. Set Motor
        motor[i] = outs[i];
		motor.spin(directionType::fwd, motor[i], velocityUnits::pct);
    }
}
