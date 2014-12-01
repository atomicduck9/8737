#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     LiftDownTouch,  sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     FrontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     BackRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     BackLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     LiftA,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     LiftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S2_C1_1,    BallRelease,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    FourBarLink,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    Tow,                  tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "../RBButtonLib.h";
RB_Button_State ButtonState;
#include "../SemiAutoLiftLib.c";

task main()
{
	RB_Button_Init(ButtonState);
	nNxtExitClicks = 10;
	startTask(LiftTeleOP);
	while(true)
	{
		int b=nNxtButtonPressed;
		if (b>0) nNxtExitClicks = 10; // Reset exits again on each use of other button
			switch (b)
		{
			// 0 = Gray Rectangle button. 1 = Right Arrow button. 2 = Left Arrow button. 3 = Orange Square button.
		case 0: b=13; // Auto Ground
		case 1: b=5;  // Manual Up
		case 2: b=14; // Manual Down
		case 3: b=6;  // Auto Floor Up
		defaut:
		}
	RB_Button_addState(ButtonState, (b<1 ? 0 : (1<<(b-1))));
	}
}