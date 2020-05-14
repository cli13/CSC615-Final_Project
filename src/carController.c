#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "echoSensorController.h"
#include "speedSensorsController.h"
#include "lineSensorsController.h"
#include "motorsController.h"

double TIME_TO_CRASH = 100;   //in secs
double SAFE_TIME = 2.7;      //in secs

void cleanUp() {
    echoSensorCleanUp();
    lineSensorsCleanUp();
    motorsCleanUp();
    exit(0);
}


void setUp() {
    motorsSet();
    lineSensorSetup();
    echoSensorSet();
    speedSensorSet();
} 

void reposition(int motor) {
    if (motor == 1) {
        motorMove(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, FORWARD, 100); 
    } else {
        motorMove(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, FORWARD, 100); 
    }
    //motorMove(MOTOR_THREE_ENABLER, MOTOR_THREE_CONTROL, MOTOR_THREE_CONTROL_TWO, BACKWARD,30); 
   // motorMove(MOTOR_FOUR_ENABLER, MOTOR_FOUR_CONTROL, MOTOR_FOUR_CONTROL_TWO, FORWARD, 30);
}

void moveBack(pthread_t t1, pthread_t t2, pthread_t t3, pthread_t t4, void *m1, void *m2, void *m3, void *m4) {

    int s1, s2, s3, s4;

    if ((s1 = pthread_create(&t1, NULL, motorToControlForward, m1))) {
        printf("thread creation failed: %d\n", s1);
    }
    if ((s2 = pthread_create(&t2, NULL, motorToControlForward, m2))) {
        printf("thread creation failed: %d\n", s2);
    }
    if ((s3 = pthread_create(&t3, NULL, motorToControlForward, m3))) {
        printf("thread creation failed: %d\n", s3);
    }
    if ((s4 = pthread_create(&t4, NULL, motorToControlForward, m4))) {
        printf("thread creation failed: %d\n", s4);
    }

    printf("join motor threads.\n");
    pthread_join( t1, NULL);
    pthread_join( t2, NULL);
    pthread_join( t3, NULL);
    pthread_join( t4, NULL);

}

//calculates crash time in parallel
void *calculateCrashTime(void *ptr) {

    double speed;
    double distance;
    pthread_t th1, th2, th3, th4;
    int motor1 = 1, motor2 = 2, motor3 = 3, motor4 = 4;
    void *m1 = &motor1;
    void *m2 = &motor2;
    void *m3 = &motor3;
    void *m4 = &motor4;

    while (1) {

	if(isOnLine(LINESENSOR_ONE_PIN)) {
		
        distance = readDistance();
        speed    = averageSpeed();
        
        if (speed > 0) {
            TIME_TO_CRASH = distance / speed;
        }

        if(TIME_TO_CRASH < SAFE_TIME) {
            motorsCleanUp();
	    delay(10);
            reposition(1);
            delay(2000);
            motorsCleanUp();
            moveBack(th1, th2, th3, th4, m1, m2, m3, m4);
	    motorsCleanUp();
	    delay(10);
            reposition(2);
            delay(2000);
            motorsCleanUp();
            moveBack(th1, th2, th3, th4, m1, m2, m3, m4);
	    motorsCleanUp();
	    delay(10);
            reposition(1);
            delay(1000);
	    motorsCleanUp();
            moveBack(th1, th2, th3, th4, m1, m2, m3, m4);
        }
	}
    }

}

void *objectInFront(void *ptr) {

    while(1){}
    //while (!isObjectInFront()){}
    decreaseMotorPowerToZero();
    cleanUp();

}

void moveforward() {

    pthread_t t1, t2, t3, t4, t5, t6, t7, t8;
    int s1, s2, s3, s4, motor1 = 1, motor2 = 2, motor3 = 3, motor4 = 4;
    void *m1 = &motor1;
    void *m2 = &motor2;
    void *m3 = &motor3;
    void *m4 = &motor4;
    int sp1 = SPEED_SENSOR_THREE_PIN, sp2 = SPEED_SENSOR_ONE_PIN, s5, s6, s7, s8;
    void *sd1 = &sp1;
    void *sd2 = &sp2;

    printf("initialize motors\n");
    if ((s1 = pthread_create(&t1, NULL, motorToControlForward, m1))) {
        printf("thread creation failed: %d\n", s1);
    }
    if ((s2 = pthread_create(&t2, NULL, motorToControlForward, m2))) {
        printf("thread creation failed: %d\n", s2);
    }
    if ((s3 = pthread_create(&t3, NULL, motorToControlForward, m3))) {
        printf("thread creation failed: %d\n", s3);
    }
    if ((s4 = pthread_create(&t4, NULL, motorToControlForward, m4))) {
        printf("thread creation failed: %d\n", s4);
    }

    printf("join motor threads.\n");
    pthread_join( t1, NULL);
    pthread_join( t2, NULL);
    pthread_join( t3, NULL);
    pthread_join( t4, NULL);
    
        
    if ((s5 = pthread_create(&t5, NULL, useSpeedSensor, sd1))) {
        printf("thread creation failed: %i\n", s5);
    }
    if ((s6 = pthread_create(&t6, NULL, useSpeedSensor, sd2))) {
        printf("thread creation failed: %i\n", s6);
    }

    if ((s7 = pthread_create(&t7, NULL, calculateCrashTime, NULL))) {
        printf("thread creation failed: %i\n", s7);
    }

    if ((s8 = pthread_create(&t8, NULL, objectInFront, NULL))) {
        printf("thread creation failed: %i\n", s8);
    }

   while(1) {} 
}

int main() {
    signal(SIGINT, cleanUp);

    setUp();

    moveforward();
    
    cleanUp();
    
    return 0;
}
