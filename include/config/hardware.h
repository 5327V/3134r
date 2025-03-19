#pragma once

#include "api.h"

#define motor pros::Motor
#define optical pros::Optical
#define piston pros::adi::DigitalOut


inline pros::Controller master(pros::E_CONTROLLER_MASTER);

//misc. hardware objects
std::vector<int> vMotorPorts = {
    8, // intake
    4, // neutral
    9, // Optical Bottom
    2, //Optical Top
    -17}; // Lady Brown Rotation Sensor

std::vector<char> pneumaticPorts = {
    'D', // hang
    'H', // clamp
    'F', // pistake
    'B', //doinker
    'G'}; //rush


//hardware
extern motor intake(vMotorPorts[0]); //intake
extern motor ladyBrown(vMotorPorts[1]); //neutral
extern optical colorSensorBottom(vMotorPorts[2]); //optical bottom
extern optical colorSensorTop(vMotorPorts[3]); //optical top
pros::Rotation ladyBrownRot(vMotorPorts[4]);

// Pneumatics
extern piston hang(pneumaticPorts[0]);
extern piston clamp(pneumaticPorts[1]);
extern piston pistonLift(pneumaticPorts[2]);
extern piston arm(pneumaticPorts[3]);
extern piston rushMech(pneumaticPorts[4]);
