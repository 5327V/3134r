#pragma once

#include "hardware.h"
#include "match.h"
#include "tunables.h"

pros::Task* neutralTask = nullptr;

enum struct neutralTargets{
    REST = 0,
    LIFT_HEIGHT = LB_PRIME_STATE,
    HOVER = LB_HOVER_STATE,
    SCORE = LB_SCORE_STATE,
    DESCORE = LB_ALLIANCE_STATE,
    TWORING = 1000,
};

double lbTarget = 0;
double liftMaxSpeedSet = 127;

bool disableControl;

inline void setLiftTarget(neutralTargets liftTarget, double speed){
    disableControl = false;
    lbTarget = double(liftTarget);
    liftMaxSpeedSet = speed;

}

inline void disableLiftControl(bool disable){
    disableControl = disable;
}

inline void resetLift(double position){
    ladyBrownRot.reset_position();
    ladyBrownRot.set_position(position);
    liftPID->reset();
}

inline void liftTaskF(){
    bool isDPressed;
    while(true){

        double error = lbTarget - ((ladyBrownRot.get_position()/100) * (36/24));
        double power = liftPID->update(error);

        //driver
        if(!COMPETITION_AUTONOMOUS){
            if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
                setLiftTarget(neutralTargets::LIFT_HEIGHT, 127);
            } 
            
            else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
                setLiftTarget(neutralTargets::REST, 127);
            
            } 
            
            else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)){
                isDPressed = !isDPressed;
                if(isDPressed){
                    setLiftTarget(neutralTargets::DESCORE, 127);
                } else{
                    setLiftTarget(neutralTargets::HOVER, 127);
                }
            } 
            
            else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)){
                setLiftTarget(neutralTargets::DESCORE, 127);
            } 
            
            else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)){
                disableControl = true;
                ladyBrown.move(127);
            }

            else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)){
                disableControl = true;
                ladyBrown.move(-127);
            }

            else {
	            ladyBrown.move(0);
            }



            //add macro for 2 ring


            if(!disableControl){
                ladyBrown.move(power);
            }
        }
        pros::delay(UTIL_TIME);
    }
    
}