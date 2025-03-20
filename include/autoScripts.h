#pragma once

#include "api.h"
#include "config/hardware.h"
#include "config/dt.h"
#include "lemlib/timer.hpp"

inline void exit_condition(lemlib::Pose targetPose, double exitDist){
    double wait_until = chassis.getPose().distance(targetPose);
    chassis.waitUntil(wait_until - exitDist);
    chassis.cancelMotion();
}

extern void blue1_6neg();
extern void red1_6neg();
extern void blue1_6negAWP();
extern void red1_6negAWP();
extern void redRushPos();
extern void blueRushPos();
extern void redSAWP();
extern void blueSAWP();
extern void skills();

extern bool intakeSlow;