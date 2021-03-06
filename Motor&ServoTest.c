#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  none)
#pragma config(Hubs,  S2, HTServo,  none,     none,     none)
#pragma config(Sensor, S3,     HTSMUX,         sensorI2CCustom9V)
#pragma config(Sensor, S4,     Touch,          sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     LiftA,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LiftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     BackLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     FrontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     BackRight,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    up,                   tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    forebarlink,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    Tow,                  tServoStandard)
#pragma DebuggerWindows("joystickGame")
#pragma DebuggerWindows("debugStream")
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
motor[LiftA]=20;
motor[LiftB]=20;
motor[BackLeft]=20;
motor[FrontLeft]=20;
motor[FrontRight]=20;
motor[BackRight]=20;
servo[Tow]=90;
servo[up]=90;
servo[forebarlink]=90;
sleep(500);
motor[LiftA]=0;
motor[LiftB]=0;
motor[BackLeft]=0;
motor[FrontLeft]=0;
motor[FrontRight]=0;
motor[BackRight]=0;
servo[Tow]=0;
servo[up]=0;
servo[forebarlink]=0;
}
