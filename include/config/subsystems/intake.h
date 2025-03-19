#pragma once


#include "hardware.h"
#include "match.h"
#include "tunables.h"

bool antiJamActive = true;
bool colorSortingOn = true;

pros::Task* intakeTask = nullptr;

enum struct intakeState{
    INTAKE_FAST = 127,
    INTAKE_SLOW = 40,
    OUTTAKE_FAST = -127,
    OUTTAKE_SLOW = -40,
    COAST = 0
};


bool isWrongColorRingDetected(){
    //is red detected
    if(actualMatchColor != matchColor::RED){
        if(colorSensorTop.get_hue()<27){
			return true;
		} else {
			return false;
			}
    }

    //is blue detected
    if(actualMatchColor != matchColor::BLUE){
        if(colorSensorTop.get_hue()<150){
			return true;
		} else {
			return false;
			}
    }

}

bool holdOnToRing(){
    //is red detected
    if(actualMatchColor == matchColor::RED){
        if(colorSensorTop.get_hue()<27){
			return true;
		} else {
			return false;
			}
    }

    //is blue detected
    if(actualMatchColor == matchColor::BLUE){
        if(colorSensorTop.get_hue()<150){
			return true;
		} else {
			return false;
			}
    }
}

bool antiJamStarted = false;
uint32_t startTime;
bool antiJam(intakeState intakeSpeed){
    
    double currentIntaking = double(intakeSpeed);
    if(intake.get_actual_velocity() == 0 && currentIntaking != 0 && !antiJamStarted){
        //
        antiJamStarted = true;
        startTime = pros::millis();
        return false;
    }
    else if(!(intake.get_actual_velocity() == 0 && currentIntaking != 0) && antiJamStarted){
        antiJamStarted = false;
        return false;
    } 
    else if(intake.get_actual_velocity() == 0 && currentIntaking != 0 && (pros::millis() - startTime)>1500){
        return true;
        antiJamStarted = false;
    }
    else{
        return false;
    }
}

extern void intakeThreadF(intakeState intakeSpeed, bool holdOn, bool triggerAntiJam){
    bool downPressed;
    while(true){
        //if auton
        if(COMPETITION_AUTONOMOUS){
            //get current intake speed
            double currIntakeSpeed = double(intakeSpeed);

            //if wrong color detected
            if(isWrongColorRingDetected){
                intake.move(-127);
                pros::delay(20);
                intake.move(currIntakeSpeed);
            }

            //hold on to ring
            if(holdOn){
                if(holdOnToRing){
                    intake.move(0);
                } 
            } else{
                intake.move(currIntakeSpeed);
            }

            //anti jam
            if(triggerAntiJam){
                //if jammed and no wrong ring in conveyor
                if(antiJam(intakeSpeed) && !isWrongColorRingDetected){
                    pros::delay(1500);
                    if(intake.get_torque()>1.0){
                        intake.move(-127);
                        pros::delay(150);
                    }
                    intake.move(currIntakeSpeed);
                } 

                //if jammed and wrong ring in conveyor
                else if(antiJam(intakeSpeed) && isWrongColorRingDetected){
                    pros::delay(1500);
                    if(intake.get_torque()>1.0){
                        intake.move(-127);
                        pros::delay(150);
                    }
                    intake.move(currIntakeSpeed);
                    pros::delay(1500);
                    intake.move(-127);
                    pros::delay(150);
                    intake.move(currIntakeSpeed);
                }

            } else{
                intake.move(currIntakeSpeed);
            }
        }

        //if driver
        else{
            //get current intake speed
            double currIntakeSpeed = double(intakeSpeed);

            //if wrong color detected
            if(isWrongColorRingDetected){
                intake.move(-127);
            } 

            //otherwise if jam
            else if((intake.get_target_velocity() != 0 && intake.get_actual_velocity() == 0) && intake.get_torque() >= 0.92){
		            intake.move(-127);
		            pros::delay(50);
            }

            //intake controls
            else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)){
		        intake.move(-127);
	        }
	        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
		        intake.move(127);
	        } 
            else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
                intake.move(127);
            
            } 
            else if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)){
                downPressed = !downPressed;
                if(downPressed){
                
            
            } else{
                intake.move(0);
            }

            

        }
        
        
        //save resources
        pros::delay(UTIL_TIME);
    }
}}
