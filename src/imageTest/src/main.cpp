/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\reece.turner                                     */
/*    Created:      Wed Jan 15 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

void lcdStartup();

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  lcdStartup();
  
}

void lcdStartup() 
{
  /* replace “myimage.bmp” with the name of you image file on the SD card.
     make sure the image is less than 480 x 272 (although it will still be cropped to 240 pixels height)
     so if you image is called “sahil.png” and fills the screen use */
  int count = 0;
  while(count < 30)
  {
	  Brain.Screen.drawImageFromFile( "V5_Pirate.png", 0, 0 );
    count = count + 1;
  }

  Brain.Screen.clearScreen();
  // lcdClear();
}