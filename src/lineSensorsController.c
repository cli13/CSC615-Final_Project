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

bool isOnLine(int sensorPin) {

	return (digitalRead(sensorPin) == HIGH);

}


/*
// ************** Test code ********************
#define LED_PIN 4 // PIN 16, GPIO23

int main(int argc, char** argv) {
	int rc;

	if ((rc = wiringPiSetup()) == -1) {
		perror("Fail to setup wiringPi\n");
		exit(1);
	}

	if ((rc = wiringPiI2CSetup()) == -1) {
		perror("Fail to setup wiringPiI2C\n");
		exit(1);
	}

	// set the LED_PIN to be output, and LINESENSOR_ONE_PIN to be input
	pinMode(LED_PIN, OUTPUT);
	pinMode(LINESENSOR_ONE_PIN, INPUT);

	// turn off the LED_PIN, and LINESENSOR_ONE_PIN
	digitalWrite(LED_PIN, LOW);
	digitalWrite(LINESENSOR_ONE_PIN, LOW);

	// turn off the LED_PIN, and LINESENSOR_ONE_PIN
	wiringPiI2CWrite(LED_PIN, LOW);
	wiringPiI2CWrite(LINESENSOR_ONE_PIN, LOW);

	long startTime, endTime;
	while (1) {
		startTime = millis();
		if (digitalRead(LINESENSOR_ONE_PIN) == LOW) {
			digitalWrite(LED_PIN, LOW); // turn off the LED_PIN
			delay(200);
		} else {
			printf("Using digitalRead, LINESENSOR_ONE_PIN is High\n");
			digitalWrite(LED_PIN, HIGH); // turn on the LED_PIN
			delay(200);
		}
		endTime = millis();
		printf("****** DigitalRead run time: %l\n", endTime - startTime);

		startTime = millis();
		if (wiringPiI2CRead(LINESENSOR_ONE_PIN) == LOW) {
			wiringPiI2CWrite(LED_PIN, LOW); // turn off the LED_PIN
			delay(200);
		} else {
			printf("Using wiringPiI2CRead, LINESENSOR_ONE_PIN is High\n");
			wiringPiI2CWrite(LED_PIN, HIGH); // turn on the LED_PIN
			delay(200);
		}
		endTime = millis();
		printf("****** I2C run time: %l\n", endTime - startTime);
	}

	return 0;
}
// ******************** end ************************ 
//*/


