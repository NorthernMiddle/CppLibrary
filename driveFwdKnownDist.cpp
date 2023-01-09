/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       LoJac10                                                   */
/*    Created:      Wed Sep 25 2019                                           */
/*    Description:  Moving Forward (inches)                                   */
/*                                                                            */
/*    This program drives the robot forward for 6 inches. Additionally this   */
/*    program will print smartmotor encoder info to brain screen and a        */
/*    *.dat file on your computer.                                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 2, 19, 20 
// lfMotor              smartmotor    1
// lbMotor              smartmotor    2
// rfMotor              smartmotor    19
// rbMotor              smartmotor    20
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

double leftsideDiff,
       rightsideDiff,
       frontcrossDiff,
       backcrossDiff;

// declare array
double arr[4];

// declare pointer
double *ptr;







// declare pointer and set array to pointer
double *ptr = arr;

void resetDriveEncoders()
{
  // left motors
  lfMotor.setPosition(0, rotationUnits::raw);
  lbMotor.setPosition(0, rotationUnits::raw);

  // right motors
  rfMotor.setPosition(0, rotationUnits::raw);
  rbMotor.setPosition(0, rotationUnits::raw);
  
}

double driveOffsetCal()
{
  // ** side diff **
  arr[0] = lfMotor.position(rotationUnits::raw) - lbMotor.position(rotationUnits::raw);
  arr[1] = rfMotor.position(rotationUnits::raw) - rbMotor.position(rotationUnits::raw);

  // ** cross diff **
  arr[2] = lfMotor.position(rotationUnits::raw) - rfMotor.position(rotationUnits::raw);
  arr[3] = lbMotor.position(rotationUnits::raw) - rbMotor.position(rotationUnits::raw);
}


int driveOffsetDisplay( )
{

  // open 'output.dat' file to write to on computer
  std::ofstream output;
  output.open("output.dat");

  // clear screen to display encoder info
  Brain.Screen.clearScreen();

  // display some useful info on screen
  Brain.Screen.setCursor(2,1);

  // left-side encoder difference
  Brain.Screen.print( "  LSdiff: %4.0f", ptr[0] );
  Brain.Screen.newLine();
  std::cout << "LSdiff: " << ptr[0] << std::endl;
  
  // right-side encoder difference
  Brain.Screen.print( "  RSdiff: %4.0f", ptr[1] );
  Brain.Screen.newLine();
  std::cout << "RSdiff: " << ptr[1] << std::endl;
  
  // front motors encoder difference
  Brain.Screen.print( "  FCdiff: %4.0f", ptr[2] );
  Brain.Screen.newLine();
  std::cout << "FCdiff: " << ptr[2] << std::endl;

  // back motors encoder difference
  Brain.Screen.print( "  BCdiff: %4.0f", ptr[3] );    // print to brain
  Brain.Screen.newLine();                             
  std::cout << "BCdiff: " << ptr[3] << std::endl;     // print  to terminal

  Brain.Screen.newLine();

  // writes info to 'output.dat'
  output << "LeftSidediff: " << ptr[0] << std::endl;
  output << "RightSidediff: " << ptr[1] << std::endl;
  output << "FrontCrossdiff: " << ptr[2] << std::endl;
  output << "BackCrossdiff: " << ptr[3] << std::endl;

  // close 'output.dat' file
  output.close();

  // exit code
  return 0;

}


////////////////////////
//
// MAIN
//
/////////////////////////////////////////////////

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  resetDriveEncoders();
  driveOffsetDisplay( );
  Drivetrain.driveFor(forward, 6, inches);
  
  return 0;
}
