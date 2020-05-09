#include "../headers/lineSensorsController.h"

void lineSensorSetup(void){
    wiringPiSetup();
    pinMode(LINESENSOR_ONE_PIN, INPUT);
    pinMode(LINESENSOR_TWO_PIN, INPUT);
    pinMode(LINESENSOR_THREE_PIN, INPUT);
}

int readLinePin(int readPin){
    return digitalRead(readPin);
}
