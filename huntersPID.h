

//By: Enzo    3/3/2018
//Updated 4/2/2018

#define _DISTANCETRAY 1100
#define _Kp 1
#define _Ki 0.8
#define _resetKi 20 // #Cycles we want to reset Ki

float getError()
{
	float error = 0;
	error = getGyroDegreesFloat(gyroSensor);
	return (error);
}

void ForwardPID(int distanceInDegrees, int speedPID){
	int speed = speedPID;
	int speedLeft = speedPID;
	int speedRight = speedPID;

	float Kproportional = _Kp;
	float error = 0;

	resetMotorEncoder(rightMotor);
	while (getMotorEncoder(rightMotor) < distanceInDegrees){
		setMotorSpeed(leftMotor, speedLeft);
		setMotorSpeed(rightMotor, speedRight);
		error = getError();

		if(error>0)
		{
			speedLeft= speed +((abs(error)/2)*Kproportional);
			speedRight= speed -((abs(error)/2)*Kproportional);
		}
		else if(error<0)
		{
			speedLeft = speed -((abs(error)/2)*Kproportional);
			speedRight = speed +((abs(error)/2)*Kproportional);
		}
		else if(error == 0)
		{
			speedLeft=speed;
			speedRight=speed;
		}

		setMotorSpeed(leftMotor, speedLeft);
		setMotorSpeed(rightMotor,speedRight);
		displayCenteredTextLine(2,"SpeedLeft: %f",speedLeft);
		displayCenteredTextLine(3,"SpeedRight: %f",speedRight);
		displayCenteredTextLine(4,"Error: %f",error);
	}
}
void sideWaysPID(int distanceInDegrees, int speedPID, int direction){
	int speed = speedPID;
	int speedLeft = speedPID / 1;
	int speedRight = speedPID / 1;
	int resetKi = _resetKi;
	float Kproportional = _Kp;
	float Kintegral = _Ki;
	float error = 0;
	float sumError =0;

	resetMotorEncoder(leftMotor);
	resetMotorEncoder(sideWays);
	if (distanceInDegrees <= 0) {
		// when distance is this way we use the colorSensor to detect and stop on the next black line

		while (getColorGrayscale(MColorSensor) > 80) {
			setMotor(sideWays,(speed * direction));
			error = getError();

			if(error>0) // Robot is deviating to the left
				{
				// proportonal only
				resetMotorEncoder(rightMotor);
				moveMotor(rightMotor, -abs(error)* Kproportional*3, degrees, -speedRight);


				}

			else if(error<0) // Robot is deviating to the right
				{
				// proportonal only
				resetMotorEncoder(leftMotor);
				moveMotor(leftMotor, abs(error)* Kproportional*3, degrees,-speedLeft);

				}
			} // end while
		} // end if

	else {
	// Loop to move
	while (abs(getMotorEncoder(sideWays)) < distanceInDegrees){




		setMotorSpeed(sideWays, (speed * direction));

		error = getError();

		if(error>0) // Robot is deviating to the left
			{

			// proportonal only

				resetMotorEncoder(rightMotor);
				moveMotor(rightMotor, - abs(error) * Kproportional*3,degrees, -speedRight);


			}
		else if(error<0) // Robot is deviating to the right
			{
			// proportonal only
				resetMotorEncoder(leftMotor);
				moveMotor(leftMotor, abs(error)* Kproportional*3, degrees, -speedLeft);

		}

	 } // end of While

  } // end of else

		setMotorSpeed(leftMotor, 0);
		setMotorSpeed(rightMotor, 0);
		setMotorSpeed(sideWays, 0);
		stopMultipleMotors(leftMotor, rightMotor,sideWays);

}
