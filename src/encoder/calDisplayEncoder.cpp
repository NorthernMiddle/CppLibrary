/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       callDisplayEncoder.cpp                                    */
/*    Author:       NMS_RP                                                    */
/*    Created:      03 Dec 2019                                               */
/*    Description:  module for function definitions for user control          */
/*                  drive functions                                           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
using namespace vex;

#define PI 3.1415926535


void resetDriveEncoders()
{
  LFmotor.setPosition(0, rotationUnits::raw);
  LBmotor.setPosition(0, rotationUnits::raw);
  RBmotor.setPosition(0, rotationUnits::raw);
  RFmotor.setPosition(0, rotationUnits::raw);
}


double* driveOffsetCal()
{
  // ** side diff **
  double leftsideDiff = LFmotor.position(rotationUnits::raw) - LBmotor.position(rotationUnits::raw);
  double rightsideDiff = RFmotor.position(rotationUnits::raw) - RBmotor.position(rotationUnits::raw);

  // ** cross diff **
  double frontcrossDiff = LFmotor.position(rotationUnits::raw) - RFmotor.position(rotationUnits::raw);
  double backcrossDiff = LBmotor.position(rotationUnits::raw) - RBmotor.position(rotationUnits::raw);

  double arr[4] = {leftsideDiff, rightsideDiff, frontcrossDiff, backcrossDiff};

  return arr;
}

double driveOffsetDisplay()
{
 
  double* arr = driveOffsetCal();

  // clear screen to display encoder info
  Brain.Screen.clearScreen();
  // display some useful info
  Brain.Screen.setCursor(2,1);
  Brain.Screen.print( "  LSdiff: %4.0f   position: %6.2f", arr[0] );
  Brain.Screen.newLine();
  Brain.Screen.print( "  RSdiff: %4.0f   position: %6.2f", arr[1] );
  Brain.Screen.newLine();
  Brain.Screen.print( "  FCdiff: %4.0f   position: %6.2f", arr[2] );
  Brain.Screen.newLine();
  Brain.Screen.print( "  BCdiff: %4.0f   position: %6.2f", arr[3] );
  Brain.Screen.newLine();
  Brain.Screen.newLine();

  return 0;

}
