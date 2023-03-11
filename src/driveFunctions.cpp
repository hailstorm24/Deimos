#include "main.h"
#include "globals.hpp"
#include "pros/imu.h"
#include "pros/screen.h"
#include <string>
#include "display/lv_objx/lv_btnm.h"
#include "pros/misc.h"

#define DIGITAL_SENSOR_PORT_A 4
#define DIGITAL_SENSOR_PORT_B 3
#define DIGITAL_SENSOR_PORT_C 2
#define DIGITAL_SENSOR_PORT_D 5

pros::ADIDigitalOut expansionA (DIGITAL_SENSOR_PORT_A);
pros::ADIDigitalOut expansionB (DIGITAL_SENSOR_PORT_B);
pros::ADIDigitalOut expansionC (DIGITAL_SENSOR_PORT_C);
pros::ADIDigitalOut expansionD (DIGITAL_SENSOR_PORT_D);



// drive code -- powers the drivetrain based on the x-axis of the right joystick and y-axis of the left joystick
void setDriveMotors(){
   int rightJoystickX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
   int leftJoystickY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);

   int leftPower = leftJoystickY+rightJoystickX;
   int rightPower = leftJoystickY-rightJoystickX;

   setDrive(leftPower, rightPower);
}

// sets left drivetrain motors to leftPower and right drivetrain motors to rightPower
void setDrive(int leftPower,int rightPower){
  driveLeftFront = leftPower;
  driveLeftMiddle = leftPower;
  driveLeftBack = leftPower;
  driveRightFront = rightPower;
  driveRightMiddle = rightPower;
  driveRightBack = rightPower;
}

// triggers expansion pneumatics if the X button is pressed
void expansionOn(){
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){ // &&pros::millis()>51000){
        shootExpansion();
    }
}

void shootExpansion(){
    expansionC.set_value(true);
    expansionD.set_value(true);
    pros::delay(250);
    expansionA.set_value(true);
    expansionB.set_value(true);

}
// powers the intake/roller based on the states of buttons R1 and R2
void setIntakeRollerMotors(){
    int intakeOn = 200 * (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) - controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2));
    setIntakeRoller(intakeOn);
 }

// sets the intake/roller to a given power
void setIntakeRoller(int power){
    intake = power;
}

// moves the catapult a given number of degrees
void cycleCata(int degrees){
    catapult.move_absolute(5*degrees,6000);
}