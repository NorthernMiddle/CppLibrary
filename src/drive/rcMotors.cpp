#include "robot-config.h"
using namespace vex;

/* module to drive motors based on pre-set values
   selected by rc button press */

//rc_motors_rev.cpp

int main() {
  //Set the font size for the screen
  Brain.Screen.setFont(mono30);

  //Create variables to store motor encoder revolutions
  float rightRevs = 0.0;
  float leftRevs = 0.0;

  //Set the default velocity for motors and reset motor encoders
  rightMotor.setVelocity(60, vex::velocityUnits::pct);
  leftMotor.setVelocity(60, vex::velocityUnits::pct);
  rightMotor.resetRotation();
  leftMotor.resetRotation();

  //Drive the robot based on the directional buttons
  while(true){
    if(Controller.ButtonUp.pressing()){
      rightMotor.spin(directionType::fwd);
      leftMotor.spin(directionType::fwd);
    }
    else if(Controller.ButtonDown.pressing()){
      rightMotor.spin(directionType::rev);
      leftMotor.spin(directionType::rev);
    }
    else if(Controller.ButtonRight.pressing()){
      rightMotor.spin(directionType::rev);
      leftMotor.spin(directionType::fwd);
    }
    else if(Controller.ButtonLeft.pressing()){
      rightMotor.spin(directionType::fwd);
      leftMotor.spin(directionType::rev);
    }
    else{
      rightMotor.stop();
      leftMotor.stop();
    }

    //If Button A is pressed, reset the motor encoders to 0
    if(Controller.ButtonA.pressing()){
      rightMotor.resetRotation();
      leftMotor.resetRotation();
    }

    //Set Variables equal to current encoder readings
    rightRevs = rightMotor.rotation(rotationUnits::rev);
    leftRevs = leftMotor.rotation(rotationUnits::rev);

    //Display updated variables to the LCD
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(50,50,"Right Motor Revolutions:");
    Brain.Screen.printAt(50,75,"%.2f", rightRevs);
    Brain.Screen.printAt(50,125,"Left Motor Revolutions:");
    Brain.Screen.printAt(50,150,"%.2f", leftRevs);

    task::sleep(50);
  }

  return 0;
}
