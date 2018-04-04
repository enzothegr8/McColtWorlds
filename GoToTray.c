#pragma config(Sensor, port3,  touchLED,       sensorVexIQ_LED)
#pragma config(Sensor, port7,  gyroSensor,     sensorVexIQ_Gyro)
#pragma config(Sensor, port8,  colorSensor,    sensorVexIQ_ColorHue)
#pragma config(Sensor, port12, MColorSensor,   sensorVexIQ_ColorGrayscale)
#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motor4,          sideWays,      tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor5,          storageMotor,  tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, PIDControl, driveRight, encoder)
#pragma config(Motor,  motor10,         vaccum,        tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor11,         stickMotor,    tmotorVexIQ, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


//By: Enzo    3/3/2018
//Updated 4/2/2018



#include "huntersPID.h"

void goToTray()
{
//	moveMotor(sideWays, 60, degrees, -100);
	sideWaysPID(60, 100, -1);
	wait1Msec(350);
	ForwardPID(_DISTANCETRAY, 50);
	wait1Msec(2000);
	moveMotor(sideWays, 1500, milliseconds, -80);
	wait1Msec(500);
	sideWaysPID(0, 80, 1);
	wait1Msec(500);
	//ForwardPID(85, 100);
	forward(800, milliseconds, 60);
	backward(100, degrees, 100);
	wait1Msec(300);
	moveMotor(sideWays, 1000, milliseconds, -80);
	wait1Msec(100);
//	moveMotor(sideWays, 1200, degrees, 50);
	sideWaysPID(680, 80, 1);
	sideWaysPID(0, 80, 1);
	wait1Msec(100);
	//ForwardPID(85, 100);
	forward(800, milliseconds, 60);
	backward(200, degrees, 100);
}



task main()
{

	setTouchLEDColor(touchLED, colorBlue);
	waitUntil(getTouchLEDValue(touchLED)== true);
	wait10Msec(10);
	resetGyro(gyroSensor);
	wait10Msec(10);
	setTouchLEDColor(touchLED, colorRed);
	goToTray();
	setTouchLEDColor(touchLED, colorGreen);
	//	startTask(runVaccum,4);
	// startTask(sortRing, 8);

} // End of main
