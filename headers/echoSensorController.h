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
#define SPEED_OF_SOUND         34300.0  //in centimeters per second

//This function sets the pins being used by the echo sensor.
//Contributors:
void  echoSensorSet(void);

//Takes a float variable that indicates the time it
//took the echo to come back.
//It returns a float with distance measured by the the echo.
//Contributors:
float calculateDistance(float time);

//This function prepares the trigger to send out the echo.
//Contributors:
void  prepareTrigger(void);

//This function returns the time as a float it took for the echo to
//come back.
//Contributors:
float getTime(void);

//This function returns a float with the distance.
//Contributors:
float getDistance(void);

//This function displays the distance that was calculated by using the echo.
//Contributors:
void  displayDistance(void);

//This function sets all the pins off for the echo sensor.
//Contributors:
void echoSensorCleanUp(void);

#endif