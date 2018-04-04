
void TurnRight180Degrees () {
	resetGyro(gyroSensor);

	setMotor(rightMotor,35);
	setMotor(leftMotor, -35);

	waitUntil(getGyroHeading(gyroSensor) == 140);

	setMotorSpeed(rightMotor,0);
}


void ScoreLowVertical () {

	//Allign With Pole
	TurnRight180Degrees();
	wait(300,milliseconds);
	forward(0.25,rotations,30);
	moveMotor(sideWays,0.25,rotations,100);
	while(getColorGrayscale(MColorSensor) > 20) {
		setMotor(sideWays,-100);
	}
	setMotor(sideWays,0);
	backward(2.5,seconds,50);

	//Score Rigns
	moveMotor(storageMotor,2.5,rotations,100);
	wait(200,milliseconds);
	moveMotor(storageMotor,-2.5,rotations,100);
	moveMotor(stickMotor,0.33,rotations,100);

	//Go Back to Original Position
	forward(0.46,rotations,40);
	TurnRight180Degrees();

}
