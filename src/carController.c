#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "echoSensorController.h"
#include "speedSensorsController.h"
#include "lineSensorsController.h"
#include "motorsController.h"

double TIME_TO_CRASH = 100;   //in secs
double SAFE_TIME = 2.5;      //in secs

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

//calculates crash time in parallel
void *calculateCrashTime(void *ptr) {

    double speed;
    double distance;

    while (TIME_TO_CRASH > SAFE_TIME) {

        distance = readDistance();
        speed    = averageSpeed();
        
        if (speed > 0) {
            TIME_TO_CRASH = distance / speed;
        }
        
        printf("Distance: %f\tSpeed: %f\n", distance, speed);
        printf("time to crash: %f\n", TIME_TO_CRASH);
    }

    decreaseMotorPowerToZero();

    printf("Distance to object: %f\n", readDistance());

    cleanUp();
}

void *objectInFront(void *ptr) {

    while (!isObjectInFront()){}
    decreaseMotorPowerToZero();
    printf("Distance to object: %f\n", readDistance());
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
    
    printf("Finished.");
    
    return 0;
}
