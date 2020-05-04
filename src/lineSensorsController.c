#include "./lineSensorsController.h"

void lineSensorSetup(void){
    wiringPiSetup()
    pinMode(LINESENSOR_ONE_PIN, INPUT);
    pinMode(LINESENSOR_TWO_PIN, INPUT);
    pinMode(LINESENSOR_THREE_PIN, INPUT);
}

int readLinePin(int readPin){
    return digitalRead(readPin);
}

int main(void){
    printf("pin1: %d", readLinePin(LINESENSOR_ONE_PIN));
    printf("pin1: %d", readLinePin(LINESENSOR_TWO_PIN));
    printf("pin1: %d", readLinePin(LINESENSOR_THREE_PIN));
    return 0;
}