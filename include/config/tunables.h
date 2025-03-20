#pragma once

#include "lemlib/api.hpp"

//delay times
#define UTIL_TIME 20
//ring hue colors
#define RED_HUE 27
#define BLUE_HUE 150

//lb
#define LB_PRIME_STATE 4250
#define LB_HOVER_STATE 12000
#define LB_SCORE_STATE 25000
#define LB_ALLIANCE_STATE 60000


// lateral motion controller
inline lemlib::ControllerSettings linearController(12, // proportional gain (kP)
                                            0, // integral gain (kI)
                                            75, // derivative gain (kD)
                                            3, // anti windup
                                            1, // small error range, in inches
                                            100, // small error range timeout, in milliseconds
                                            3, // large error range, in inches
                                            500, // large error range timeout, in milliseconds
                                            0 // maximum acceleration (slew)
);

// angular motion controller
inline lemlib::ControllerSettings angularController(6, // proportional gain (kP)
                                             0, // integral gain (kI)
                                             26, // derivative gain (kD)
                                             3, // anti windup
                                             1, // small error range, in degrees
                                             100, // small error range timeout, in milliseconds
                                             3, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
);

inline lemlib::PID* liftPID = new lemlib::PID(1, // kP
        0.004, // kI
        3, // kD
        7, // integral anti windup range
        false);
