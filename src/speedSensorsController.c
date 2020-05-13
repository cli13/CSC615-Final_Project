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
    
    pthread_mutex_lock( &m );
    speed = MOTORS_SPEED[motor];
    pthread_mutex_unlock( &m );
    
    return speed;

}

double calculateAngularSpeed(int totalPulses, double time) {
    return (2.0 * PI * totalPulses) / (time * PULSES_PER_ROTATION);
}

double calculateLinearSpeed(double diameter, double angularSpeed) {
    return (diameter / 2) * angularSpeed;
}

int readPulses(double time, int pin) {
    int count = 0;
    double start = millis();
    double end = start + (1000 * time);

    printf("start: %f, end: %f\n", start, end);

    while (end > millis()) {

        if(digitalRead(pin)) {

            count++;
            while(digitalRead(pin)){}
        }

    }
    printf("Total count: %d\n", count);

    return count;
}

void *useSpeedSensor(void *ptr) {
    int pin;
    pin = *((int *) ptr);
    double aSpeed;
    double speed;
    
    while(1) {
    aSpeed = calculateAngularSpeed(readPulses(TIME_TO_MEASURE, pin), TIME_TO_MEASURE);
    speed = calculateLinearSpeed(WHEEL_DIAMETER, aSpeed);

    printf("The angular speed is: %f rad/s\n", aSpeed);
    printf("The linear speed is: %f cm/s\n", speed);

    if (pin == SPEED_SENSOR_ONE_PIN) {
        writeSpeed(0, speed);
    } else if(pin == SPEED_SENSOR_TWO_PIN) {
        writeSpeed(1, speed);
    } else if(pin == SPEED_SENSOR_THREE_PIN) {
        writeSpeed(2, speed);
    } else if (pin == SPEED_SENSOR_FOUR_PIN) {
        writeSpeed(3, speed);
    }

    }
    
    return NULL;
}

double averageSpeed(void) {

    double total = 0;

    total = MOTORS_SPEED[0] + MOTORS_SPEED[2];

    printf("Total speed added: %f\n", total);

    return total / NUMBER_OF_MOTORS;

}
