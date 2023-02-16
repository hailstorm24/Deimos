#include "main.h"
/*this file is where I am setting all of the physical components as variables.
All of these variables are global variables, meaning, I can refrence them
anywhere in the code.*/

//CONTROLLER
pros::Controller controller(pros::E_CONTROLLER_MASTER);

//DRIVETRAIN
pros::Motor driveLeftBack(17, pros::E_MOTOR_GEARSET_18,true, pros::E_MOTOR_ENCODER_COUNTS); //
pros::Motor driveLeftMiddle(16, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_COUNTS); //
pros::Motor driveLeftFront(15, pros::E_MOTOR_GEARSET_18,true, pros::E_MOTOR_ENCODER_COUNTS); //
pros::Motor driveRightBack(14, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightMiddle(19, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);
pros::Motor driveRightFront(18, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_COUNTS);

// CATAPULT
pros::Motor catapult(12, pros::E_MOTOR_GEARSET_18,true, pros::E_MOTOR_ENCODER_COUNTS);

// INTAKE
pros::Motor intake(11, pros::E_MOTOR_GEARSET_18,true, pros::E_MOTOR_ENCODER_COUNTS);

//INERTIAL SENSOR
pros::Imu inertialSensor(1);