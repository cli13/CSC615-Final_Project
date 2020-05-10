#include "../headers/carController.h"

void cleanUp() {
    echoSensorCleanUp(void);
    lineSensorsCleanUp(void);
    motorsCleanUp(void);
}


void setUp() {
    motorsSet(void);
    lineSensorSetup(void);
    echoSensorSet(void);
    speedSensorSet(void);
} 

bool moveforward(void) {

    double timeToCrash = 100; //in secs
    double safeTime = 2;      //in secs
    double distance = 100;
    double speed = 1;
    pthread_t t1, t2, t3, t4, t5, t6, t7, t8, t9;
    int s1, s2, s3, s4, s5, s6, s7, s8, s9, motor1 = 1, motor2 = 2, motor3 = 3, motor4 = 4;
    void *m1 = &motor1;
    void *m2 = &motor2;
    void *m3 = &motor3;
    void *m4 = &motor4;
    void *sp1 = &SPEED_SENSOR_ONE_PIN;
    void *sp2 = &SPEED_SENSOR_TWO_PIN;
    void *sp3 = &SPEED_SENSOR_THREE_PIN;
    void *sp4 = &SPEED_SENSOR_FOUR_PIN;

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

        if ((s9 = pthread_create(&t9, NULL, useEchoSensor, NULL))) {
            printf("thread creation failed: %i\n", s9);
        }

        if ((s5 = pthread_create(&t5, NULL, useSpeedSensor, sp1))) {
            printf("thread creation failed: %i\n", s5);
        }
        if ((s6 = pthread_create(&t6, NULL, useSpeedSensor, sp2))) {
            printf("thread creation failed: %i\n", s6);
        }
        if ((s7 = pthread_create(&t7, NULL, useSpeedSensor, sp3))) {
            printf("thread creation failed: %i\n", s7);
        }
        if ((s8 = pthread_create(&t8, NULL, useSpeedSensor, sp4))) {
            printf("thread creation failed: %i\n", s8);
        }

        pthread_join( t5, NULL);
        pthread_join( t6, NULL);
        pthread_join( t7, NULL);
        pthread_join( t8, NULL);
        pthread_join( t9, NULL);

        distance = readDistance();
        speed = averageSpeed();

        timeToCrash = distance / speed;

    }

    decreaseMotorPowerToZero();

    MOTOR_FOUR_S;
    MOTOR_THREE_S;
    MOTOR_TWO_S;
    MOTOR_ONE_S;
    
    return true;
}

int main(void) {
    signal(SIGINT, cleanUp);

    setUp();

    bool x = moveforward();

    printf("Finished.")
}