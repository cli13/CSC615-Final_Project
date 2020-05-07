#include "./lineSensorsController.h"

void lineSensorSetup(void){
    wiringPiSetup();
    pinMode(LINESENSOR_ONE_PIN, INPUT);
    pinMode(LINESENSOR_TWO_PIN, INPUT);
    pinMode(LINESENSOR_THREE_PIN, INPUT);
}

int readLinePin(int readPin){
    return digitalRead(readPin);
}

int main(void){
    lineSensorSetup();
    while(1){
    printf("pin1: %d\n", readLinePin(LINESENSOR_ONE_PIN));
    printf("pin2: %d\n", readLinePin(LINESENSOR_TWO_PIN));
    printf("pin3: %d\n", readLinePin(LINESENSOR_THREE_PIN));
    delay(1000);
    }
    return 0;
}