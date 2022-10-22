/**
 * --- hal.cpp ---
 * Module: Hardware Abstraction Layer
 * Description: abstacts motors & sensors into a set of accessor functions
 * Author: Brandon McGuire aka "Mayor Monty"
 *
 * @TODO: clean up
 * @TODO: convert from *.c to *.cpp
 *
 */

// Slight crinkle in HAL philosophy, in case where more advanced motor algorithmns are being applied
#include "motor.cpp"
#include "util.cpp"
#include "pid.cpp"
#include "profile.cpp"

// -----------------------------------------------------------------------------
/* Section 1: Drive */
void drive(int left, int right) {
    robot.leftDrive = left;
    robot.rightDrive = right;
}

void driveReset() {
    SensorValue[leftDrive] = 0;
    SensorValue[rightDrive] = 0;
}

int driveOffset() {
    return SensorValue[leftDrive] - SensorValue[rightDrive];
}

void driveHandle() {
    motorTarget[port4] = -robot.leftDrive;
    motorTarget[port6] = -robot.leftDrive;
    motorTarget[port8] = -robot.leftDrive;

    motorTarget[port5] = robot.rightDrive;
    motorTarget[port7] = robot.rightDrive;
    motorTarget[port9] = robot.rightDrive;
}

/**
 * Drives a set number of specified inches
 */
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
// -----------------------------------------------------------------------------
/* Section 2: Cube Tray Lift */
void traySet(int value) {
    motorTarget[port8] = value;
}

void trayHandle() {
    if(robot.tray == UP && SensorValue[trayMotor] > 150) {
       traySet(127);
    } else if (robot.tray == DOWN && SensorValue[trayMotor] < 2400) {
        traySet(-127);
    } else {
        traySet(0);
    }
}

void trayUp() {
    robot.tray = UP;
}
void trayDown() {
    robot.tray = DOWN;
}

// -----------------------------------------------------------------------------
task handleAll() {
    while(true) {
        trayHandle();
        driveHandle();
        motorHandle();
        wait1Msec(20);
    }
}
