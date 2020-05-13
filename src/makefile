# Class: CSC-615-01 Spring 2020
# Project: <Final Project>
# File: makefile
CC=gcc
CFLAGS= -g -I.
DEPS = motorsController.h speedSensorsController.h lineSensorsController.h echoSensorController.h
OBJ = carController.o motorsController.o speedSensorsController.o lineSensorsController.o echoSensorController.o

%.o: %.c $(DEPS)
	sudo $(CC) -c -o $@ $< $(CFLAGS)

finalassignment: $(OBJ)
	sudo $(CC) -o $@ $^ $(CFLAGS) -lwiringPi -lpthread
