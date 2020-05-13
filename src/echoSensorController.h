/**************************************************************
* Class: CSC-615-01 Spring 2020
* Project: <Final Project>
*
* File: <echoSensorController.h>
*
* Description: This header files defines the functions to be
*              be implemented in echoSensorController.c
*              All the included libraries are listed here.
*              This file also has all the macros being used to make code more readable.
**************************************************************/
#ifndef ECHOSENSORCONTROLLER_H_   
#define ECHOSENSORCONTROLLER_H_

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <wiringPi.h>

#define ECHO_PIN               22       //pin 31(GPIO 6)
#define TRIGGER_PIN            21       //pin 29(GPIO 5)
#define SPEED_OF_SOUND         34300.0  //speed of sound in cm

//This function sets the pins being used by the echo sensor.
//Contributors:
void  echoSensorSet(void);

//Takes a double variable that indicates the times in milliseconds
//took the echo to come back.
//Contributors:
double calculateDistance(double time);

//This function prepares the trigger to send out the echo.
//Contributors:
void  prepareTrigger(void);

//This function returns the time in seconds it took for the echo to
//come back. Using time.h's clock() function 
//This return time in milliseconds 
//Contributors:
double getTime(void);

//This function uses the echo sensor to calculate distance.
//Contributors:
void *useEchoSensor(void *ptr);

//Returns the distance in the ECHO_DISTANCE variable.
double readDistance(void);

//This function displays the distance that was calculated by using the echo.
//Contributors:
void  displayDistance(void);

//This function sets all the pins off for the echo sensor.
//Contributors:
void echoSensorCleanUp(void);

#endif
