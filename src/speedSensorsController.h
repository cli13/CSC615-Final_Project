/**************************************************************
* Class: CSC-615-01 Spring 2020
* Project: <Final Project>
*
* File: <speedSensorsController.h>
*
* Description: This header files defines the functions to be
*              be implemented in speedSensorsController.c
*              All the included libraries are listed here.
*              This file also has all the macros being used to make code more readable.
**************************************************************/
#ifndef SPEEDSENSORSCONTROLLER_H_   
#define SPEEDSENSORSCONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <wiringPi.h>

#define PI                      3.14159265358979323846  //the value of pi
#define NUMBER_OF_MOTORS        2                       //This defines the number of motors being analized by speed encored.
#define PULSES_PER_ROTATION     20                      //The number of holes in the wheel encoder. The speed sensor reads each hole as a pulse.

#define SPEED_SENSOR_ONE_PIN    27                      //pin 36(GPIO 16)
#define SPEED_SENSOR_THREE_PIN  29                      //pin 40(GPIO 21)

#define TIME_TO_MEASURE         0.35                     //Time frame used to measure pulses.
#define ARRAY_INIT_VAL          0.0                     //Initial value for array elements.
#define WHEEL_DIAMETER          6.0                     //in centimeters.

//It sets up the pins needed for the speed sensor. 
//Contributors:
void speedSensorSet(void);

//reads the pulses that the speed sensor sees in the time frame specified. It returns the pulses that were counted.
//Contributors:
int readPulses(int pin);

//calculates and returns the speed of the wheel.
//Contributors:
double calculateSpeed(int totalPulses);

//Function to be used in threads to display the speed read by the speed sensor.
//Contributors:
void *useSpeedSensor(void *ptr);

//This function returns a double with the average speed of the motors.
double averageSpeed(void);

#endif
