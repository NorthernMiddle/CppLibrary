#include "vex.h"
#include "controls.h"
#include "drivePower.cpp"
using namespace vex;

// Set voltage <-- power setting for drive
// drivePower.cpp

int mode = 0;
int deadband = 8; // Deadband stops the motors when Axis values are close to zero.

void tank() {
  int l_joy = abs(Controller1.Axis3.value()) > deadband ? Controller1.Axis3.value() : 0;
  int r_joy = abs(Controller1.Axis2.value()) > deadband ? Controller1.Axis2.value() : 0;
  set_tank(l_joy, r_joy);
}

void arcade() {
    int fwd = ((std::abs(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) * master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) / 127) * 100;
    int turn = ((std::abs(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) * master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) / 127) * 100;
    left_side.move(fwd + turn);
    right_side.move(fwd - turn);
}

void controls() {
    while(1) {
        if (mode == 0) {
            tank();
        } else if (mode == 1) {
            arcade();
        }
        if (Controller1.ButtonL1.pressing()) {
            mode = 0;
        } else if (Controller1.ButtonL2.pressing()) {
            mode = 1;
        }

        wait(20, msec); // Sleep the task for a short amount of time to
                        // prevent wasted resources.
    }
}
