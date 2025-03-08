#include "main.h"
#include "fmt/format.h"
#include "pros/device.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.h"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"
#include <cmath>
#include <string>
#include "robodash/api.h"

using namespace std;
std::string teamColor = "blue"; // caps doesnt matter
bool autonRunning;

rd::Selector selector({
    {"Blue Pos", &bluePositive, "", 210},
    {"Blue Neg", &blueNegative, "", 210},
    {"Red Pos", &redPositive, "", 7},
    {"Red Neg", &redNegative, "", 7},
});

rd::Console console;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */



void initialize() {
    int intakeBackInt = 0;
    //scoring.set_brake_mode(MOTOR_BRAKE_HOLD);
    chassis.calibrate(); //calibrate sensors
    scoring.set_encoder_units(pros::motor_encoder_units_e_t::E_MOTOR_ENCODER_DEGREES);
    //lB.tare_position_all();
    //lB.set_brake_mode(MOTOR_BRAKE_HOLD);
    //lB.set_encoder_units_all(MOTOR_ENCODER_DEGREES);
    intakeMotor.set_brake_mode(MOTOR_BRAKE_COAST);

    rotation.reset_position();
    intakePistonDouble.set_value(true);

    autonRunning = true;

    //chassis.setPose(0, 0, 0);
    pros::delay(50);
    controller.clear();
    //pros::lcd::initialize(); //initialize brain screen
    
    optical.disable_gesture(); // Disables gesture detection on the sensor because when it is detecting gestures it cant detect color or smt
    optical.set_led_pwm(100);
    
    pros::delay(300);

    //Creating Thread
    // print position to brain screen
    pros::Task screenTask([&]() {
        while (false) {
            // print robot location to the brain screen
            //pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            //pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            //pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
            
        }
    });

    pros::Task scoringPIDTask([&]() {
        while (true) {
            if(true){
                float power1 = ladyBrownPID.update(scoringTarget - scoring.get_position());
                scoring.move(power1);
                pros::delay(5);
            }
        }
    });


    bool toggleScoring = true;
    bool scoringOff = false;
    std::string scoringState = "";
    
    pros::Task toggleScoringTask([&]() {
        while (true) {
            bool isL2pressed = controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2);
        
            if(isL2pressed){
                scoreScoring();
            }
        }
    });

    pros::Task intakeTask([&]() {
        while (true) {
			intakeMotor.move(intakeMotorVoltage);
			pros::delay(20);
        }
    });

    /*
    pros::Task colorSensingTask([&]() {
        while (false) {
            double hue = optical.get_hue();
            double prox = optical.get_proximity();

            if(colorSensorOn){
                if (teamColor == "red" && optical.get_proximity() > 200) {
                    if(hue > 5 && hue < 10){
                        //controller.set_text(0, 0, "Detected Red");
                    }else{
                        ejectRing();
                    }
                }else if(teamColor == "blue" && optical.get_proximity() > 200){
                    if(hue > 215 && hue < 225){  

                    }else {
                        //controller.set_text(1, 0, "Ejecting");
                        //ejectRing();
                    }
                }

                double prox = optical.get_proximity();
                controller.set_text(0,0, "H:" + to_string((int)hue) + " P: " + to_string((int)optical.get_proximity()));
                //pros::lcd::set_text(3, "Not Ejecting Ring");
            }

            //controller.set_text(1, 0, "Hue: " + fmt::to_string(hue));
            //controller.set_text(1, 0, "Prox: " + fmt::to_string(optical.get_proximity()));


            if(ringStop){
                if ((hue > 2 && hue < 16) || (hue > 200 && hue < 230)) {
                    intakeMotorVoltage = 0;
                }
            }

            if(LBState == "SCORING" && intakeBackInt == 0){
                    intakeBackInt = 1;
                    intakeMotorVoltage = -127;
                    delay(100);
                    intakeMotorVoltage = 0;
            }

            //controller.clear_line(0);
		    pros::delay(5);
            //pros::lcd::set_text(4, "Position: " + to_string(intakeMotor.get_position()));
        }
    });*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    //selector.focus();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous(){
    overClockSkills();
    //selector.run_auton();
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    autonRunning = false;
    intakeMotorVoltage = 0;
    //colorSensorOn = true;
    target = 0;
    while (true){
        drive();
        toggleClamp();
        toggleSlapper();
        controllerPrint();
        runIntake();
        toggleLift();
        //controller.set_text(0,0, "I POS: " + fmt::to_string(intakeMotor.get_position()));
        //controller.set_text(0, 0,"Target: " + to_string(target));
        pros::delay(20);
    }
}