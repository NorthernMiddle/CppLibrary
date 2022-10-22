/**
 * --- state.cpp ---- 
 *
 * adapted from Brandon McGuire aka "Mayor Monty"
 */

// ---------------------------------------------------------------------------------------

struct matchState{
	int type;	// 0 = standard, 1 = driver, 2 = programming, 3 = record rerun
	int routine;	// See /routines
	int alliance;	// 0 = red, 1 = blue
} match;

// ---------------------------------------------------------------------------------------

enum trayState{
	UP, DOWN
};

// ---------------------------------------------------------------------------------------

struct robotState{
    mogoState mogo;
    int leftDrive;
    int rightDrive;
    bool driveDirect; 	// In autonomous, we would likely want to forgo slew rate, motion profiling will take care of its role

    bool trayMoving;
    bool driveMoving;

    int debugDisplay; 	// Refer to debugValues() task for more information
} robot;
