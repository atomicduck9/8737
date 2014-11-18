#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     Touch,          sensorTouch)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S4,     LiftZeroSensor, sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     FrontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     BackRight,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     BackLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     LiftA,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     LiftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C4_1,    up,                   tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    forebarlink,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    Tow,                  tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                    - Tetrix Quiet  Tank Drive -                                        *|
|*                                          ROBOTC on Tetrix                                              *|
|*                                                                                                        *|
|*  This program allows you to drive a robot via remote control using the ROBOTC Debugger.                *|
|*  This particular method uses "Tank Drive" where each side is controlled individually like a tank.      *|
|*  This program also ignores low values that would cause your robot to move when the joysticks fail to   *|
|*  return back to exact center.  You may need to play with the 'threshold' value to get it just right.   *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*    NOTES:       5                                                                                      *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port D                  motorD              12V                 Right motor                         *|
|*    Port E                  motorE              12V                 Left motor                          *|
\*---------------------------------------------------------------------------------------------------4246-*/
#include "RBButtonLib.h";
RB_Button_State ButtonState;
#include "JoystickDriver.c"
#include "SemiAutoLiftLib.c";
#include "RobotMainLib.c"

task main()
{
	RB_Button_Init(ButtonState);
	startTask(LiftTeleOP);
	startTask(Drive);
	//	startTask(Lift);
	startTask(ScoreOpenClose);
	startTask(Forebar);
	startTask(TowMech);
	//wait1Msec(120000);
	wait1Msec(1200);
	while(true)
	{
		getJoystickSettings(joystick);
		// Add Triggers as Buttons: 13=Right, 14=Left
		short Z2 = joystick.joy1_y2;
		short extraButtons = (Z2>=10 ? 1<<12 : (Z2<=-10 ? 1<<13 : 0));
		writeDebugStreamLine("z2=%d b=%d e=%d", Z2, joystick.joy1_Buttons, extraButtons);
		RB_Button_addState (ButtonState, joystick.joy1_Buttons | extraButtons);
		wait1Msec(20);
	}
}
