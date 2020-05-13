#include "speedSensorsController.h"

//This array contains the speed of each motor.
//Motor 1 at index 0, Motor 2 at index 1 and so on.
//*** Specify if you are measuring in cm/s or rad/s***

double MOTORS_SPEED[NUMBER_OF_MOTORS] = {ARRAY_INIT_VAL};
//this mutex is to help maintain order when having code in critical sections.
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;


void speedSensorSet(void) {
    wiringPiSetup();

    pinMode(SPEED_SENSOR_ONE_PIN, INPUT);
    pinMode(SPEED_SENSOR_TWO_PIN, INPUT);
    pinMode(SPEED_SENSOR_THREE_PIN, INPUT);
    pinMode(SPEED_SENSOR_FOUR_PIN, INPUT);
}

void writeSpeed(int motor, double speed) {
    
    MOTORS_SPEED[motor] = speed;
    
}

double readSpeed(int motor) {
    
    double speed;
    
    
    speed = MOTORS_SPEED[motor];
    
    
    return speed;

}

double calculateAngularSpeed(int totalPulses) {
    return (2.0 * PI * totalPulses * (WHEEL_DIAMETER / 2) ) / (TIME_TO_MEASURE * PULSES_PER_ROTATION);
}

double calculateLinearSpeed(double diameter, double angularSpeed) {
    return (diameter / 2) * angularSpeed;
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
    speed = calculateAngularSpeed(readPulses(pin));
    //speed = calculateLinearSpeed(WHEEL_DIAMETER, aSpeed);

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
