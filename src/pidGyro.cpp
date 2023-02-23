#include "functions.hpp"
#include "globals.hpp"
#include "main.h"
#include <string>

// this function uses a PID and inertial-sensor to travel a given distance with a set tolerance, direction, and target angle / angle tolerance.
void pidDriveStraight(int distance, double distanceTolerance, int direction, int angle, double angleTolerance) {

  // start timer


  int timeOut = pros::millis() + 1000 + 1200*(distance/3800);

// sets the weights for the proportional, integral, and derivative PID actions based on the ultimate gain and period
  const double kU = 775000;
  const double tU = 250;

  // const double kP = 0.6*kU;
  // const double kI = 1.2*kU/tU;
  // const double kD = 0.075*kU*tU;

  const double kP = 0.325;
  const double kI = 0.00020;
  const double kD = 0.3;

  const double akP = 10;
  const double akI = 0.0025;
  const double akD = 0.7;


  // resets drive encoders, sets all variables to zero
  resetDriveEncoders();
  double distanceIntegral = 0.0;
  double distanceDerivative = 0.0;
  double distanceError = 0.0;
  double distancePrevError = 0.0;

  double angleIntegral = 0.0;
  double angleDerivative = 0.0;
  double angleError = 0.0;
  double anglePrevError = 0.0;

  bool targetReached = false;

  while (!targetReached && pros::millis()<timeOut) {

    // compare the distance measured through motor encoder units to the target distance. 
    int currentDistance = getCurrentDistance();
    distanceError = distance - currentDistance;

    // compare the angle measured through the inertial sensor to the target angle
    int currentAngle = getCurrentAngle();
    angleError = angle - currentAngle;

    // compute the integrals and derivatives for the distances and angle
    distanceIntegral += distanceError;
    if(distanceError > 1000.0){
      distanceIntegral = 0;
    }
    distanceDerivative = distanceError - distancePrevError;
    distancePrevError = distanceError;

    angleIntegral += angleError;
    if(angleError > 1000.0){
      angleIntegral = 0;
    }
    angleDerivative = angleError - anglePrevError;
    anglePrevError = angleError;

    // using the predefined weights and established values for the three PID actions, calculate the necessary speed and angle adjustment
    int motorSpeed = kP * distanceError + kI * distanceIntegral + kD * distanceDerivative;
    int angleAdjustment = akP * angleError + akI * angleIntegral + akD * angleDerivative;

    // power the drivetrain accordingly
    setDrive((direction*motorSpeed)+angleAdjustment,(direction*motorSpeed)-angleAdjustment);
    pros::delay(10);

    // check to see if the target has been reached and break if this is the case
    if (fabs(distanceError) < distanceTolerance && fabs(angleError) < angleTolerance) {
        targetReached = true;
        setDrive(0,0);
    }

  }
setDrive(0,0);
}

// this function uses a PID to turn in a direction to a target angle with a given angle tolerance.
void pidTurn(int angle, double angleTolerance) {

  // sets the weights for the proportional, integral, and derivative PID actions

  const double kP = 4;
  const double kI = 0.00025;
  const double kD = 0.035;

  //   const double kP = 0.6*kU;
  // const double kI = 1.2*kU/tU;
  // const double kD = 0.075*kU*tU;

  // sets all variables to zero
  double angleIntegral = 0.0;
  double angleDerivative = 0.0;
  double angleError = 0.0;
  double anglePrevError = 0.0;

  bool targetReached = false;

  int timeOut = pros::millis() + 2000;

  while (!targetReached && pros::millis()<timeOut) {

    // compare the angle measured through the inertial sensor to the target angle
    int currentAngle = getCurrentAngle();
    angleError = angle - currentAngle;

    // compute the integrals and derivatives for the angle
    angleIntegral += angleError;
    angleDerivative = angleError - anglePrevError;
    anglePrevError = angleError;
    controller.set_text(0, 0, std::to_string(currentAngle));

    // using the predefined weights and established values for the three PID actions, calculate the necessary motor speed adjustments
    int angleAdjustment = kP * angleError + kI * angleIntegral + kD * angleDerivative;
    
    // power the drivetrain accordingly
    setDrive(angleAdjustment, -angleAdjustment);
    pros::delay(10);

    // check to see if the target has been reached and break if this is the case
    if (fabs(angleError) < angleTolerance) {
        targetReached = true;
        setDrive(0,0);
    }
    
  }
  setDrive(0,0);
}

// this function returns the angle measured by the inertial sensor
int getCurrentAngle(){
    // controller.set_text(0, 0, std::to_string((int)inertialSensor.get_rotation()%360));
    return((int)inertialSensor.get_rotation()%360);
}

// this function resets and recallibrates the inertial sensor
void resetInertialSensor(){
    inertialSensor.reset();
    while (inertialSensor.is_calibrating()) {
    	pros::delay(10);
	}
}

// this function returns the distance measured through motor encoder units
int getCurrentDistance() {
    return((int)(averageLeftDriveEncoders()+averageRightDriveEncoders())/2);
}

// this function resets the drivetrain motor encoder units
void resetDriveEncoders(){
  driveLeftFront.tare_position();
  driveLeftMiddle.tare_position();
  driveLeftBack.tare_position();
  driveRightFront.tare_position();
  driveRightMiddle.tare_position();
  driveRightBack.tare_position();
}

// this function returns the average of the left drivetrain motor encoder units
double averageLeftDriveEncoders(){
  return (fabs(driveLeftFront.get_position())+
  fabs (driveLeftBack.get_position())+
  fabs (driveLeftMiddle.get_position())) / 3;
}

// this function returns the average of the right drivetrain motor encoder units
double averageRightDriveEncoders(){
  return (fabs (driveRightMiddle.get_position())+
  fabs (driveRightFront.get_position())+
  fabs (driveRightBack.get_position())) / 3;
}
