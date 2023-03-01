#include "main.h"
#include "functions.hpp"
#include "globals.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include <string>

// initialization code -- resets catapult, inertial sensor/drive encoders
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
	resetInertialSensor();
	resetDriveEncoders();
}

void disabled() {}

void competition_initialize() {
}

// autonomous code -- this is where we will run/call our different autonomous programs
void autonomous() {
	// straight(1);
	// skillsAuton();
	// justFarRollerAuton(false);
	farRollerFullAuton(false);
}

// drive controls -- controls drivetrain/intake-roller mechanism/expansion and holds catapult until button A triggers the catapult to cycle
void opcontrol() {
	bool released = true; 
	int cataPhase = 1;
	while (true) {
		setDriveMotors();
		setIntakeRollerMotors();
		if(cataPhase==1){
			cycleCata(-1000);
			// controller.set_text(0, 0, std::to_string(catapult.get_position()));
			if(catapult.get_position()<-3300){
				catapult.tare_position();
				cataPhase = 2;
			}
		}else{
			cycleCata(2100);
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)==1 && released){
			catapult.tare_position();
			released = !released;
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)==0 && !released){
			released = !released;
		}
		expansionOn();
		pros::delay(20);
	}
}
