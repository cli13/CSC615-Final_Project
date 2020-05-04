/**************************************************************
* Class: CSC-615-01 Spring 2020
* Project: <Final Project>
*
* File: <lineSensorsController.h>
*
* Description: This header files defines the functions to be
*              be implemented in lineSensorsController.c
*              All the included libraries are listed here.
*              This file also has all the macros being used to make code more readable.
**************************************************************/
#ifndef LINESENSORSCONTROLLER_H_   
#define LINESENSORSCONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <wiringPi.h>

#define LINESENSOR_ONE_PIN       24  //pin 35(GPIO 19)
#define LINESENSOR_TWO_PIN       25  //pin 37(GPIO 26)
#define LINESENSOR_THREE_PIN     7   //pin 7 (GPIO  4)

//function signatures and documentation to be added later

//This function sets all the pins off for the line sensors.
//Contributors:
void lineSensorsCleanUp(void);

//This function sets up all the pins for the linesensors that are being used.
void lineSensorSetup(void);


//This function reads a linepin and return the pin's output
int readLinePin(int linePin)

#endif