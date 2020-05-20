#include "motorsController.h"


void motorsSet(void){

    int rc;
    if ((rc = wiringPiSetup()) == -1) {
            perror("Fail to setup wiringPi\n");
            exit(1);
    }

    pinMode(MOTOR_ONE_CONTROL, OUTPUT);
    pinMode(MOTOR_ONE_CONTROL_TWO , OUTPUT);
    pinMode(MOTOR_ONE_ENABLER, OUTPUT);

    pinMode(MOTOR_TWO_CONTROL, OUTPUT);
    pinMode(MOTOR_TWO_CONTROL_TWO , OUTPUT);
    pinMode(MOTOR_ONE_ENABLER, OUTPUT);

    pinMode(MOTOR_THREE_CONTROL, OUTPUT);
    pinMode(MOTOR_THREE_CONTROL_TWO , OUTPUT);
    pinMode(MOTOR_THREE_ENABLER, OUTPUT);

    pinMode(MOTOR_FOUR_CONTROL, OUTPUT);
    pinMode(MOTOR_FOUR_CONTROL_TWO , OUTPUT);
    pinMode(MOTOR_FOUR_ENABLER, OUTPUT);


       if ((rc = softPwmCreate(MOTOR_ONE_ENABLER, MIN_INTENCITY, MAX_INTENCITY)) != 0) {
                     perror("Fail to creates a software controlled PWM pin\n");
             }
       if ((rc = softPwmCreate(MOTOR_TWO_ENABLER, MIN_INTENCITY, MAX_INTENCITY)) != 0) {
                     perror("Fail to creates a software controlled PWM pin\n");
             }

       if ((rc = softPwmCreate(MOTOR_THREE_ENABLER, MIN_INTENCITY, MAX_INTENCITY)) != 0) {
                     perror("Fail to creates a software controlled PWM pin\n");
             }
       if ((rc = softPwmCreate(MOTOR_FOUR_ENABLER, MIN_INTENCITY, MAX_INTENCITY)) != 0) {
                    perror("Fail to creates a software controlled PWM pin\n");
             }
}

void motorMove(int enabler, int control, int control2, int direction, int power){
    digitalWrite(enabler, HIGH);
    softPwmWrite(enabler, power);

    if (direction) {
        digitalWrite(control2, LOW); // turn off the motorPin2
        digitalWrite(control, HIGH); // turn on the motorPin1
                
    } else {

        digitalWrite(control, LOW); // turn off the motorPin1
        digitalWrite(control2, HIGH); // turn on the motorPin2
    }
    
}

void motorStop(int enabler, int control, int control2){

    digitalWrite(enabler, LOW);
    digitalWrite(control, LOW);
    digitalWrite(control2, LOW);
}


void *motorToControlForward(void *ptr){

    int motor;
    motor = *((int *) ptr);
    
    if (motor == 1) {
        MOTOR_ONE_F;
    } else if (motor == 2) {
        MOTOR_TWO_F; 
    } else if (motor == 3) {
        MOTOR_THREE_F;
    } else if (motor == 4) {
        MOTOR_FOUR_F;
    }

    return NULL;

}

void motorsCleanUp(void){
    MOTOR_ONE_S;
    MOTOR_TWO_S;
    MOTOR_THREE_S;
    MOTOR_FOUR_S;
}


void adjustMotorsSpeed(int side) {

    if (side) {
        digitalWrite(MOTOR_FOUR_ENABLER, HIGH);
        digitalWrite(MOTOR_THREE_ENABLER, HIGH);
        digitalWrite(MOTOR_TWO_ENABLER, HIGH);
        digitalWrite(MOTOR_ONE_ENABLER, HIGH);

        softPwmWrite(MOTOR_FOUR_ENABLER, POWER+12);
        softPwmWrite(MOTOR_THREE_ENABLER, POWER-12);
        softPwmWrite(MOTOR_TWO_ENABLER, POWER-12);
        softPwmWrite(MOTOR_ONE_ENABLER, POWER+12);
    } else {
        digitalWrite(MOTOR_FOUR_ENABLER, HIGH);
        digitalWrite(MOTOR_THREE_ENABLER, HIGH);
        digitalWrite(MOTOR_TWO_ENABLER, HIGH);
        digitalWrite(MOTOR_ONE_ENABLER, HIGH);

        softPwmWrite(MOTOR_FOUR_ENABLER, POWER-12);
        softPwmWrite(MOTOR_THREE_ENABLER, POWER+12);
        softPwmWrite(MOTOR_TWO_ENABLER, POWER+12);
        softPwmWrite(MOTOR_ONE_ENABLER, POWER-12);
    }
}


void moveLeft() {
    digitalWrite(MOTOR_FOUR_ENABLER, HIGH);
    digitalWrite(MOTOR_THREE_ENABLER, HIGH);
    digitalWrite(MOTOR_TWO_ENABLER, HIGH);
    digitalWrite(MOTOR_ONE_ENABLER, HIGH);

    softPwmWrite(MOTOR_FOUR_ENABLER, 0);
    softPwmWrite(MOTOR_THREE_ENABLER, 0);
    softPwmWrite(MOTOR_TWO_ENABLER, POWER+40);
    softPwmWrite(MOTOR_ONE_ENABLER, 0);
}


void moveRight() {
    digitalWrite(MOTOR_FOUR_ENABLER, HIGH);
    digitalWrite(MOTOR_THREE_ENABLER, HIGH);
    digitalWrite(MOTOR_TWO_ENABLER, HIGH);
    digitalWrite(MOTOR_ONE_ENABLER, HIGH);

    softPwmWrite(MOTOR_FOUR_ENABLER, 0);
    softPwmWrite(MOTOR_THREE_ENABLER, 0);
    softPwmWrite(MOTOR_TWO_ENABLER, 0);
    softPwmWrite(MOTOR_ONE_ENABLER, POWER+50);
}

void moveRegular() {
    digitalWrite(MOTOR_FOUR_ENABLER, HIGH);
    digitalWrite(MOTOR_THREE_ENABLER, HIGH);
    digitalWrite(MOTOR_TWO_ENABLER, HIGH);
    digitalWrite(MOTOR_ONE_ENABLER, HIGH);

    softPwmWrite(MOTOR_FOUR_ENABLER, POWER);
    softPwmWrite(MOTOR_THREE_ENABLER, POWER);
    softPwmWrite(MOTOR_TWO_ENABLER, POWER);
    softPwmWrite(MOTOR_ONE_ENABLER, POWER);
}

void stopMotors() {
    digitalWrite(MOTOR_FOUR_ENABLER, HIGH);
    digitalWrite(MOTOR_THREE_ENABLER, HIGH);
    digitalWrite(MOTOR_TWO_ENABLER, HIGH);
    digitalWrite(MOTOR_ONE_ENABLER, HIGH);

    softPwmWrite(MOTOR_FOUR_ENABLER, 0);
    softPwmWrite(MOTOR_THREE_ENABLER, 0);
    softPwmWrite(MOTOR_TWO_ENABLER, 0);
    softPwmWrite(MOTOR_ONE_ENABLER, 0);
}
