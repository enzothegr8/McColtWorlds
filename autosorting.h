
//Moves the stick motor clockwise
void moveNext ()
{
	resetMotorEncoder(stickMotor);
	while (getMotorEncoder(stickMotor) < 110)
	{
		setMotorSpeed(stickMotor, 127);
	}
	setMotorSpeed(stickMotor, 0);
}
//Moves the stick motor counterclockwise
void movePrevious ()
{
	resetMotorEncoder(stickMotor);
	while (getMotorEncoder(stickMotor) > -110)
	{
		setMotorSpeed(stickMotor, -127);
	}
	setMotorSpeed(stickMotor, 0);
}

//This is the task to sort the rings based on the color sensor.
task sortRing ()
{
int startPosition =0;//Here we are seting the starting postion at whatever stick it is on.
//It is usually onthe blue stick.
int proximity =0;
string colorDetected = "_";
int saturation = 0;
long greenChannel = getColorGreenChannel(colorSensor);
long blueChannel = getColorBlueChannel(colorSensor);
long redChannel = getColorRedChannel(colorSensor);
setTouchLEDColor(touchLED, colorNone);

	datalogClear();

	datalogRate(25,milliseconds);
	datalogStart();
if(getColorMode(colorSensor) != colorTypeRGB_Hue_Reflected)
		{
			setColorMode(colorSensor, colorTypeRGB_Hue_Reflected);
		}

if(getColorMode(MColorSensor) != colorTypeGrayscale_Ambient)
		{
			setColorMode(MColorSensor, colorTypeGrayscale_Ambient);
		}
while (true) {
//This is to test if it is on RGB mode and Reflected.

		//This is the right distance to only detect the rings and nothing else.
		proximity = getColorProximity(colorSensor);
		saturation = getColorSaturation(colorSensor);
		 greenChannel = getColorGreenChannel(colorSensor);
		blueChannel = getColorBlueChannel(colorSensor);
		redChannel = getColorRedChannel(colorSensor);
		if (proximity >= 185)
		{
			//Displays the information on the brain screen.
			long ringHueValue = getColorHue(colorSensor);

			displayCenteredTextLine(4,"Proximity: %d",getColorProximity(colorSensor));
			displayCenteredTextLine(3,"Green channel: %d ", getColorGreenChannel(colorSensor));
			displayCenteredTextLine(5,"Saturation: %d ", getColorSaturation(colorSensor));




			// Default stick position is Blue
			// Blue = 1 ; Green = 2 ; Red = 3
			if ((startPosition == 0) || (startPosition == 1)) {
				ringHueValue = getColorHue(colorSensor);
				displayCenteredTextLine(2,"position: %d",startPosition);
				displayCenteredTextLine(0,"Color Value :%d",ringHueValue);
				// Test if ring color is blue

				if (ringHueValue >= 155 && ringHueValue < 175 && saturation > 180)
					//Saturation helps making it is blue since only blue rings have a saturation level this high.
				{
					setTouchLEDHue(touchLED, ringHueValue);
					colorDetected = "Blue";
					displayCenteredTextLine(1,colorDetected);
					startPosition =1;
					// No change on the  Stick Position
				}

				// Test if ring color is Red
				else if ((ringHueValue >=0 && ringHueValue < 32) || ringHueValue > 200)
				{
				colorDetected = "red";
				displayCenteredTextLine(1,"Red");
					setTouchLEDHue(touchLED, ringHueValue);
					resetMotorEncoder(stickMotor);
					startPosition = 3; // Red
					moveNext();//Turning the stick motor clockwise.
				}
			else if (ringHueValue >= 80 && ringHueValue < 155 && saturation > 120)
				{
					setTouchLEDHue(touchLED, ringHueValue);
					startPosition = 2; // Assign to Green
					movePrevious();
					colorDetected = "Green";
					displayCenteredTextLine(1,	colorDetected);
				}
			} // end if startPosition

			else if (startPosition == 2) {

				displayCenteredTextLine(0,"Color Value :%d",ringHueValue);
				displayCenteredTextLine(2,"postion: %d",startPosition);
				ringHueValue = getColorHue(colorSensor);
				if ((ringHueValue >=0 && ringHueValue < 32) || ringHueValue > 200)
				{
					setTouchLEDHue(touchLED, ringHueValue);
					colorDetected = "Red";
					displayCenteredTextLine(1,	colorDetected);
					startPosition = 3; // Assign to Red
					movePrevious();//moving the stick motor counterclockwise.

				}
				else if (ringHueValue >= 155 && ringHueValue < 175 && 	saturation  > 180)
				{
					setTouchLEDHue(touchLED, ringHueValue);
					colorDetected = "Blue";
					displayCenteredTextLine(1,	colorDetected);
					startPosition = 1; // Assign the stick current position to Blue
					moveNext();//moving the stick motor clockwise.

				}
			else if (ringHueValue >= 80 && 	ringHueValue < 155  && saturation > 120)

				{
					colorDetected = "Green";
					displayCenteredTextLine(1,	colorDetected);
					setTouchLEDHue(touchLED, ringHueValue);
					// No change on the stick position
					startPosition = 2; // Green
				}
			} // end if startPosition == 2

			else if (startPosition == 3) { // Red
				ringHueValue = getColorHue(colorSensor);
				displayCenteredTextLine(2,"position: %d",startPosition);
				displayCenteredTextLine(0,"Color Value :%d",ringHueValue);

				if ((ringHueValue >=0 && ringHueValue < 32) || ringHueValue > 200)
					{
					// No change on the  Stick Position
					colorDetected = "Red";
					displayCenteredTextLine(1,	colorDetected);
					startPosition = 3; // Red
					setTouchLEDHue(touchLED, 	ringHueValue);

				}

				else if (ringHueValue >= 155 && ringHueValue < 175 && saturation > 180)
					{
					setTouchLEDHue(touchLED, 	ringHueValue);
					colorDetected = "Blue";
					displayCenteredTextLine(1,	colorDetected);
					startPosition = 1; // Assign the stick current position to Blue
					movePrevious();

				}
				else if (ringHueValue >= 80 && 	ringHueValue < 155 && saturation > 120)
				{
					colorDetected = "Green";
					displayCenteredTextLine(1,	colorDetected);
					setTouchLEDHue(touchLED, 	ringHueValue);
					startPosition = 2; // Green
					moveNext();
				}
			} // end if startPosition == 3


		datalogDataGroupStart();
		datalogAddValue (0, proximity);
		datalogAddValue (1, ringHueValue);
	//	datalogAddValue(2, ringHueValue1);
	//	datalogAddValue (3, ringHueValue2);
		datalogAddValue (6, startPosition);
		datalogAddValue (5, saturation);
		datalogAddValue(2,greenChannel);
		datalogAddValue(3,blueChannel);
	datalogAddValue(4,redChannel);
		datalogDataGroupEnd();

		} // end if getColorProximity


		wait1Msec(25);
	} // end of While

	datalogStop();
}
