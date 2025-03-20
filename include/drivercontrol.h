#pragma once

#include "api.h"
#include "config/hardware.h"
#include "config/dt.h"

inline void controllerControl() {
	int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    chassis.tank(left, right);
}

bool pistonControlFlag = false;
inline void pistonLiftControl() {
	if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)){
		pistonControlFlag = !pistonControlFlag;
		if(pistonControlFlag){
			pistonLift.set_value(false);
	    } else {
			pistonLift.set_value(true);
		}
	}
}

bool clampControlFlag = false;
inline void clampControl() {
	if(master.get_digital(pros::E_CONTROLLER_DIGITAL_Y)){
		clamp.set_value(false);
	} else{
			clamp.set_value(true);
	}

}

bool clawControlFlag = false;
inline void clawControl() {
	if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
		clawControlFlag = !clawControlFlag;
		if(clawControlFlag){
			hang.set_value(true);
	    } else {
			hang.set_value(false);
		}
	}
}

bool armControlFlag = false;
inline void armControl() {
	if(master.get_digital(pros::E_CONTROLLER_DIGITAL_B)){
		arm.set_value(true);
	} else{
			arm.set_value(false);
	}
}

inline void driverControl(){
    while(true){
        armControl();
        clawControl();
        clampControl();
        pistonLiftControl();
        controllerControl();
        
        pros::delay(10);
    }
}

