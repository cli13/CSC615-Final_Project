# Class: CSC-615-01 Spring 2020
# Project: <Final Project>
# File: makefile
CC=gcc
CFLAGS= -g -Wall -I.
DEPS = carController.h motorsController.h speedSensorsController.h lineSensorsController.h echoSensorController.h
OBJ = finalassignmnet.o carController.o motorsController.o speedSensorsController.o lineSensorsController.o echoSensorController.o

%.o: %.c $(DEPS)
	sudo $(CC) -c -o $@ $< $(CFLAGS)

finalassignmnet: $(OBJ)
	sudo $(CC) -o $@ $^ $(CFLAGS) -lwiringPi -lpthread