#include "fmt/format.h"
#include "liblvgl/llemu.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include <cstddef>
#include <string>
#include <algorithm>  

bool toggleIntake1 = false;
bool toggleClamp1 = true;
bool toggleIntake2 = false;
bool toggleSlapper1 = false;
bool colorSensorOn = false;
bool toggleLift1 = false;

std::string LBState = "";
int scoringTarget = 0; 
float target = 0;

bool toggleScoring = true;
bool scoringOff = false;
std::string scoringState = "";

void runIntake(){
    bool isR1pressed = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1);
    bool isR2pressed = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2);
    if(isR1pressed){
        toggleIntake1 = !toggleIntake1;
    }
    if(isR2pressed){
        toggleIntake2 = !toggleIntake2;
    }

    if(toggleIntake1 && !toggleIntake2){
        intakeMotorVoltage = -127;
        //intakeMotor.move(127);
    }else if(toggleIntake1 && toggleIntake2){
        //reverse intake
        intakeMotorVoltage = 127;
    }else{
            intakeMotorVoltage = 0;
    }
}


void toggleLift(){
    bool isApressed = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A);
    if(isApressed){
        toggleLift1 = !toggleLift1;
    }
    lift.set_value(toggleLift1);
}

void scoreScoring(){
    scoringTarget = -3000;
    pros::delay(550);
    scoringTarget = 0;
}

void toggleClamp(){
    bool isL1pressed = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1);
    if(isL1pressed){
        toggleClamp1 = !toggleClamp1;
    }
    clamp.set_value(toggleClamp1);
}   

void toggleSlapper(){
    bool isYpressed = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y);
    if(isYpressed){
        toggleSlapper1 = !toggleSlapper1;
    }
    slapper.set_value(toggleSlapper1);
}

void drive(){
    //sanjit is tank
    // Drive sanjit's controls rn, arcade is normal driving
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    chassis.arcade(leftY, rightX);
}

std::string clampValue = "";

void controllerPrint()
{
    if (std::to_string(toggleClamp1) == "0") {
        clampValue = "Down";
    } else {
        clampValue = "Up";
    }
    controller.set_text(0, 0, "C: " + clampValue);
}