/**************************************************************
* Class: CSC-615-01 Spring 2020
* Project: <Final Project>
*
* File: <carController.h>
*
* Description: This header files defines the functions to be
*              be implemented in carController.c
*              All the included libraries are listed here.
*              This file also has all the macros being used to make code more readable.
**************************************************************/
#ifndef CARCONTROLLER_H_   
#define CARCONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "echoSensorController.h"
#include "speedSensorsController.h"
#include "lineSensorsController.h"
#include "motorsController.h"

//function responsible to clean everything properly when a ctrl + c signal is issued.
//Contributors: Osbaldo Martinez
void cleanUp();

//set all four motors on the car to move in one direction
void movefoward(void);

#endif