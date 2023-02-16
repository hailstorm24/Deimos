#pragma once
#include "main.h"

// This is a file where I declare the global functions that I make

// drive control functions
void setDriveMotors();
void setIntakeRollerMotors();

//all drive functions
void setDrive(int leftPower,int rightPower);
void setIntakeRoller(int power);
void cycleCata(int distance);

// pid, inertial-sensor, and other functions
void pidDriveStraight(int distance, int distanceTolerance, int direction, int angle, int angleTolerance);
void pidTurn(int angle, int angleTolerance, int direction);

// pid/inertial-sensor helper functions
int getCurrentAngle();
void resetInertialSensor();
int getCurrentDistance();
void resetDriveEncoders();
double averageLeftDriveEncoders();
double averageRightDriveEncoders();