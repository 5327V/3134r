#pragma once

#include "intake.h"
#include "ladybrown.h"
#include "dt.h"

//create new thread instance
extern void runSubSystemsTasksF(intakeState intakeSpeed, bool holdOn, bool triggerAntiJam){
    //calibrate chassis
    chassis.calibrate();
    
    //remove current intake task
    intakeTask = nullptr;
    intakeTask->remove();

    //if removed, run a new intake instance
    if(intakeTask == nullptr){
        intakeTask = new pros::Task([=]{
            
            intakeThreadF(intakeSpeed, holdOn, triggerAntiJam);
            
            
        });
    }

    //if removed, run a new neutral instance
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	ladyBrownRot.reset();
	ladyBrownRot.reset_position();
	ladyBrownRot.set_position(0);
    colorSensorBottom.set_led_pwm(100);
	colorSensorTop.set_led_pwm(100);

    if(neutralTask == nullptr){
        neutralTask = new pros::Task([=]{
            


        });
    }
}