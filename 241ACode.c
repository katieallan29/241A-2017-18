#pragma config(Motor,  port2,           L,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           R,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           TowerL1,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           TowerL2,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           TowerR1,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           TowerR2,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           Claw,         tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(150)
#include "VEX_Competition_Includes.c"
void pre_auton (){
}
task autonomous () {
		motor[L] = 100;
		motor[R] = 100;
		wait1Msec(4000);
		motor[L] = 0;
		motor[R] = 0;

		/*
		//WIP Autonomous
		//How many inches the bot moves in 1 second
		int secIn = 33.52;
		//Move forward for 49 inches
		motor[L] = 127;
		motor[R] = 127;
		wait1Msec((49/secIn)*1000);
		//Move backward for 49 inches
		motor[R] = -127;
		motor[L] = -127;
		wait1Msec((49/secIn)*1000);
		//Rotate bot clockwise 130 degrees
		motor[R] = -127;
		motor[L] = 127;
		wait1Msec(1300);
		//Move forward 12 inches
		motor[R] = 127;
		motor[L] = 127;
		wait1Msec((12/secIn)*1000);
		//Stop
		motor[R] = 0;
		motor[L] = 0;
		*/
}
task usercontrol(){
	while (1==1){
		//Right joystick controls right wheels
		motor[R] = vexRT[Ch2]*(0.65);
		//Left joystick controls left wheels
		motor[L] = vexRT[Ch3]*(0.65);

		//Above, we mutiplied the above values by 0.5 to reduce the power going to the motors by 50% in order to reduce overheating

		//Tower controlled by buttons 5U and 5D
		if(vexRT[Btn5D]){
			motor[TowerL1] = -100;
			motor[TowerL2] = -100;
			motor[TowerR1] = -100;
			motor[TowerL2] = -100;
			wait1Msec(1);
			motor[TowerL1] = 0;
			motor[TowerL2] = 0;
			motor[TowerR1] = 0;
			motor[TowerL2] = 0;
		}
		if(vexRT[Btn5U]){
			motor[TowerL1] = 100;
			motor[TowerL2] = 100;
			motor[TowerR1] = 100;
			motor[TowerL2] = 100;
			wait1Msec(1);
			motor[TowerL1] = 0;
			motor[TowerL2] = 0;
			motor[TowerR1] = 0;
			motor[TowerL2] = 0;
		}
		//Claw opening and closing controlled by Buttons 7U and 8U
		if(vexRT[Btn7U]){
			motor[Claw] = 100;
			wait1Msec(1);
			motor[Claw] = 0;
		}
		if(vexRT[Btn8U]){
			motor[Claw] = -100;
			wait1Msec(1);
			motor[Claw] = 0;
		}
		if(vexRT[Btn8D]){
			startTask(autonomous);
			wait1Msec(15000);
			stopTask(autonomous);
		}
		/* press the bottom button of the right buttons to
		start the autonomous*/
	}
}
