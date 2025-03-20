#include "autoScripts.h"

void goalRushRedPosSetup(){
    chassis.setPose(0,0,0);
    chassis.turnToHeading(-20, 3000);
}


void redRushPos(){
    chassis.setPose(0,0,-20);

    pros::Task runLift([=](){
        while(abs(10000 - ladyBrownRot.get_position()) > 1){
            double output = liftPID->update(10000 - ladyBrownRot.get_position());
            ladyBrown.move(output);
            pros::delay(20);
        }
    });
    chassis.moveToPoint(-12, 32, 3000, {.forwards = true, .minSpeed = 127});
    chassis.waitUntil(3);
    intake.move(127);
    exit_condition(lemlib::Pose(-8,31),1.5);
    arm.set_value(1);
    chassis.moveToPoint(-11, 17, 3000, {.forwards = false});
    chassis.waitUntil(10);
    intake.move(15);
    chassis.waitUntilDone();
    arm.set_value(0);
    chassis.turnToHeading(180, 600);
    chassis.moveToPoint(-3, 45, 5000, {.forwards = false});
    exit_condition(lemlib::Pose(-3,45),1);
    clamp.set_value(1);
    pros::delay(20);
    chassis.moveToPoint(-30, 15, 4000, {.forwards = true, .maxSpeed = 100});
    chassis.waitUntil(4);
    intake.move(127);
    exit_condition(lemlib::Pose(-30,15),1);
    chassis.turnToHeading(0, 700);
    chassis.waitUntilDone();
    clamp.set_value(0);
    intake.move(0);
    chassis.turnToHeading(190, 800);
    chassis.moveToPose(-39, 30, 170, 2000, {.forwards = false,.lead = 0.2,  .maxSpeed = 90});
    exit_condition(lemlib::Pose(-39,30),1);
    clamp.set_value(1);
    pros::delay(20);
    chassis.moveToPoint(-6, 15, 4000, {.forwards = true, .maxSpeed = 100});
    chassis.waitUntil(4);
    intake.move(-127);
    exit_condition(lemlib::Pose(-6,15),1);
    chassis.moveToPoint(-7, 0, 6000, {.forwards = true, .maxSpeed = 100});
    chassis.turnToHeading(135, 600);
    intake.move(127);
    chassis.moveToPoint(10, -10, 1600, {.forwards = true, .maxSpeed = 100});
    chassis.moveToPoint(-8, 20, 1500, {.forwards = false, .maxSpeed = 100});
    exit_condition(lemlib::Pose(-8,20),1);
    chassis.turnToHeading(10, 600);
    chassis.moveToPose(1, 45, 45, 3000, {.forwards = true, .lead = 0.2, .maxSpeed = 100});
    chassis.waitUntil(30);
    pros::Task runLift2([=](){
        while(abs(60000 - ladyBrownRot.get_position()) > 1){
            double output = liftPID->update(60000 - ladyBrownRot.get_position());
            ladyBrown.move(output);
            pros::delay(20);
        }
    });
}