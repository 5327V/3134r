#pragma once

#include "intake.h"
#include "ladybrown.h"
#include "../dt.h"

//create new thread instance
inline void runSubSystemsTasksF(){
    //calibrate chassis
    chassis.calibrate();


    //if removed, run a new neutral instance
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	ladyBrownRot.reset();
	ladyBrownRot.reset_position();
	ladyBrownRot.set_position(0);
    colorSensorBottom.set_led_pwm(100);
	colorSensorTop.set_led_pwm(100);

    if(neutralTask == nullptr){
        neutralTask = new pros::Task([=]{
            
            liftTaskF();


        });
    }
}