#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "echoSensorController.h"
#include "speedSensorsController.h"
#include "lineSensorsController.h"
#include "motorsController.h"

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

void moveforward() {

    double timeToCrash = 100;   //in secs
    double safeTime = 1.2;      //in secs
    double distance = 100;
    double speed = 1;

    pthread_t t1, t2, t3, t4;
    int s1, s2, s3, s4, motor1 = 1, motor2 = 2, motor3 = 3, motor4 = 4;
    void *m1 = &motor1;
    void *m2 = &motor2;
    void *m3 = &motor3;
    void *m4 = &motor4;

    printf("initialize motors\n");
    if ((s1 = pthread_create(&t1, NULL, motorToControlForward, m1))) {
        printf("thread creation failed: %i\n", s1);
    }
    if ((s2 = pthread_create(&t2, NULL, motorToControlForward, m2))) {
        printf("thread creation failed: %i\n", s2);
    }
    if ((s3 = pthread_create(&t3, NULL, motorToControlForward, m3))) {
        printf("thread creation failed: %i\n", s3);
    }
    if ((s4 = pthread_create(&t4, NULL, motorToControlForward, m4))) {
        printf("thread creation failed: %i\n", s4);
    }

    printf("join motor threads.\n");
    pthread_join( t1, NULL);
    pthread_join( t2, NULL);
    pthread_join( t3, NULL);
    pthread_join( t4, NULL);
    
    while (timeToCrash > safeTime) {
        distance = readDistance();
        speed = averageSpeed();
        
        if (speed > 0 ) {
            timeToCrash = distance / speed;
        }
        printf("Distance: %f\tSpeed: %f\n", distance, speed);
        printf("time to crash: %f\n", timeToCrash);
    }

    decreaseMotorPowerToZero();
    cleanUp();
    
}

int main() {
    signal(SIGINT, cleanUp);

    setUp();

   // moveforward();
    while(1) {
        if (isObjectInFront()) {
            printf("Object in front.\n");
        } else {
            printf("No object.\n");
        }
    }
    printf("Finished.");
    
    return 0;
}
