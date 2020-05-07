#include "./carController.h"

void cleanUp() {
    echoSensorCleanUp();
    lineSensorsCleanUp();
    motorsCleanUp();
    speedSensorsCleanUp();
}

void moveforward(){
    
}

int main(void) {
    motorsSetup();
    LineSensorSetup();
    while(1){
        if(readLinePin(LINESENSOR_ONE_PIN) == 1){
            motorMove(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO, FOWARD);
            motorMove(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO, FOWARD);
            motorMove(MOTOR_THREE_ENABLER, MOTOR_THREE_CONTROL, MOTOR_THREE_CONTROL_TWO, FOWARD);
            motorMove(MOTOR_FOUR_ENABLER, MOTOR_FOUR_CONTROL, MOTOR_FOUR_CONTROL_TWO, FOWARD);
        }else{
            motorStop(MOTOR_ONE_ENABLER, MOTOR_ONE_CONTROL, MOTOR_ONE_CONTROL_TWO);
            motorStop(MOTOR_TWO_ENABLER, MOTOR_TWO_CONTROL, MOTOR_TWO_CONTROL_TWO);
            motorStop(MOTOR_THREE_ENABLER, MOTOR_THREE_CONTROL, MOTOR_THREE_CONTROL_TWO);
            motorStop(MOTOR_FOUR_ENABLER, MOTOR_FOUR_CONTROL, MOTOR_FOUR_CONTROL_TWO);
        }
    }
}