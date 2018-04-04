#define _Kp 0.7
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

	float Kproportional = _Kp; float error = 0; resetMotorEncoder(rightMotor);
	while(getMotorEncoder(rightMotor) < distanceInDegrees){
		setMotorSpeed(leftMotor, speedLeft);
		setMotorSpeed(rightMotor, speedRight);
		error = getError();
		if(error>0){
			speedLeft= speed +((abs(error)/2)*Kproportional);
			speedRight= speed -((abs(error)/2)*Kproportional);
		}
		else if(error<0){
			speedLeft = speed -((abs(error)/2)*Kproportional);
			speedRight = speed +((abs(error)/2)*Kproportional);
		}
		else if(error == 0){
			speedLeft=speed; speedRight=speed;
		}
		setMotorSpeed(leftMotor, speedLeft);
		setMotorSpeed(rightMotor,speedRight);
		displayCenteredTextLine(2,"SpeedLeft: %f",speedLeft);
		displayCenteredTextLine(3,"SpeedRight: %f",speedRight);
		displayCenteredTextLine(4,"Error: %f",error); }
}
