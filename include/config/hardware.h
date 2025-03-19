#pragma once

#include "api.h"

#define motor pros::Motor
#define optical pros::Optical
#define piston pros::adi::DigitalOut


inline pros::Controller master(pros::E_CONTROLLER_MASTER);

//misc. hardware objects
inline std::vector<int> vMotorPorts = {
    8, // intake
    4, // neutral
    9, // Optical Bottom
    2, //Optical Top
    -17}; // Lady Brown Rotation Sensor

inline std::vector<char> pneumaticPorts = {
    'D', // hang
    'H', // clamp
    'F', // pistake
    'B', //doinker
    'G'}; //rush


//hardware
inline motor intake(vMotorPorts[0]); //intake
inline motor ladyBrown(vMotorPorts[1]); //neutral
inline optical colorSensorBottom(vMotorPorts[2]); //optical bottom
inline optical colorSensorTop(vMotorPorts[3]); //optical top
inline pros::Rotation ladyBrownRot(vMotorPorts[4]);

// Pneumatics
inline piston hang(pneumaticPorts[0]);
inline  piston clamp(pneumaticPorts[1]);
inline piston pistonLift(pneumaticPorts[2]);
inline piston arm(pneumaticPorts[3]);
inline piston rushMech(pneumaticPorts[4]);
