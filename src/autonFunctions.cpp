#include "functions.hpp"
#include "globals.hpp"
#include "main.h"
#include "pros/rtos.hpp"

void straight(double tiles){
    pidDriveStraight(fabs(tiles)*3800, 1, tiles/fabs(tiles), getCurrentAngle(), 1);
}

void turn(int degrees){
    pidTurn(degrees, 1);
}

void spinRoller(bool blue, int bailTime){
    opticalSensor.set_led_pwm(100);
    setIntakeRoller(-150);
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
	straight(0.9);
    straight(-0.2);
	turn(90);
	straight(-0.9);
    spinRoller(true,4000);
    catapult.tare_position();
    cycleCata(2000);
    straight(1.9);
 	turn(0);
    straight(-0.9);
    while(true){
        int time = pros::millis();
        while(pros::millis()-time<5000){
            setIntakeRoller(-200);
        }
        setIntakeRoller(0);
        straight(0.9);
        turn(90);
        catapult.tare_position();
        cycleCata(2100);
        pros::delay(1500);
        turn(0);
        straight(-0.9);
    }
}