//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// hal.cpp - Hardware Abstraction layer, abstacts motors & sensors into 
//	         a set of accessor functions
//
//////////////////////////////////////////////////////////////////////////////////////////////////////


#include "vex.h"
using namespace vex;


/* Slight crinkle in HAL philosophy, in case where more advanced motor 
	algorithmns are being applied */
#include "lib/motor.cpp"
#include "lib/pid.cpp"
#include "lib/profile.cpp"


//////////////////////////////////
//
// --- Section 1: Drive ---
//
//////////////////////////////////

void drive(double left, int right) {
  LeftSide.setVelocity(left, velocityUnits::rpm);
  RightSide.setVelocity(right, velocityUnits::rpm);
}

void driveReset() {
  LeftSide.resetPosition();
  RightSide.resetPosition();
}

int driveOffset() {
  return fabs(LBmotor.position(rotationUnits::raw) - RBmotor.position(rotationUnits::raw) );
}

void driveHandle() {
    motorTarget[port4] = -robot.leftDrive;
    motorTarget[port6] = -robot.leftDrive;

    motorTarget[port5] = robot.rightDrive;
    motorTarget[port7] = robot.rightDrive;
}


////////////////////////////////////////////////
//
//  Drives a set number of specified inches
//
////////////////////////////////////////////////

void driveDistance(int inches) {
    robot.driveDirect = true;
    driveReset();

    // Calculate the movement
    int targetTicks = inches;
    int deceleratePeriod = clamp(targetTicks / 2, 0, 800);
    targetTicks -= deceleratePeriod;
    int startTicks  = LBmotor.position(rotationUnits::raw);

    while(targetTicks - LBmotor.position(rotationUnits::raw) > 50) 
	{
        drive(100, 100);
    }

    // Stop the drive after we've completed the distance
    drive(0, 0);
    robot.driveDirect = false;
}


//////////////////////////////////////
//
// Turns a set number of degrees
//
/////////////////////////////////////
 
int rotationTicks() {
    return sin(LBmotor.position(rotationUnits::raw)) * (abs(SensorValue[leftDrive]) + abs(SensorValue[rightDrive])) / 2;
}


/////////////////////////////////////////////////////////////
//
// Turns a specified number of rotations
// float rotations The number of rotations to turn
//
////////////////////////////////////////////////////////////
 

void turn(float rotations) {
    driveReset();
    int targetTicks = 440 * rotations;
    int out;

    while (abs(rotationTicks()) < abs(targetTicks)) {
        out = profile(PROFILE_TRAPEZOID, 30, 60, 0, targetTicks, rotationTicks());
        drive(out, -out);
    }
    drive(0, 0);
}


////////////////////////////////////////////////
//
// --- Section 2: Tray Lift ---
//
////////////////////////////////////////////////

void traySet(double velocity) {
    TrayLiftmotor::setVelocity(double velocity, velocityUnits::rpm)
}


void trayHandle() {
    if(robot.tray == UP && SensorValue[trayLeft] > 600) {
        traySet(100);
        robot.trayMoving = true;
    } else if (robot.tray == DOWN && SensorValue[trayLeft] < 2450) {
        traySet(-100);
        robot.trayMoving = true;
    } else {
        traySet(0);
        robot.trayMoving = false;
    }
}

void untilTrayDone() {
    while(robot.trayMoving) {};
    return;
}


void trayUp() {
    robot.tray = UP;
    robot.trayMoving = true;
    untilTrayDone();
}
void trayDown() {
    robot.tray = DOWN;
    robot.trayMoving = true;
    untiltrayDone();
}

////////////////////////////////////////////////
//
// --- Handle All Call ---
//
////////////////////////////////////////////////
task handleAll() {
    while(true) {
        trayHandle();
        driveHandle();
        motorHandle();
        task::sleep( 100 );
    }
}
