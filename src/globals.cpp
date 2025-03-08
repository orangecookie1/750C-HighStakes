#include "lemlib/chassis/trackingWheel.hpp"
#include "main.h"
#include "pros/abstract_motor.hpp"
#include "pros/adi.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

//Other
pros::Imu imu(18);
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//Optical Sensor
pros::Optical optical(0);

//Intake Motors
pros::Motor intakeMotor(10);

//Rotation
pros::Rotation rotation(0);

//Scoring moter
pros::Motor scoring(20);

//Scoring PID
lemlib::PID scoringPID(1.3, 0, .5, 0, true);

//Pid
lemlib::PID ladyBrownPID(1.3, 0, .5, 0, true);
bool runPIDLoop = true;
int intakeMotorVoltage = 0;
bool ringStop = false;

int scoringMotorVoltage = 0;


pros::MotorGroup lB({0, 0});

//Pistons
pros::adi::DigitalOut clamp('H'); //proper way to create a solenoid
pros::adi::DigitalOut intakePiston('E');
pros::adi::DigitalOut intakePistonDouble('F');
pros::adi::DigitalOut slapper('D');
pros::adi::DigitalOut lift('A');

//Drive Motors
pros::MotorGroup left_motors({-19, -6, -1}, pros::MotorGearset::blue); // front, bottom, stack
pros::MotorGroup right_motors({2, 11, 5}, pros::MotorGearset::blue); // front, bottom, stack

//LemLib Stuff
lemlib::Drivetrain drivetrain(&left_motors, // left motor group
                              &right_motors, // right motor group
                              12.5, // 12.5 inch track width
                              lemlib::Omniwheel::NEW_275, 
                              450, 
                              2 // horizontal drift is 2 (for now)
);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);


//11 3
// lateral PID controller
lemlib::ControllerSettings lateral_controller(10.8, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              4, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

//4 27
// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              12.7, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors);