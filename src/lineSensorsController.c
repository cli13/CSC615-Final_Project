#include "lineSensorsController.h"

int readLinePin(int readPin){
    return digitalRead(readPin);
}

void lineSensorsCleanUp(void) {
	
	digitalWrite(LINESENSOR_MIDDLE_PIN, LOW);
	digitalWrite(LINESENSOR_RIGHT_PIN, LOW);
    digitalWrite(LINESENSOR_LEFT_PIN, LOW);
	
}

void lineSensorSetup(void) {
	int rc;

	if ((rc = wiringPiSetup()) == -1) {
		printf("Fail to setup wiringPi\n");
		exit(1);
	}

	pinMode(LINESENSOR_MIDDLE_PIN, INPUT);
	pinMode(LINESENSOR_RIGHT_PIN, INPUT);
    pinMode(LINESENSOR_LEFT_PIN, INPUT);
}