#include "functions.hpp"
#include "globals.hpp"
#include "main.h"

void straight(double tiles){
    pidDriveStraight(fabs(tiles)*3800, 1, tiles/fabs(tiles), getCurrentAngle(), 1);
}

void turn(int degrees){
    pidTurn(degrees, 1);
}

void spinRoller(bool blue, int bailTime){
    opticalSensor.set_led_pwm(100);
    setIntakeRoller(-200);
    double startTime = pros::millis();
    if(!blue){
        while(abs(opticalSensor.get_hue()-200)>60 && (pros::millis()-startTime)<bailTime){ // while the sensor sees red (and the bail time hasn't been reached)
            pros::delay(100);
        }
    }
    else{
        while(int(opticalSensor.get_hue()) % 300 >60 && (pros::millis()-startTime)<bailTime){ // while the sensor sees blue (and the bail time hasn't been reached)
            pros::delay(100);
        }
    }
    controller.set_text(0, 0, std::to_string((int)opticalSensor.get_hue()));
    setIntakeRoller(0);
}

void skillsAuton(){
    straight(-0.1);
	spinRoller(true,4000);
	straight(0.7);
	turn(90);
	straight(-1.25);
    spinRoller(true,4000);
}