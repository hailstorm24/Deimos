#include "main.h"
#include "functions.hpp"
#include "globals.hpp"
#include "pros/misc.h"

// initialization code -- sets catapult, resets inertial sensor/drive encoders
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	resetInertialSensor();
	resetDriveEncoders();
	catapult.tare_position();
}

void disabled() {}

void competition_initialize() {
}

// autonomous code -- this is where we will run/call our different autonomous programs
void autonomous() {
	// straight(1);
	skillsAuton();
}

// drive controls -- controls drivetrain/intake-roller mechanism/expansion and holds catapult until button A triggers the catapult to cycle
void opcontrol() {
	bool released = true; 
	bool firstSet = true;
	while (true) {
		setDriveMotors();
		setIntakeRollerMotors();
		if(firstSet){
			cycleCata(2400);
		}else{
			cycleCata(2100);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)==1 && released){
			catapult.tare_position();
			firstSet = false;
			released = !released;
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)==0 && !released){
			released = !released;
		}
		expansionOn();
		pros::delay(20);
	}
}
