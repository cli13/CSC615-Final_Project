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

#define PI                    3.14159265358979323846  //the value of pi
#define NUMBER_OF_MOTORS      2                       //This defines the number of motors being analized by speed encored.
#define PULSES_PER_ROTATION   20                      //The number of holes in the wheel encoder. The speed sensor reads each hole as a pulse.
#define SPEED_SENSOR_PIN      27                      //pin 36(GPIO 16)
#define SPEED_SENSOR_TWO_PIN  28                      //pin 38(GPIO 20)
#define TIME_TO_MEASURE       1.0                     //Time frame used to measure pulses.
#define ARRAY_INIT_VAL        0                       //Initial value for array elements.
#define ENCODER_DIAMETER      2.5                     //in centimeters.

//It sets up the pins needed for the speed sensor. 
//Contributors:
void speedSensorSet(void);

//reads the pulses that the speed sensor sees in the time frame specified. It returns the pulses that were counted.
//Contributors:
int readPulses(double time);

//calculates and returns angular speed using formula omega = (2*PI*NumberOfPulses) / (Time * PulsesPerRotation). Speed in radians per second.
//Contributors:
double calculateAngularSpeed(int totalPulses, double time);

//calculates and returns linear speed using formula v = ωr. Speed in meters per second.
//Contributors:
double calculateLinearSpeed(double diameter, double angularSpeed);

//It writes the speed to the array containing the speeds of each motor.
//Contributors:
void writeSpeed(int motor, double speed);

//It reads the speed of the array containing the speeds of each motor.
//Contributors:
double readSpeed(int motor);

//Function to be used in threads to display the speed read by the speed sensor.
//Contributors:
void *useSpeedSensor(void *ptr);

//This function sets all the pins off for the speed sensors.
//Contributors:
void speedSensorsCleanUp(void);

#endif
