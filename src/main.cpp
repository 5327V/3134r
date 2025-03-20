#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep


void initialize() {
    runSubSystemsTasksF();
}

void disabled() {}


void competition_initialize() {}



void autonomous() {
   
}

/**
 * Runs in driver control
 */
void opcontrol() {
   driverControl();
}
