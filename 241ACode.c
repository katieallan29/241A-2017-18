#pragma config(Sensor, in1,    powerex,        sensorAnalog)
#pragma config(Sensor, dgtl1,  LEncoder,       sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  REncoder,       sensorQuadEncoder)
#pragma config(Motor,  port2,           L,             tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           TowerL1,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           TowerL2,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           TowerR1,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           TowerR2,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           Claw,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           R,             tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define vexCompetitionState (nVexRCReceiveState & (vrDisabled | vrAutonomousMode))
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(150)
#include "VEX_Competition_Includes.c"
int Program; //Int that determines what autonomous is going to run
void towerCtrl(int power, int time){
		motor[TowerL1] = power;
		motor[TowerL2] = power;
		motor[TowerR1] = power;
		motor[TowerR2] = power;
		wait1Msec(time);
		motor[TowerL1] = 0;
		motor[TowerL2] = 0;
		motor[TowerR1] = 0;
		motor[TowerR2] = 0;
}
void clawCtrl(int power, int time, bool Stop){
		motor[Claw] = power;
		wait1Msec(time);
		if(Stop){
			motor[Claw] =  0;
		}
}
void move(int ticks){
	SensorValue[REncoder] = 0;
	SensorValue[LEncoder] = 0;
	while(SensorValue[LEncoder] <= ticks && SensorValue[REncoder] <= ticks){
		if(SensorValue[LEncoder] <= ticks){
			motor[L] = 127;
		}
		if(SensorValue[REncoder] <= ticks){
			motor[R] = 127;
		}
	}
	motor[L] = 0;
	motor[R] = 0;
}
void moveBack(int ticks){
	SensorValue[REncoder] = 0;
	SensorValue[LEncoder] = 0;
	while(SensorValue[LEncoder] >= -1*ticks && SensorValue[REncoder] >= -1*ticks){
		if(SensorValue[LEncoder] <= ticks){
			motor[L] = -127;
		}
		if(SensorValue[REncoder] <= ticks){
			motor[R] = -127;
		}
	}
	motor[L] = 0;
	motor[R] = 0;
}
void spinLeft(int ticks){
	SensorValue[REncoder] = 0;
	SensorValue[LEncoder] = 0;
	while(SensorValue[LEncoder] <= ticks && SensorValue[REncoder] >= -1*ticks){
		if(SensorValue[LEncoder] <= ticks){
			motor[L] = 127;
		}
		if(SensorValue[REncoder] <= ticks){
			motor[R] = -127;
		}
	}
	motor[L] = 0;
	motor[R] = 0;
}
void pre_auton ()
{
  bStopTasksBetweenModes = true;
	int lcdScreenMin = 1;
	int lcdScreen = 1;
	int lcdScreenMax = 3;
	bLCDBacklight = true;

	const short leftButton = 1;
	const short centerButton = 2;
	const short rightButton = 4;

	while (vexCompetitionState) { //Ensures this code will run ONLY when the robot is disabled
		if (nLCDButtons == leftButton) { //Scrolls to the left
			if (lcdScreenMin == lcdScreen) {
				lcdScreen = lcdScreenMax;
				wait1Msec(250);
			}
			else {
				lcdScreen --;
				wait1Msec(250);
			}
		}
		if (nLCDButtons == rightButton) { //Scrolls to the right
			if (lcdScreenMax == lcdScreen) {
				lcdScreen = lcdScreenMin;
				wait1Msec(250);
			}
			else {
				lcdScreen++;
				wait1Msec(250);
			}
		}
		if (lcdScreen == 1 && Program != 1) {
			displayLCDCenteredString (0, "Forward");
			displayLCDCenteredString (1, "1");
			if (nLCDButtons == centerButton) {
				Program = lcdScreen; //Sets the Program to the one on-screen
				displayLCDCenteredString (0, "Autonomous Has");
				displayLCDCenteredString (1, "Been Selected!");
				wait1Msec(1500);
			}
		}
		else if (lcdScreen == 1 && Program == 1) {
			displayLCDCenteredString (0, "Program"); //We use brackets to mark which program we have chosen
			displayLCDCenteredString (1, "[1]"); //So that while we're scrolling, we can have one marked
		}
		else if (lcdScreen == 2 && Program != 2) {
			displayLCDCenteredString (0, "Left");
			displayLCDCenteredString (1, "2");
			if (nLCDButtons == centerButton) {
				Program = lcdScreen; //Sets the Program to the one on-screen
				displayLCDCenteredString (0, "Autonomous Has");
				displayLCDCenteredString (1, "Been Selected!");
				wait1Msec(1500);
			}
		}
		else if (lcdScreen == 2 && Program == 2) {
			displayLCDCenteredString (0, "Program"); //We use brackets to mark which program we have chosen
			displayLCDCenteredString (1, "[2]"); //So that while we're scrolling, we can have one marked
		}
		else if (lcdScreen == 3 && Program != 3) {
			displayLCDCenteredString (0, "Right");
			displayLCDCenteredString (1, "3");
			if (nLCDButtons == centerButton) {
				Program = lcdScreen; //Sets the Program to the one on-screen
				displayLCDCenteredString (0, "Autonomous Has");
				displayLCDCenteredString (1, "Been Selected!");
				wait1Msec(1500);
			}
		}
		else if (lcdScreen == 3 && Program == 3) {
			displayLCDCenteredString (0, "Program"); //We use brackets to mark which program we have chosen
			displayLCDCenteredString (1, "[3]"); //So that while we're scrolling, we can have one marked
	  }
	}
}
task autonomous () {
	if(Program == 1){
		//Lift Tower
		towerCtrl(100, 1000);

		//Close Claw partway
		clawCtrl(-100, 125, true);

		//Lower Tower
		towerCtrl(-63, 1000);

		//Close Claw fully
		clawCtrl(-127, 800, false);
		//NOT STOPPING CLAW TO ENSURE CONE REMAINS IN THE CLAW

		//Lift Tower
		towerCtrl(100, 1000);

		//Move forward
		move(200);

		//Lower Tower Slightly
		towerCtrl(-100, 200);

		//Open Claw
		clawCtrl(100, 500, true);
	}
	else if(Program == 2){
		move(400);
		towerCtrl(100, 1000);
		clawCtrl(-127, 125, true);
		towerCtrl(-100, 1000);
		clawCtrl(-127, 800, false);
		moveBack(400);
		spinLeft(450);
		move(500);
		clawCtrl(100, 500, true);
	}
	else{
		//Lift Tower
		towerCtrl(100, 1000);

		//Close Claw partway
		clawCtrl(-100, 125, true);

		//Lower Tower
		towerCtrl(-63, 1000);

		//Close Claw fully
		clawCtrl(-127, 800, false);
		//NOT STOPPING CLAW TO ENSURE CONE REMAINS IN THE CLAW

		//Lift Tower
		towerCtrl(100, 1000);

		//Move forward
		move(200);

		//Lower Tower Slightly
		towerCtrl(-100, 200);

		//Open Claw
		clawCtrl(100, 500, true);
	}
}
task usercontrol(){

	//This whole block is dedicated to displaying the Battery Voltage on the LCD Display
	bLCDBacklight = true;									// Turn on LCD Backlight
	string mainBattery;
	string secondaryBattery;
		clearLCDLine(0);											// Clear line 1 (0) of the LCD
		clearLCDLine(1);											// Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		displayLCDString(0, 0, "Primary: ");
		sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		displayNextLCDString(mainBattery);

		//Display the Secondary Robot battery voltage
		displayLCDString(1, 0, "Secondary: ");
		sprintf(secondaryBattery, "%1.2f%c", SensorValue(powerex)/270, 'V');
		displayNextLCDString(secondaryBattery);

		//Short delay for the LCD refresh rate
		wait1Msec(100);

	while (1==1){
		//Right joystick controls right wheels
		motor[R] = vexRT[Ch3]*(0.70);
		//Left joystick controls left wheels
		motor[L] = vexRT[Ch2]*(0.70);

		//Above, we mutiplied the above values by 0.7 to reduce the power going to the motors by 50% in order to reduce overheating

		//Tower controlled by buttons 5U and 5D
		if(vexRT[Btn5D]){
			motor[TowerL1] = -100;
			motor[TowerL2] = -100;
			motor[TowerR1] = -100;
			motor[TowerL2] = -100;
		}
		else if(vexRT[Btn5U]){
			motor[TowerL1] = 104;
			motor[TowerL2] = 104;
			motor[TowerR1] = 104;
			motor[TowerL2] = 104;
		}
		else{
			motor[TowerL1] = 0;
			motor[TowerL2] = 0;
			motor[TowerR1] = 0;
			motor[TowerL2] = 0;
		}
		//Claw opening and closing controlled by Buttons 7U and 8U
		if(vexRT[Btn7U]){
			motor[Claw] = 100;
		}
		else if(vexRT[Btn8U]){
			motor[Claw] = -100;
		}
		else{
			motor[Claw] = 0;
		}
		if(vexRT[Btn8D]){
			Program = 2;
			startTask(autonomous);
			wait1Msec(15000);
			stopTask(autonomous);
		}
		/* press the bottom button of the right buttons to
		start the autonomous*/
	}
}
