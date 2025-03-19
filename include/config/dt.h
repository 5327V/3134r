#pragma once

#include "lemlib/api.hpp"
#include "tunables.h"
#include "api.h"

#define motorGroup pros::MotorGroup
#define rot pros::Rotation
#define inertial pros::Imu

// dt hardware objects
std::vector<int8_t> odomAccessories = {
    -15, -12, -19, // left motors
    13,  6,   16, // right motors
    -11, // vertical tracker wheel
    21, // horizontal tracker wheel
    3, // imu
};

// dt motors
motorGroup leftMotors({odomAccessories[0], odomAccessories[1], odomAccessories[2]}, pros::MotorGearset::blue);
motorGroup rightMotors({odomAccessories[3], odomAccessories[4], odomAccessories[5]}, pros::MotorGearset::blue);

// imu
inertial imu(odomAccessories[8]);

//vertical tracker
rot verticalEnc(odomAccessories[6]);
lemlib::TrackingWheel vertical(&verticalEnc, lemlib::Omniwheel::NEW_275, 0);

//horizontal tracker
rot horizontalEnc(odomAccessories[7]);
lemlib::TrackingWheel horizontal(&horizontalEnc, lemlib::Omniwheel::NEW_275, -2.32);

//---

//overall dt setup

lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.5, // 10 inch track width
                              lemlib::Omniwheel::NEW_325, // using new 4" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

lemlib::OdomSensors sensors(&vertical, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.026 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.026 // expo curve gain
);

// create the chassis
extern lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);