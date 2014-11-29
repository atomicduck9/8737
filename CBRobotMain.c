#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     LiftDownTouch,  sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     LiftA,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     LiftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     BackLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     FrontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     BackRight,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    BallRelease,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    FourBarLink,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    KickStand,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    Tow,                  tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "RBButtonLib.h";
RB_Button_State ButtonState;
#include "JoystickDriver.c"
#include "SemiAutoLiftLib.c";
#include "CBRobotMainLib.c"

void initializeRobot()
{
	SetFourBar(false);//set 4 bar down
	SetScoreOpen(false);//close score string
	servo[Tow]=0; // tow arm set down

	if (! SensorValue[LiftDownTouch])//if NOT bottom button is pressed warn driver to go down
	{
		playTone(1000,500); // 1000Hz for 1/2sec
	}
}


task main()
{
	RB_Button_Init(ButtonState);

	initializeRobot(); // Servo etc setup
	waitForStart(); // wait for start of tele-op phase

	startTask(LiftTeleOP);
	startTask(CBDrive);
	startTask(TowMechTeleOP);
	startTask(KickStandTeleOP);
	wait1Msec(1200);
	while(true)
	{
		getJoystickSettings(joystick);
		// Add Triggers as Buttons: 13=Right, 14=Left
		// short Z2 = joystick.joy1_y2;
		// short extraButtons = (Z2>=10 ? 1<<12 : (Z2<=-10 ? 1<<13 : 0));
		// RB_Button_addState (ButtonState, joystick.joy1_Buttons | extraButtons);
		RB_Button_addState (ButtonState, joystick.joy1_Buttons);
		wait1Msec(20);
	}
}
