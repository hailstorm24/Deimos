#include "main.h"
#include "functions.hpp"
#include "globals.hpp"
#include "pros/misc.h"

// initialization code -- sets catapult, resets inertial sensor/drive encoders
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	catapult.move_absolute(5*39,-6000);
	catapult.tare_position();
	resetInertialSensor();
	resetDriveEncoders();
}

void disabled() {}

void competition_initialize() {
}

// autonomous code -- this is where we will run/call our different autonomous programs
void autonomous() {
	pidDriveStraight(1000, 1, 1, 0, 1);
	pidTurn(90, 1, -1);
}

// drive controls -- controls drivetrain/intake-roller mechanism and holds catapult until button A triggers the catapult to cycle
void opcontrol() {
	bool released = true; 
	while (true) {
		setDriveMotors();
		setIntakeRollerMotors();
		cycleCata(500);
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)==1 && released){
			catapult.tare_position();
			released = !released;
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)==0 && !released){
			released = !released;
		}
		pros::delay(20);
	}
}
