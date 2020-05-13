#include "echoSensorController.h"

pthread_mutex_t mu = PTHREAD_MUTEX_INITIALIZER;

void echoSensorSet(void){
    wiringPiSetup();
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);

    digitalWrite(TRIGGER_PIN, LOW);
    digitalWrite(ECHO_PIN, HIGH);
}

double calculateDistance(double time){
    return ((time) * (SPEED_OF_SOUND)) / 2.0;
}

void prepareTrigger(void){
    digitalWrite(TRIGGER_PIN, HIGH);
    delay(10);
    digitalWrite(TRIGGER_PIN, LOW);
}

double getTime(void){
    clock_t start, end;
    double delta = 0.0;
    while(digitalRead(ECHO_PIN) == 0){}
	start = clock();
    while(digitalRead(ECHO_PIN) == 1){}
    end = clock();
    delta = (double) (end - start) / CLOCKS_PER_SEC;
    return delta;
}

void *useEchoSensor(void *ptr) {
    printf("Using echo sensor\n");
    while(1) {
        prepareTrigger();
        printf("Echo distance: %f\n", calculateDistance(getTime()));
    }
}

double readDistance(void) {
    double distance;
    prepareTrigger();
    distance = calculateDistance(getTime());
    return distance;
}

void displayDistance(void){
    prepareTrigger();
    printf("Distance: %.2f cm\n", calculateDistance(getTime()));
}

void echoSensorCleanUp(void){
    digitalWrite(TRIGGER_PIN, LOW);
    digitalWrite(ECHO_PIN, LOW);
}
