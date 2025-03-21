#include "autoScripts.h"

void blueRushPosSetup(){
    chassis.setPose(0,0, -90);
    chassis.turnToHeading(-110, 150000);
}
void blueRushPos(){
    chassis.setPose(0,0,-20);
    pros::Task runLift([=](){
        while(abs(10000 - ladyBrownRot.get_position()) > 1){
            double output = liftPID->update(10000 - ladyBrownRot.get_position());
            ladyBrown.move(output);
            pros::delay(20);
        }
    });
    //..grab goal
    chassis.moveToPoint(-10, 36, 3000, {.forwards = true, .minSpeed = 127});
    chassis.waitUntil(3);
    intake.move(127);
    exit_condition(lemlib::Pose(-10,36),1.5);
    arm.set_value(1);

    //..drag back
    chassis.moveToPoint(-7, 11, 3000, {.forwards = false});
    chassis.waitUntil(10);
    intake.move(15);
    arm.set_value(0);

    //turn and grab goal
    chassis.turnToHeading(180, 600);
    chassis.moveToPoint(-10, 30, 5000, {.forwards = false});
    exit_condition(lemlib::Pose(-10,30),1);
    clamp.set_value(1);
    pros::delay(20);

    //intake and depo to area
    chassis.moveToPoint(0, 15, 4000, {.forwards = true, .maxSpeed = 100});
    chassis.waitUntil(4);
    intake.move(127);
    exit_condition(lemlib::Pose(0,15),1);
    chassis.turnToHeading(0, 700);
    chassis.waitUntilDone();
    clamp.set_value(0);
    intake.move(0);
    chassis.turnToHeading(-170, 800);

    //grab second goal
    chassis.moveToPose(8, 17, -160, 2000, {.forwards = false,.lead = 0.2,  .maxSpeed = 90});
    exit_condition(lemlib::Pose(8,17),1);
    clamp.set_value(1);
    pros::delay(20);

}