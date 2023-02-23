#include "functions.hpp"
#include "globals.hpp"
#include "main.h"

void straight(double tiles){
    pidDriveStraight(fabs(tiles)*3500, 1, tiles/fabs(tiles), 0, 1);
}

void turn(int degrees){
    pidTurn(degrees, 1);
}

void spinRoller(bool blue, int bailTime){
    opticalSensor.set_led_pwm(50);
    setIntakeRoller(-100);
    double startTime = pros::millis();
    if(!blue){
        while(int(opticalSensor.get_hue()) % 300 <=60 && (pros::millis()-startTime)<bailTime){ // while the sensor sees red (and the bail time hasn't been reached)
            pros::delay(100);
        }
    }
    else{
        while(fabs(opticalSensor.get_hue()-200)<60 && (pros::millis()-startTime)<bailTime){ // while the sensor sees blue (and the bail time hasn't been reached)
            pros::delay(100);
        }
    }
    controller.set_text(0, 0, std::to_string((int)opticalSensor.get_hue()));
    setIntakeRoller(0);
}

void skillsAuton(){
    // straight(-0.1);
	// spinRoller(true,1000);
	straight(3);
	// turn(-90);
	// straight(1);
}