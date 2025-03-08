#include "main.h"
#include "pros/rtos.hpp"

void toggleClamp(bool toggle){
    clamp.set_value(toggle);
}

void toggleIntakePiston(bool toggle){
    intakePiston.set_value(toggle);
}

void toggleIntake(bool toggle){

}