#pragma config(Sensor, port3, touchLED, sensorVexIQ_LED)
#pragma config(Sensor, port7, gyroSensor, sensorVexIQ_Gyro)
#pragma config(Sensor, port8, colorSensor, sensorVexIQ_ColorHue)
#pragma config(Sensor, port12, MColorSensor, sensorVexIQ_ColorGrayscale)
#pragma config(Motor, motor1, leftMotor, tmotorVexIQ, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor, motor4, sideWays, tmotorVexIQ, openLoop, encoder)
#pragma config(Motor, motor5, storageMotor, tmotorVexIQ, openLoop, encoder)
#pragma config(Motor, motor6, rightMotor, tmotorVexIQ, PIDControl, driveRight, encoder)
#pragma config(Motor, motor10, vaccum, tmotorVexIQ, openLoop, encoder)
#pragma config(Motor, motor11, stickMotor, tmotorVexIQ, openLoop, reversed, encoder)
//!!Code automatically generated by 'ROBOTC' configuration wizard !!//

/**


REPLACE ALL MOVEMOTORS/FORWARDS/BACKWARDS WITH PID CONTROLS



**/


/**

Bus Stops
1 ~ Stack Breaker on Middle of Blue Ring (Arin)
**/

#include "autosorting.h";
#include "huntersPID.h" ;

void TurnRight90Degrees(){
	setMotor(leftMotor, 20);
	setMotor(rightMotor, -20);
	waitUntil(getGyroDegrees(gyroSensor) == -90 );
	stopMultipleMotors(leftMotor, rightMotor);
}

void TurnLeft90Degrees(){
	setMotor(leftMotor, -20);
	setMotor(rightMotor, 20);
	waitUntil(getGyroDegrees(gyroSensor) == 90 );
	stopMultipleMotors(leftMotor, rightMotor);
}



// Align to the front of the vertical pole to pick up ring row from starting position
// Start program with this function
void AlignPoleRowFromStart(){
	forward(0.2, rotations, 50);
	// Turn right 90 Degrees
	TurnRight90Degrees();
	// Align against the wall
	moveMotor(sideWays, 2, seconds, 50);
	// Move sideways to align with stack
	moveMotor(sideWays, 0.3, rotations, -50);
}

// Align to the middle line to pick rings from starting position
void AlignMiddleLineFromStart(){
	setMotor(sideWays, 50);
	// Wait keep moving until it detects black line
	waitUntil(getColorGrayscale(colorSensor) <= 50);
	stopMotor(sideWays);
}

void AlignMiddleLineFromVerticalRow(){
	// Turn to face forwards
	TurnLeft90Degrees();
	// Back Up to align with wall
	backward(1, seconds, 50);
	// Move sideways to align with middle strip
	setMotor(sideWays, 50);
	waitUntil(getColorGrayscale(colorSensor) <= 50);
	stopMotor(sideWays);
}

void PoleOneRowtoPoleTwoRow(){
	// Move sideways to next pole row
	sideWaysPID(700, 100, -1);
}

void PoleTwoRowtoPoleThreeRow(){
	// Move sideways to next pole row
	sideWaysPID(690, 100, -1);
}

void PoleThreeRowtoPoleTwoRow(){
	// Move sideways to next pole row
	sideWaysPID(700, 100, 1);
}

void PoleTwoRowtoPoleOneRow(){
	// Move sideways to next pole row
	sideWaysPID(690, 100, 1);
}