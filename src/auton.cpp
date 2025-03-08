#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

//Select Auton to Run
//int autonInt = 2;

//Skills
void overClockSkills(){
    chassis.setPose(0, 0, 0);
    scoreScoring();
    pros::delay(450);
    intakeMotorVoltage = -127;

    chassis.moveToPoint(0, 10, 550, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0, 0, 0);

    chassis.swingToHeading(47, DriveSide::RIGHT, 600, {.maxSpeed = 127}, false);
    chassis.setPose(0, 0, 0);

    chassis.moveToPoint(0, 61, 1800, {.forwards = true, .maxSpeed = 100}, false);
    chassis.setPose(0, 0, 0);

    chassis.swingToHeading(57, DriveSide::RIGHT, 550, {.maxSpeed = 127}, false);
    chassis.setPose(0, 0, 0);

    chassis.moveToPoint(0, 9, 1100, {.forwards = true, .maxSpeed = 90}, false);
    chassis.setPose(0, 0, 0);

    chassis.turnToHeading( 182, 1000, {.maxSpeed = 110}, false);
    chassis.setPose(0, 0, 0);

    lift.set_value(true);
    chassis.moveToPoint(0, -6, 500, {.forwards = false, .maxSpeed = 105}, false);
    chassis.setPose(0, 0, 0);

    intakeMotorVoltage = 0;
    scoreScoring();
    pros::delay(450);
    lift.set_value(false);

    chassis.moveToPoint(0, 13.8, 800, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0, 0, 0);

    intakeMotorVoltage = -127;
    chassis.swingToHeading(121, DriveSide::RIGHT, 1000, {.maxSpeed = 127}, false);
    chassis.setPose(0, 0, 0);

    chassis.moveToPoint(0, 37.5, 1350, {.forwards = true, .maxSpeed = 70}, false);
    chassis.setPose(0, 0, 0);

    //chassis.turnToHeading(-14, 750,  {.maxSpeed = 127}, false);
    //chassis.setPose(0, 0, 0);
    //intakeMotorVoltage = 0;

    //chassis.moveToPoint(0, -95, 2500, {.forwards = false, .maxSpeed = 127}, false);
    //chassis.setPose(0, 0, 0);
    //clamp.set_value(true);

    //scoreScoring();

    /*    
    chassis.turnToHeading(90, 750,  {.maxSpeed = 100}, false);
    chassis.setPose(0,0,0);
    intakeMotorVoltage = -127;

    chassis.moveToPoint(0, 25, 1200, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0, 0, 0);    

    chassis.turnToHeading(33, 750,{.maxSpeed = 100}, false);
    chassis.setPose(0,0,0);

    chassis.moveToPoint(0, 20, 1200, {.forwards = true, .maxSpeed = 127}, false);*/
}

//Path 1
void blueNegative(){
    toggleClamp(true); //clamp goes up
    pros::delay(300);
    chassis.moveToPoint(0, 30, 1000, {.forwards = true, .maxSpeed = 100}, false); //move forward
    chassis.setPose(0,0,0);

    chassis.turnToHeading(23, 300, {.maxSpeed = 127}, false); //face the rings (mirrored angle)
    chassis.setPose(0, 0, 0);

    intakeMotorVoltage = 127;
    ringStop = true;
    chassis.moveToPoint(0, 12, 750, {.forwards = true, .maxSpeed = 100}, false); //move towards ring
    chassis.setPose(0, 0, 0);

    pros::delay(500);

    chassis.moveToPoint(0, -5, 300, {.forwards = false, .maxSpeed = 110}, false);
    chassis.setPose(0,0,0);

    chassis.turnToHeading(46, 750, {.maxSpeed = 100}, false); //mirrored angle
    chassis.setPose(0,0,0);

    chassis.moveToPoint(0, -21.5, 1000, {.forwards = false, .maxSpeed = 100}, true);
    chassis.setPose(0, 0, 0);
    pros::delay(700);
    ringStop = false;

    toggleClamp(false); //clamp down
    pros::delay(200);
    intakeMotorVoltage = 127;

    chassis.turnToHeading(22, 300, {.maxSpeed = 100}, false); //mirrored angle
    chassis.setPose(0, 0,0);

    chassis.moveToPoint(0, 31, 1000, {.forwards = true, .maxSpeed = 115}, false);
    chassis.setPose(0,0,0);

    pros::delay(600);

    chassis.turnToHeading(-84, 750, {.maxSpeed = 100}, false); //mirrored angle
    chassis.setPose(0,0,0);

    chassis.moveToPoint(0, 14.3, 1500, {.forwards = true, .maxSpeed = 100}, false);
    chassis.setPose(0,0,0);
    
    pros::delay(600);
    
    chassis.moveToPoint(-22, -43.5, 2750, {.forwards = true, .maxSpeed = 127}, false); //mirrored X-coordinate
    chassis.setPose(0,0,0);

    pros::delay(750);

    chassis.turnToHeading(130, 1000, {.maxSpeed = 100}, false); //mirrored angle
    chassis.setPose(0,0,0);
    
    chassis.moveToPoint(0, 34, 1000, {.forwards = true, .maxSpeed = 100}, false);
    chassis.setPose(0,0,0);
 
}

//Path 2
void bluePositive(){
    target = -250; //score
	pros::delay(550);
	target = 0; // pull ladybrown back
	pros::delay(550);
	toggleClamp(false);

    target = 40;
    delay(400);
    rotation.reset_position();

    chassis.turnToHeading(-75, 500, {.maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    intakeMotorVoltage = 127;
    toggleIntakePiston(true);
    chassis.moveToPoint(0, 8, 1500, {.forwards = true, .maxSpeed = 30}, false);
    ringStop = true;
    toggleIntakePiston(false);
    chassis.setPose(0,0,0);

    delay(600);

    chassis.moveToPoint(0, -3.5, 1000, {.forwards = false, .maxSpeed = 127}, false);
    chassis.setPose(0, 0,0);
    delay(300);
    ringStop = false;
    intakeMotorVoltage = 0;


    toggleClamp(true); //clamp goes up
    chassis.moveToPose(-40, 8.5, 120, 2000, {.forwards = false, .maxSpeed = 127}, false);
    chassis.setPose(0,0, 0);
    toggleClamp(false);
    delay(750);

    intakeMotorVoltage = 127;

    chassis.moveToPoint(0, 1, 300, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    chassis.turnToHeading(90, 1000, {.maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    chassis.moveToPoint(0, 22, 1000, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    pros::delay(400);

    chassis.moveToPoint(0, -30, 1500, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);


    pros::delay(1000);

    
    intakeMotorVoltage = 0;
    delay(1000);
    
    target = 40;
    delay(600);
    rotation.reset_position();
    
    //chassis.moveToPoint(0, -4, 1000, {.forwards = false, .maxSpeed = 100}, false);
    //chassis.setPose(0,0,0);
    
    //chassis.turnToHeading(70, 1000, {.maxSpeed = 100}, false);
    //chassis.setPose(0,0,0);



	//toggleClamp(true);
	//chassis.moveToPoint(0, -27, 1000, {.forwards = false, .maxSpeed = 127}, true);
	//toggleClamp(false);
	//chassis.setPose(0, 0, 0);
}

//Path 3
void redNegative(){
    toggleClamp(true); //clamp goes up
    pros::delay(300);
    chassis.moveToPoint(0, 30, 1000, {.forwards = true, .maxSpeed = 100}, false); //move forward
    chassis.setPose(0,0,0);

    chassis.turnToHeading(-23, 300, {.maxSpeed = 127}, false); //face the rings
    chassis.setPose(0, 0, 0);

    intakeMotorVoltage = 127;
    ringStop = true;
    chassis.moveToPoint(0, 12, 750, {.forwards = true, .maxSpeed = 100}, false); //move towards ring
    chassis.setPose(0, 0, 0);

    pros::delay(500);

    chassis.moveToPoint(0, -5, 300, {.forwards = false, .maxSpeed = 110}, false);
    chassis.setPose(0,0,0);

    chassis.turnToHeading(-46, 750, {.maxSpeed = 100}, false);
    chassis.setPose(0,0,0);

    chassis.moveToPoint(0, -21.5, 1000, {.forwards = false, .maxSpeed = 100}, true);
    chassis.setPose(0, 0, 0);
    pros::delay(700);
    ringStop = false;

    toggleClamp(false); //clamp down
    pros::delay(200);
    intakeMotorVoltage = 127;

    chassis.turnToHeading(-22, 300, {.maxSpeed = 100}, false);
    chassis.setPose(0, 0,0);

    chassis.moveToPoint(0, 31, 1000, {.forwards = true, .maxSpeed = 115}, false);
    chassis.setPose(0,0,0);

    pros::delay(600);

    chassis.turnToHeading(84, 750, {.maxSpeed = 100}, false);
    chassis.setPose(0,0,0);

    chassis.moveToPoint(0, 14.3, 1000, {.forwards = true, .maxSpeed = 100}, false);
    chassis.setPose(0,0,0);
    
    pros::delay(600);
    
    chassis.moveToPoint(20, -41.5, 2750, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    pros::delay(750);

    chassis.turnToHeading(-130, 1000, {.maxSpeed = 100}, false);
    chassis.setPose(0,0,0);
    
    chassis.moveToPoint(0, 34, 1000, {.forwards = true, .maxSpeed = 100}, false);
    chassis.setPose(0,0,0);



    /*
    //push rings out of the way
    chassis.moveToPoint(0, -23, 1000, {.forwards = false, .maxSpeed = 127}, false);
    chassis.setPose(0, 0,0);
    
    //move back forward in front of wall stakes
    chassis.moveToPoint(0, 7, 1000, {.forwards = false, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);
    
    //face wall stake
    chassis.turnToHeading(90, 1000, {.maxSpeed = 100}, false);
    chassis.setPose(0,0,0);

    //move clamp down so it doesnt hit the wall abd move back so you can score on wall stakes
    toggleClamp(true);
    chassis.moveToPoint(0, -9, 1000, {.forwards = false, .maxSpeed = 127}, false);
    chassis.setPose(0, 0, 0);

    //run intake and score ring
    intakeMotor.move(127);
    pros::delay(1000);
    intakeMotor.move(0);
    toggleClamp(false);

    //forward before go to mogo
    chassis.moveToPoint(0, 6, 1000, {.forwards = false, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    //move to mogo
    chassis.moveToPose(-24, 52, 180, 2500, {.forwards = false, .maxSpeed = 127}, false);
    chassis.setPose(0, 0, 0);

    //clamp mogo
    toggleClamp(true);
    pros::delay(100);
    
    //move to angle towards rings
    chassis.turnToHeading(135, 1000, {.maxSpeed = 100}, false);
    chassis.setPose(0,0, 0);
    
    //turn on intake and move forward towards rings
    run = true;
    chassis.moveToPoint(0, 22, 1000, { .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);
    
    //turn and face the rings
    chassis.turnToHeading(-45, 500, {.maxSpeed = 100}, false);
    chassis.setPose(0 ,0, 0);

    //moving forward into the rings
    chassis.moveToPoint(0, 23, 1000, {.forwards = true, .maxSpeed = 60}, false);
    chassis.setPose(0,0,0);

    chassis.moveToPoint(0, -10, 1000, {.forwards = false, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    chassis.turnToHeading(180, 500);
    chassis.setPose(0,0,0);

    //turn off intake
    pros::delay(500);
    run = false;*/
    
//CHANGE THIS TO MIRROR BLUE NEGATIVE
    /*toggleClamp(true);
    pros::delay(1000);
    chassis.turnToHeading( 45,  500); //turn 45 degrees
    //drive backwards
    //chassis.moveToPoint(-15, -15, 1000, {.forwards = false, .maxSpeed = 127}, false); //move 31 inches backwards and 31 inches right
    chassis.moveToPoint(-30, -30, 1000, {.forwards = false, .maxSpeed = 127}, false); //move 31 inches backwards and 31 inches right

    pros::delay(1000);
    toggleClamp(false);//grabs mogo
    pros::delay(1000);
    //toggleIntake(true, 40000);
    intakeMotor.move_voltage(12000);
    //chassis.moveToPose(4, 0, 45,4000); //45 degree to stack
    chassis.moveToPoint(-27.5, -27.5, 1000, {.forwards = true, .maxSpeed = 127}, false); //move 31 inches backwards and 31 inches right
    chassis.turnToHeading(90, 1000);
    chassis.moveToPoint(1, -27.5, 1000, {.forwards = true, .maxSpeed = 127}, false); //move 31 inches backwards and 31 inches right
    chassis.moveToPose(12, -41, 180, 4000);
    pros::delay(1000);
    intakeMotor.move_voltage(0);
    intakeMotor.move_voltage(-12000);
    chassis.moveToPoint(12, -41.5 , 2000);
    intakeMotor.move_voltage(0);
    chassis.moveToPoint(12, -34 , 2000);
    intakeMotor.move_voltage(12000);*/             
}

//Path 4
void redPositive(){
    target = -250; //score
	pros::delay(550);
	target = 0; // pull ladybrown back
	pros::delay(550);
	toggleClamp(false);

    target = 40;
    delay(400);
    rotation.reset_position();

    chassis.turnToHeading(75, 500, {.maxSpeed = 127}, false); // Flip turn angle
    chassis.setPose(0,0,0);

    intakeMotorVoltage = 127;
    toggleIntakePiston(true);
    chassis.moveToPoint(0, 8, 1500, {.forwards = true, .maxSpeed = 30}, false);
    ringStop = true;
    toggleIntakePiston(false);
    chassis.setPose(0,0,0);

    delay(600);

    chassis.moveToPoint(0, -3.5, 1000, {.forwards = false, .maxSpeed = 127}, false);
    chassis.setPose(0, 0,0);
    delay(300);
    ringStop = false;
    intakeMotorVoltage = 0;

    toggleClamp(true); //clamp goes up
    chassis.moveToPose(40, 8.5, -120, 2000, {.forwards = false, .maxSpeed = 127}, false); // Mirror X and adjust angle
    chassis.setPose(0,0, 0);
    toggleClamp(false);
    delay(750);

    intakeMotorVoltage = 127;

    chassis.moveToPoint(0, 3, 300, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    chassis.turnToHeading(-100, 1000, {.maxSpeed = 127}, false); // Flip turn angle
    chassis.setPose(0,0,0);

    chassis.moveToPoint(0, 22, 1000, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    pros::delay(400);

    chassis.moveToPoint(0, -30, 1500, {.forwards = true, .maxSpeed = 127}, false);
    chassis.setPose(0,0,0);

    pros::delay(1000);

    intakeMotorVoltage = 0;
    delay(1000);
    
    target = 40;
    delay(600);
    rotation.reset_position();;
}

void goForward(){
    left_motors.move(127);
    right_motors.move(127);
    pros::delay(300);
    left_motors.move(0);
    right_motors.move(0);
}

void testAuton(){
    chassis.moveToPoint(0, 20, 1000, {.forwards = true, .maxSpeed = 100}, true);
    toggleClamp(true);
    pros::delay(1000);
}