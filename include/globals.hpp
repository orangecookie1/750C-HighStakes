#include "lemlib/api.hpp" 
#include "lemlib/pid.hpp"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
#include "pros/rtos.hpp"


extern int scoringMotorVoltage;

//Other
extern pros::Imu imu;
extern pros::Controller controller;
extern pros::Task intakeTask;

//Sensors
extern pros::Optical optical;
extern pros::Rotation rotation;

//Intake Motor
extern pros::Motor intakeMotor;

//Scoring Mech
extern pros::Motor scoring;

//ladybrown
extern pros::MotorGroup lB;
extern bool runPIDLoop;
extern int intakeMotorVoltage;
extern bool ringStop;

//Pneumatics
extern pros::adi::DigitalOut intakePiston;
extern pros::adi::DigitalOut intakePistonDouble;
extern pros::adi::DigitalOut clamp;
extern pros::adi::DigitalOut slapper;
extern pros::adi::DigitalOut lift;

//Drive Motors
extern pros::MotorGroup left_motors;
extern pros::MotorGroup right_motors;

//LemLib Stuff
extern lemlib::Drivetrain drivetrain; 
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis;

//Custom PID stuff
extern lemlib::PID ladyBrownPID;