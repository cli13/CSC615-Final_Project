#include "speedSensorsController.h"

//This array contains the speed of each motor.
//Motor 1 at index 0, Motor 2 at index 1 and so on.
volatile double MOTORS_SPEED[NUMBER_OF_MOTORS] = {ARRAY_INIT_VAL};

void speedSensorSet(void) {
    wiringPiSetup();

    pinMode(SPEED_SENSOR_ONE_PIN, INPUT);
    
    pinMode(SPEED_SENSOR_THREE_PIN, INPUT);
    
}

double calculateSpeed(int totalPulses) {
    return (2.0 * PI * totalPulses * (WHEEL_DIAMETER / 2) ) / (TIME_TO_MEASURE * PULSES_PER_ROTATION);
}

int readPulses(int pin) {
    int count = 0;
    double start = millis();
    double end = start + (1000 * TIME_TO_MEASURE);

    while (end > millis()) {

        if(digitalRead(pin)) {

            count++;
            while(digitalRead(pin)){}
        }

    }

    return count;
}

void *useSpeedSensor(void *ptr) {
    int pin;
    pin = *((int *) ptr);
    double aSpeed;
    double speed;
    
    while(1) {
    speed = calculateSpeed(readPulses(pin));

    if (pin == SPEED_SENSOR_ONE_PIN) {
        MOTORS_SPEED[0] = speed;
    } else if(pin == SPEED_SENSOR_THREE_PIN) {
        MOTORS_SPEED[2] = speed;
    }

    }
    
    return NULL;
}

double averageSpeed(void) {

    double total = 0;

    total = MOTORS_SPEED[0] + MOTORS_SPEED[2];

    return total / NUMBER_OF_MOTORS;

}
