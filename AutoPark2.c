#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTServo)
#pragma config(Sensor, S2,     HTIRS2,         sensorI2CCustom)
#pragma config(Sensor, S3,     sonarSensor,    sensorSONAR)
#pragma config(Sensor, S4,     LiftDownTouch,  sensorTouch)
#pragma config(Motor,  mtr_S1_C1_1,     LiftA,         tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     LiftB,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     BackLeft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     FrontLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_1,     FrontRight,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     BackRight,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C4_1,    BallRelease,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_2,    FourBarLink,          tServoStandard)
#pragma config(Servo,  srvo_S1_C4_3,    KickStand,            tServoStandard)
#pragma config(Servo,  srvo_S1_C4_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C4_6,    Tow,                  tServoStandard)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define DRIVE_FORWARD 0
#define DRIVE_BACK 1
#define STRAFE_RIGHT 2
#define STRAFE_LEFT 3
#define ROTATE_RIGHT 4
#define ROTATE_LEFT 5

#include "RBButtonLib.h";
#include "JoystickDriver.c";  //Include file to "handle" the Bluetooth messages.
RB_Button_State ButtonState;
#include "SemiAutoLiftLib.c"
#include "lego-ultrasound.h"
#include "hitechnic-irseeker-v2.h"
// Create struct to hold sensor data
tHTIRS2 irSeeker;

const int NXTMinimumBatteryLevel = 6300;
const int TETRIXMinimumBatteryLevel = 13100;//voltage should be no higher than 13.5 or the results will be unperdictable.
int HZb = 950;

void DOT()
{

	playTone(HZb,7);
	playTone(0,7);
	sleep(140);
}
void DASH()
{
	playTone(HZb,21);
	playTone(0,7);
	sleep(280);
}
void CSPACE()
{
	playTone(0,21);
	sleep(210);
}
void initializeRobot()
{
	nVolume = 4;
	initSensor(&irSeeker, S2);
	int IRValue = irSeeker.acValues[2];
	int USValue = SensorValue(sonarSensor);
	servo[BallRelease] = -80;
	FourBarDeployed=false;
	servo[KickStand] =70;
	servo[Tow] = 70;
	if (! SensorValue[LiftDownTouch] || externalBatteryAvg <= TETRIXMinimumBatteryLevel || nImmediateBatteryLevel <= NXTMinimumBatteryLevel)//if NOT bottom button is pressed warn driver to go down
	{
		while(true)
		{//SOR = Save Our Robot
			DOT();
			DOT();
			DOT();
			CSPACE();
			DASH();
			DASH();
			DASH();
			CSPACE();
			DOT();
			DASH();
			DOT();
			playTone(0,70);
			sleep(700);
		}
	}
}

void InchDrive(int Action, int DriveXin)
{
	writeDebugStreamLine("STARTING INCHDRIVE");
	if(DriveXin < 0) return;
	int MotorRunTime = 0;

	int Brake1 = 8;
	float Brake1MS = 88.75;

	int Brake2 = 17;
	float Brake2MS = 68.89;

	int Brake3 = 25;
	float Brake3MS = 66.51;

	float Brake4MS = 66.51;


	//average	8, 17, 25
	//MsPerInch	88.75, 68.89, 66.51

	if(DriveXin >= Brake1)
	{
		writeDebugStreamLine("BREAK1");
		if (DriveXin >= Brake2)
		{
			writeDebugStreamLine("BREAK2");
			if(DriveXin >= Brake3)
			{
				writeDebugStreamLine("BREAK3");
				MotorRunTime = Brake1 * Brake1MS;
				DriveXin -= Brake1;
				MotorRunTime += (Brake2 - Brake1) * Brake2MS;
				DriveXin -= (Brake2-Brake1);
				MotorRunTime += (Brake3 - Brake2) * Brake3MS;
				DriveXin -= (Brake3 - Brake2);
				MotorRunTime += DriveXin * Brake4MS;
			}
			else
			{
				MotorRunTime = Brake1 * Brake1MS;
				DriveXin -= Brake1;
				MotorRunTime += (Brake2 - Brake1) * Brake2MS;
				DriveXin -= (Brake2-Brake1);
				MotorRunTime += DriveXin * Brake3MS;
			}
		}
		else
		{
			MotorRunTime = Brake1 * Brake1MS;
			DriveXin -= Brake1;
			MotorRunTime += DriveXin * Brake2MS;
		}
	}
	else
	{
		MotorRunTime = DriveXin * Brake1MS;
	}
	writeDebugStreamLine("RUNNING MOTORS");
	switch (Action)
	{
	case DRIVE_FORWARD:
		motor[FrontRight]=25;
		motor[FrontLeft]=-25;
		motor[BackRight]=25;
		motor[BackLeft]=-25;
		// DriveBackForward(25);
		break;
	case DRIVE_BACK:
		motor[FrontRight]=-25;
		motor[FrontLeft]=25;
		motor[BackRight]=-25;
		motor[BackLeft]=25;
		// DriveBackForward(-25);
		break;
	case STRAFE_RIGHT:
		motor[FrontRight]=-25;
		motor[FrontLeft]=-25;
		motor[BackRight]=25;
		motor[BackLeft]=25;
		// DriveStrafe(25);
		break;
	case STRAFE_LEFT:
		motor[FrontRight]=25;
		motor[FrontLeft]=25;
		motor[BackRight]=-25;
		motor[BackLeft]=-25;
		// DriveStrafe(-25);
		break;

	default:
		break;
	}
	writeDebugStreamLine("Delay %d ms",MotorRunTime);

	sleep(MotorRunTime);
	motor[FrontRight]=0;
	motor[FrontLeft]=-0;
	motor[BackRight]=0;
	motor[BackLeft]=-0;
	writeDebugStreamLine("FINISHED INCHDRIVE");

}
int cGFinder() // center goal finder
{
	//writeDebugStreamLine("STARTING CGP FINDER"); Test 2
	int cGPosition = 0;
	//writeDebugStreamLine("READING US");
	int USValue = SensorValue(sonarSensor);
	readSensor(&irSeeker);
	int IRValue = irSeeker.acValues[2];
	writeDebugStreamLine("ir: %d",IRValue );
	writeDebugStreamLine("uSCDist: %d",USValue );
	//If GP = 3, IR = 0, US = ~65cm from sensor
	//If GP = 2, IR = 10, US = ~155cm
	//If GP = 1, IR >= 15, US = ~45cm

	//if(IRValue >= 7 && USValue	 < 36)
	if(USValue < 40)
	{
		cGPosition = 1;
	}
	//writeDebugStreamLine("FINISHED CGP FINDER"); Test 2
	return cGPosition;
}
task main()
{

	writeDebugStreamLine("Starting Program");
	// robot starts right side of robot touching wall
	initializeRobot();
	waitForStart();
	startTask(LiftTeleOP);
	startTask(KickStandTeleOP);
	DesiredFloor = 2;// take to 60cm height
	motor[FrontLeft]=75;
	motor[BackRight]=-75;
	sleep(2575);
	FourBarDeployed = false;
	motor[FrontRight]=75;
	motor[FrontLeft]=75;
	motor[BackRight]=-75;
	sleep(50);
	motor[BackLeft]=-75;
	FourBarDeployed = false;
	sleep(1100);
	motor[FrontRight]=0;
	motor[FrontLeft]=0;
	motor[BackRight]=0;
	motor[BackLeft]=0;
	sleep(500);
	int CGFound = cGFinder();
	time1[T1]=0;
	int pings = 0;
	while((time1[T1] <= 3000) && (CGFound == 0))
	{
		motor[FrontRight]=-21;
		motor[FrontLeft]=-17;
		motor[BackRight]=53;
		motor[BackLeft]=51;
		CGFound = cGFinder();
		pings++;
	}
	sleep(100);
	motor[FrontRight]=0;
	motor[FrontLeft]=0;
	motor[BackRight]=0;
	motor[BackLeft]=0;
	sleep(100);
	// Begin scoring
	if (CGFound == 1)
	{
		//InchDrive(DRIVE_BACK,6);
		//us drive back till 13in
		int USValue = SensorValue(sonarSensor);
		while (USValue < 33)
		{
			motor[FrontRight]=-25;
			motor[FrontLeft]=25;
			motor[BackRight]=-25;
			motor[BackLeft]=25;
			USValue = SensorValue(sonarSensor);
			writeDebugStreamLine("Back %d",USValue);
			sleep(10);
		}
		motor[FrontRight]=0;
		motor[FrontLeft]=0;
		motor[BackRight]=0;
		motor[BackLeft]=0;
		FourBarDeployed = true;
		DesiredFloor = 4;

		while(GetLiftEnc() <  (FloorHeight[DesiredFloor]- LiftEncGap))
		{
			//writeDebugStreamLine("GetLiftEnc:%d", GetLiftEnc() );
			sleep(100);
		}
		sleep(250);
		//InchDrive(DRIVE_FORWARD, 8);
		//us drive forward till 8in
		USValue = SensorValue(sonarSensor);
		while (USValue > 26)
		{
			motor[FrontRight]=25;
			motor[FrontLeft]=-25;
			motor[BackRight]=25;
			motor[BackLeft]=-25;
			USValue = SensorValue(sonarSensor);
			writeDebugStreamLine("Forward %d",USValue);
			sleep(10);
		}
		motor[FrontRight]=0;
		motor[FrontLeft]=0;
		motor[BackRight]=0;
		motor[BackLeft]=0;
		sleep(100);
		ForceScoreOpen = true;
		motor[FrontRight]=25;
		motor[FrontLeft]=25;
		motor[BackRight]=25;
		motor[BackLeft]=25;
		sleep(100);
		motor[FrontRight]=-25;
		motor[FrontLeft]=-25;
		motor[BackRight]=-25;
		motor[BackLeft]=-25;
		sleep(100);
		motor[FrontRight]=25;
		motor[FrontLeft]=25;
		motor[BackRight]=25;
		motor[BackLeft]=25;
		sleep(100);
		motor[FrontRight]=-25;
		motor[FrontLeft]=-25;
		motor[BackRight]=-25;
		motor[BackLeft]=-25;
		sleep(100);
		motor[FrontRight]=0;
		motor[FrontLeft]=0;
		motor[BackRight]=0;
		motor[BackLeft]=0;
		sleep(1000);
		ForceScoreOpen = false;
		InchDrive(DRIVE_BACK, 8);
		InchDrive(STRAFE_RIGHT, 22);
		motor[FrontRight]=-25;
		motor[FrontLeft]=-25;
		motor[BackRight]=-25;
		motor[BackLeft]=-25;
		DesiredFloor = 0;
		sleep(500);
		motor[FrontRight]=0;
		motor[FrontLeft]=0;
		motor[BackRight]=0;
		motor[BackLeft]=0;
		sleep(3000);
		KickStandDown = true;
		motor[BackLeft]=-95;
		motor[FrontRight]=95;
		sleep(2000);
		motor[FrontRight]=0;
		motor[FrontLeft]=0;
		motor[BackRight]=0;
		motor[BackLeft]=0;
	}
	else
	{
		writeDebugStreamLine("CG Not Found");
		DesiredFloor = 0;
	}
	writeDebugStreamLine("# of pings:%d", pings );
	while (true)
	{}
}
