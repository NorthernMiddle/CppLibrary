/**
 * shooter.cpp - some program to control flywheel
 * aurthor: NMS_RP
 * origin forked: steve1442
 * 2022-23 VRC "Spin-Up"
 *
 *
 * @TODO: Rework for game 
 * @TODO: convert from PROS
 * @TODO: 
 */

#include "main.h"

bool backshot = false;

//IMPORTANT VARIABLES
bool flywheelToggle = true;
int flywheelSpeed = 127;

int targetVel = 600, fwError, tbh, previousFwError;
float gain = 0.008;
float output = 118;
bool firstCross = true;

//CONTROL FUNCTIONS
void setFlywheel(int voltage) {
  flywheelTop = voltage;
  flywheelBottom = voltage;
}

void setFlywheelSpeed(int voltage) {
  flywheelSpeed = voltage;
  setFlywheel(voltage);
}

int getFlywheelSpeed() {
  return flywheelSpeed;
}

bool getFlywheelStatus() {
  return flywheelToggle;
}

float avgFlywheelEnc() {
  return (fabs(flywheelTop.get_actual_velocity()) + fabs(flywheelBottom.get_actual_velocity())) / 2;
}

void tbhTest() {
  fwError = targetVel - avgFlywheelEnc();
  output += gain * fwError;
  if(abs(fwError) / fwError != abs(previousFwError) / previousFwError) {
    if(firstCross) {
      output = 118;
      firstCross = false;
    }
    else {
      output = (tbh + output) / 2;
      tbh = output;
   }
  }
  output = output > 127 ? 127 : output;
  previousFwError = fwError;
  setFlywheel(output);
  pros::lcd::set_text(5, "front tbh engaged");
}

void backtbhTest() {
  fwError = 535 - avgFlywheelEnc();
  output += 0.005 * fwError;
  if(abs(fwError) / fwError != abs(previousFwError) / previousFwError) {
    if(firstCross) {
      output = 108;
      firstCross = false;
    }
    else {
      output = (tbh + output) / 2;
      tbh = output;
   }
  }
  output = output > 127 ? 127 : output;
  previousFwError = fwError;
  setFlywheel(output);
  pros::lcd::set_text(5, "back tbh engaged");
}

 //AUTONOMOUS FUNCTIONS

 //USER CONTROL FUNCTIONS

 void assignFlywheel() {
   if(controllerDigital(FLYWHEEL_TOGGLE_BUTTON)) {
     flywheelToggle = !flywheelToggle;
     while(controllerDigital(FLYWHEEL_TOGGLE_BUTTON)) {
       assignDrive();
       assignScraper();
       pros::delay(20);
     }
   }
   else if(controllerDigital(pros::E_CONTROLLER_DIGITAL_Y)) {
     backshot = !backshot;
     firstCross = true;
     flywheelSpeed = (flywheelSpeed == 127 ? 100 : 127);
     if(flywheelSpeed != 127)
           tbh = 117;
     //setFlywheel(flywheelToggle ? flywheelSpeed : 0);
     while(controllerDigital(pros::E_CONTROLLER_DIGITAL_Y)) {
       assignDrive();
       assignScraper();
       pros::delay(20);
     }
   }



   if(flywheelToggle && flywheelSpeed != 127) {
     backtbhTest();
   }
   else if(flywheelToggle && flywheelSpeed == 127){
     if(!doubleShotting){

       int error = 600 - avgFlywheelEnc();
       setFlywheel(120 + (error * 0.5) );

     }
     //tbhTest();
   }
   else
    setFlywheel(0);
 }

 int autonError = 0;
 int autonpwm = 0;
 float autonkp = 0.5;
// 580 115
 void sniperAutonReg(void * ignore) {
    /*int autoTargetVel = 630, autoFwError, autoTbh, autoPreviousFwError;
    float autoGain = 0.1; //0.1;
    float autoOutput = 127;
    bool autoFirstCross = true;
*/
    while(true) {
      if(!doubleShotting){
        /*
      autoFwError = autoTargetVel - avgFlywheelEnc();
      autoOutput += autoGain * autoFwError;
      if(abs(autoFwError) / autoFwError != abs(autoPreviousFwError) / autoPreviousFwError) {
        if(autoFirstCross) {
          autoOutput = 118;
          autoFirstCross = false;
        }
        else {
          autoOutput = (autoTbh + autoOutput) / 2;
          autoTbh = autoOutput;
        }
      }
      autoOutput = autoOutput > 127 ? 127 : autoOutput;
      autoPreviousFwError = autoFwError;
      setFlywheel(autoOutput);
      */
      int error = autonError - avgFlywheelEnc();
      setFlywheel(autonpwm + (error * autonkp) );
      }
      pros::delay(20);
    }
  }
