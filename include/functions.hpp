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
void expansionOn();

// autons

void skillsAuton();

// auton functions
void straight(double tiles);
void turn(int degrees);
void spinRoller(bool blue, int bailTime);

// pid, inertial-sensor, and other functions
void pidDriveStraight(int distance, double distanceTolerance, int direction, int angle, double angleTolerance);
void pidTurn(int angle, double angleTolerance);

// pid/inertial-sensor helper functions
int getCurrentAngle();
void resetInertialSensor();
int getCurrentDistance();
void resetDriveEncoders();
double averageLeftDriveEncoders();
double averageRightDriveEncoders();