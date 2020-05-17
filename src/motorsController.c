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

void decreaseMotorPowerToZero(void) {
    digitalWrite(MOTOR_FOUR_ENABLER, HIGH);
    digitalWrite(MOTOR_THREE_ENABLER, HIGH);
    digitalWrite(MOTOR_TWO_ENABLER, HIGH);
    digitalWrite(MOTOR_ONE_ENABLER, HIGH);

    for (int i = 20; i > MIN_INTENCITY; i -= 10) {
        softPwmWrite(MOTOR_FOUR_ENABLER, i);
        softPwmWrite(MOTOR_THREE_ENABLER, i);
        softPwmWrite(MOTOR_TWO_ENABLER, i);
        softPwmWrite(MOTOR_ONE_ENABLER, i);
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


void *motorToControlBackward(void *ptr){

    int motor;
    motor = *((int *) ptr);

    if (motor == 1) {
        MOTOR_ONE_B;
    } else if (motor == 2) {
        MOTOR_TWO_B; 
    } else if (motor == 3) {
        MOTOR_THREE_B;
    } else if (motor == 4) {
        MOTOR_FOUR_B;
    }

    return NULL;

}

void runMotors(int time){
  MOTOR_ONE_F;
  MOTOR_TWO_F;
  MOTOR_THREE_F;
  MOTOR_FOUR_F;

  delay(time);
  MOTOR_ONE_S;
  MOTOR_TWO_S;
  MOTOR_THREE_S;
  MOTOR_FOUR_S;

  delay(1);
  MOTOR_ONE_B;
  MOTOR_TWO_B;
  MOTOR_THREE_B;
  MOTOR_FOUR_B;
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

        softPwmWrite(MOTOR_FOUR_ENABLER, POWER+5);
        softPwmWrite(MOTOR_THREE_ENABLER, POWER-5);
        softPwmWrite(MOTOR_TWO_ENABLER, POWER-5);
        softPwmWrite(MOTOR_ONE_ENABLER, POWER+5);
    } else {
        digitalWrite(MOTOR_FOUR_ENABLER, HIGH);
        digitalWrite(MOTOR_THREE_ENABLER, HIGH);
        digitalWrite(MOTOR_TWO_ENABLER, HIGH);
        digitalWrite(MOTOR_ONE_ENABLER, HIGH);

        softPwmWrite(MOTOR_FOUR_ENABLER, POWER-5);
        softPwmWrite(MOTOR_THREE_ENABLER, POWER+5);
        softPwmWrite(MOTOR_TWO_ENABLER, POWER+5);
        softPwmWrite(MOTOR_ONE_ENABLER, POWER-5);
    }
}
