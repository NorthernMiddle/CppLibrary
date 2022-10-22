/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       rerun.h                                                   */
/*    Author:       NMS_RP                                                    */
/*    Created:      Mon 18 Nov 2019                                           */
/*    Description:  Super basic rerun system, warning: NOT GENERALIZED ;-)    */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
// VEX V5 C++ Project
#include "util.h"
struct matchState{
  int type;         // 0 = standard, 1 = driver, 2 = programming, 3 = record rerun
  int routine;      // See /routines
	int alliance;     // 0 = red, 1 = blue
};
matchState match;
enum trayState {
    UP, DOWN
};
struct robotState{
    trayState tray;
    int leftDrive;
    int rightDrive;
};
robotState robot;
*/

/**
 * Update robot state based on controller values
 */
 /*
void updateState() {
    if (vexRT[Btn6U] || nLCDButtons == kButtonLeft) robot.mogo = UP;
    if (vexRT[Btn6D] || nLCDButtons == kButtonRight) robot.mogo = DOWN;
    int forward = abs(vexRT[Ch3]) > 25 ? vexRT[Ch3] : 0;
    int turn = abs(vexRT[Ch4]) > 25 ? vexRT[Ch4] : 0;
    // Ch3 is direction, Ch4 is turn
    robot.leftDrive = clamp(forward, -100, 100);
    robot.rightDrive = clamp(forward, -100, 100);
}
*/

/**
 * State Codes
 * Short, textual representations of the robot's state. They take the form:
 * <mogoLift>:<leftDrive>:<rightDrive>
 * Examples:
 *   0:127:-127
 *   0:0:0
 */

/*
void outputStateCode() {
    string out;
    sprintf(out, "%d:%d:%d", robot.mogo == UP ? 0 : 1, robot.leftDrive, robot.rightDrive);
    displayLCDString(1, 0, out);
}
void activateStateCode(char * code) {
    char state[STRTOK_MAX_TOKEN_SIZE];
    char * ptr = &state;
    char * sep = ":";
    while (true) {
        if (!strtok(code, ptr, sep)) break;
    }
    robot.mogo = state[0] == 0 ? UP : DOWN;
    robot.leftDrive = (int) state[1];
    robot.rightDrive = (int) state[2];
}
*/
