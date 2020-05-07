#include "./motorsController.h"


int main(int argc, char** argv) {

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

void motorMove(int enabler, int control, int control2, int direction){
  digitalWrite(enabler, HIGH);
        softPwmWrite(enabler, 100);
        if (direction == FORWARD) {
                digitalWrite(control2, LOW); // turn off the motorPin2
                digitalWrite(control, HIGH); // turn on the motorPin1
                return;
        }

        digitalWrite(control, LOW); // turn off the motorPin1
        digitalWrite(control2, HIGH); // turn on the motorPin2
}

void motorStop(int enabler, int control, int control2){

    digitalWrite(enabler, LOW);
    digitalWrite(control, LOW);
    digitalWrite(control2, LOW);
}


void *motorToControlForward(void *ptr){


}


void *motorToControlBackward(void *ptr){


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
  MOTOR_ONE_S;

  delay(1);
  MOTOR_ONE_B;
  MOTOR_TWO_B;
  MOTOR_THREE_B;
  MOTOR_FOUR_B;
}

void motorsCleanUp(void){
digitalWrite(MOTOR_ONE_CONTROL, LOW);
digitalWrite(MOTOR_ONE_CONTROL_TWO , LOW);
digitalWrite(MOTOR_ONE_ENABLER, LOW);

digitalWrite(MOTOR_TWO_CONTROL, LOW);
digitalWrite(MOTOR_TWO_CONTROL_TWO , LOW);
digitalWrite(MOTOR_ONE_ENABLER, LOW);

digitalWrite(MOTOR_THREE_CONTROL, LOW);
digitalWrite(MOTOR_THREE_CONTROL_TWO , LOW);
digitalWrite(MOTOR_THREE_ENABLER, LOW);

digitalWrite(MOTOR_FOUR_CONTROL, LOW);
digitalWrite(MOTOR_FOUR_CONTROL_TWO , LOW);
digitalWrite(MOTOR_FOUR_ENABLER, LOW);
}

}
