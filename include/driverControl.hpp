#include <string>
extern bool toggleIntake1;
extern bool toggleClamp1;
extern bool toggleIntake2;
extern bool colorSensorOn;
extern bool run;
extern float target;
extern int scoringTarget;

void toggleClamp();
void toggleHang();
void toggleSlapper();
void intakeThread();
void controllerPrint();
void intakeAuton();
void drive();
void runIntake();
void toggleLift();
void scoreScoring();