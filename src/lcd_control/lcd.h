/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       lcd.h                                                     */
/*    Author:       NMS_RP                                                    */
/*    Created:      Mon 18 Nov 2019                                           */
/*    Description:  LCD Program Selection Library                             */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// VEX V5 C++ Project
#include "vex.h"
using namespace vex;

// clear V5 LCD
void lcdClear() {
  Brain.Screen.clearScreen();
}


/**
 * Holds the code for autonomous selection, etc.
 * Run in pre_auton();
 */
 /*
void robotConfigure() {
    displayLCDCenteredString(0, "Match Type");
    string matchTypes[] = { "Standard", "Driver", "Prog", "Rerun" };
    match.type = lcdMenu(1, matchTypes, 4);
    wait1Msec(500);
    if (match.type == 0) {
        displayLCDCenteredString(0, "Alliance");
        match.alliance = lcdPick(1, "Red", "Blue");
        wait1Msec(500);
    }
    displayLCDCenteredString(0, "Routine");
    // Menu Tree based on Match Type
    switch(match.type) {
        case 0:
            match.routine = lcdMenu(1, autonRoutines, arraySize(autonRoutines));
            break;
        case 2:
            match.routine = lcdMenu(1, skillsRoutines, arraySize(skillsRoutines));
            break;
        default: break;
    }
}
*/
