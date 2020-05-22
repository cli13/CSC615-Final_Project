/**************************************************************
* Class: CSC-615-01 Spring 2020
* Project: <Final Project>
*
* File: <motorsController.h>
*
* Description: This header files defines the functions to be
*              be implemented in motorsController.c
*              All the included libraries are listed here.
*              This file also has all the macros being used to make code more readable.
**************************************************************/
#ifndef MOTORSCONTROLLER_H_   
#define MOTORSCONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MAX_INTENCITY           100 //the max range the motor can reach in power.
#define MIN_INTENCITY            0  //the min range the motor can reach in power.
#define POWER                   20 //Power of motor

#define MOTOR_ONE_ENABLER        0  //pin 11(GPIO 17)
#define MOTOR_ONE_CONTROL        2  //pin 13(GPIO 27)
#define MOTOR_ONE_CONTROL_TWO    3  //pin 15(GPIO 22)

#define MOTOR_TWO_ENABLER        6  //pin 22(GPIO 25)
#define MOTOR_TWO_CONTROL        4  //pin 16(GPIO 23)
#define MOTOR_TWO_CONTROL_TWO    5  //pin 18(GPIO 24)

#define MOTOR_THREE_ENABLER      12 //pin 19(GPIO 10)
#define MOTOR_THREE_CONTROL      13 //pin 21(GPIO 9)
#define MOTOR_THREE_CONTROL_TWO  14 //pin 23(GPIO 11)

#define MOTOR_FOUR_ENABLER       26 //pin 32(GPIO 12)
#define MOTOR_FOUR_CONTROL       10 //pin 24(GPIO 8)
#define MOTOR_FOUR_CONTROL_TWO   11 //pin 26(GPIO 7)

#define FORWARD                  0  
#define BACKWARD                 1

#define MOTOR_ONE_F              motorMove(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, FORWARD, POWER) //makes motor one go forward.
#define MOTOR_TWO_F              motorMove(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, FORWARD, POWER) //makes motor two go forward.
#define MOTOR_THREE_F            motorMove(MOTOR_THREE_ENABLER, MOTOR_THREE_CONTROL, MOTOR_THREE_CONTROL_TWO, BACKWARD,POWER) //makes motor three go forward. //Motor 3 was assembled backwards
#define MOTOR_FOUR_F             motorMove(MOTOR_FOUR_ENABLER, MOTOR_FOUR_CONTROL, MOTOR_FOUR_CONTROL_TWO, FORWARD, POWER) //makes motor four go forward.

#define MOTOR_ONE_B              motorMove(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, BACKWARD,POWER) //makes motor one go backward.
#define MOTOR_TWO_B              motorMove(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, BACKWARD,POWER) //makes motor two go backward.
#define MOTOR_THREE_B            motorMove(MOTOR_THREE_ENABLER, MOTOR_THREE_CONTROL, MOTOR_THREE_CONTROL_TWO, FORWARD,POWER) //makes motor three go backward. //Motor 3 was assembled backwards
#define MOTOR_FOUR_B             motorMove(MOTOR_FOUR_ENABLER, MOTOR_FOUR_CONTROL, MOTOR_FOUR_CONTROL_TWO, BACKWARD,POWER) //makes motor four go backward.

#define MOTOR_ONE_S              motorStop(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO) //makes motor one stop.
#define MOTOR_TWO_S              motorStop(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO) //makes motor two stop.
#define MOTOR_THREE_S            motorStop(MOTOR_THREE_ENABLER, MOTOR_THREE_CONTROL, MOTOR_THREE_CONTROL_TWO) //makes motor three stop.
#define MOTOR_FOUR_S             motorStop(MOTOR_FOUR_ENABLER, MOTOR_FOUR_CONTROL, MOTOR_FOUR_CONTROL_TWO) //makes motor four stop.

//It sets up the motors so that they can be used by the program.
//Contributors:
void motorsSet(void);

//tells the motor enabler pin #, the pin #'s of the controllers, and the direction(BACKWARD or FORWARD)
//and makes the motor move to that direction.
//Contributors:
void motorMove(int enabler, int control, int control2, int direction, int power);

//takes the motor enabler pin # and the pin #'s of the controllers
//and makes the motor stop.
//Contributors:
void motorStop(int enabler, int control, int control2);

//Thread function that makes the motor go forward.
//the void pointer must point to either 1 or 2 to indicate the motor to control.
//returns NULL.
//Contributors:
void *motorToControlForward(void *ptr);

//This function stops all the motors.
//Contributors:
void motorsCleanUp(void);

//Adjusts the speed of the motors in the right(0) or left(1) side of the car
void adjustMotorsSpeed(int side);

//makes the move turn right
void moveRight();

//makes motor turn left
void moveLeft();

//makes motor run normally at power 20
void moveRegular();

//puts power of motors at 0
void stopMotors();

#endif
