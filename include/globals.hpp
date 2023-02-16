#pragma once
#include "main.h"
// This file is where I declare all of the variables I define in globals.

//CONTROLLER
extern pros::Controller controller;


//DRIVETRAIN
extern pros::Motor driveLeftBack;
extern pros::Motor driveLeftMiddle;
extern pros::Motor driveLeftFront;
extern pros::Motor driveRightBack;
extern pros::Motor driveRightMiddle;
extern pros::Motor driveRightFront;

//CATAPULT
extern pros::Motor catapult;

//INTAKE-ROLLER
extern pros::Motor intake;

//SENSORS
extern pros::Imu inertialSensor;
