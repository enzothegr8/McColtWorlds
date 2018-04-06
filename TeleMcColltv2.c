#pragma config(Sensor, port3,  touchLED,       sensorVexIQ_LED)
#pragma config(Sensor, port7,  gyroSensor,     sensorVexIQ_Gyro)
#pragma config(Sensor, port8,  colorSensor,    sensorVexIQ_ColorHue)
#pragma config(Sensor, port12, MColorSensor,   sensorVexIQ_ColorGrayscale)
#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, PIDControl, reversed, driveLeft, encoder)
#pragma config(Motor,  motor4,          sideWays,      tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor5,          storageMotor,  tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, PIDControl, driveRight, encoder)
#pragma config(Motor,  motor10,         vaccum,        tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor11,         stickMotor,    tmotorVexIQ, openLoop, reversed, encoder)

#include "autosorting.h"

/*------------------------------------------------------------------------------------------------
Hunter Program TeleMcColtv2
By: Enzo (updated 03/24 2018)
------------------------------------------------------------------------------------------------*/

//Runs the vacuum for the time set in timeMotorRuns when button R is pressed
task runVaccum() {
	while(true) {
		int timeMotorRuns = 45; // Seconds the vacuum runs once the button is pressed
		//If Button "R-Up" is pressed it runs the vacuum. This is the way to pick up the rings.
		if(getJoystickValue(BtnRUp) == 1)
		{
			resetTimer(T1);
			setMotorSpeed(vaccum, 90);
		}
		//If the "R-Down" is pressed, then it will run the vacuum in the opposite direction.
		else if(getJoystickValue(BtnRDown) == 1)
		{
			setMotorSpeed(vaccum, -70);
		}

		else  //If the button is not pressed(and the timer is done), it won't run the motor.
		{
			if (getTimer(T1, seconds) > timeMotorRuns)
			{setMotorSpeed(vaccum, 0);}
		}
		wait1Msec(25);//This gives a break to the processor as suggested in the Vex forum
	}
}

task main()
{
	//starting tasks runVacuum and sortRing
	startTask(runVaccum,4);
	startTask(sortRing, 8);

	int threshold = 10;
	int thresholdFullSpeed = 110;
	while(true)
	{
		//If the ChannelA (left Y-Axis) is greater than the threshold value,
		//then we'll set the speed of the motor to the value we get from the joystick.
		if((getJoystickValue(ChA) > threshold) || (getJoystickValue(ChA) < -threshold))
		{
			if((getJoystickValue(ChA) < thresholdFullSpeed) || (getJoystickValue(ChA) > -thresholdFullSpeed))
			{
				setMotorSpeed(leftMotor, (getJoystickValue(ChA) * 0.60));
			}
			else { setMotorSpeed(leftMotor, getJoystickValue(ChA * 1));}
		}
		else  //If less than the threshold, we'll set the motor to zero.
		{
			setMotorSpeed(leftMotor, 0);
		}

		//If the ChannelD (right Y-Axis) is greater than the threshold value,
		//then we'll set the speed of the motor to value from the joystick.
		if((getJoystickValue(ChD) > threshold) || (getJoystickValue(ChD) < -threshold))
		{
			if((getJoystickValue(ChD) < thresholdFullSpeed) || (getJoystickValue(ChD) > -thresholdFullSpeed))
			{ setMotorSpeed(rightMotor, (getJoystickValue(ChD)* 0.60));}
			else {setMotorSpeed(rightMotor, getJoystickValue(ChD)* 1);}

		}
		else  //If less than the threshold, we'll set the motor to zero.
		{
			setMotorSpeed(rightMotor, 0);
		}
		//If Button "L-Up" is pressed in.
		if(getJoystickValue(BtnLUp) == 1)
		{
			setMotorSpeed(sideWays, -127);
		}
		//If the "L-Up" isn't pressed, but "L-Down" is, we'll set the motor to run forward.
		else if(getJoystickValue(BtnLDown) == 1)
		{
			setMotorSpeed(sideWays, 127);
		}
		else  //If neither button is pressed, we'll set the motor off.
		{
			setMotorSpeed(sideWays, 0);
		}

		// Storage on button F
		if(getJoystickValue(BtnFUp) == 1)
		{

			setMotorSpeed(storageMotor, 127);

		}
		//If the "F-Up" isn't pressed, but "L-Down" is, we'll set the motor to run forward.
		else if(getJoystickValue(BtnFDown) == 1)
		{
				setMotorSpeed(storageMotor, -127);
		}
		else  //If neither button is pressed, we'll set the motor off.
		{
			setMotorSpeed(storageMotor, 0);
		}

		//If Button "E-Up" (stickMotor) is pressed in, we'll set the arm motor to run in reverse.
		if(getJoystickValue(BtnEUp) == 1)
		{
		setMotorSpeed(stickMotor,-40);
		}
		//If the "E-Up" isn't pressed, but "L-Down" is, we'll set the motor to run forward.
		else if(getJoystickValue(BtnEDown) == 1)
		{
			setMotorSpeed(stickMotor, 40);
		}
		else  //If neither button is pressed, we'll set the motor off.
		{
			setMotorSpeed(stickMotor, 0);
		}

	wait1Msec(25);
 	} // End of While
} // End of main
