#include "../headers/echoSensorController.h"

double ECHO_DISTANCE = 0;
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
    delay(1);
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
    printf("delta: %f\n", delta);
    return delta;
}

void *useEchoSensor(void *ptr) {
    pthread_mutex_lock( &mu );
    ECHO_DISTANCE = calculateDistance(getTime());
    pthread_mutex_unlock( &mu );
}

double readDistance(void) {
    double distance;
    pthread_mutex_lock(&mu);
    distance = ECHO_DISTANCE;
    pthread_mutex_unlock(&mu);
    return distance;
}

void displayDistance(void){
    printf("Distance: %.2f cm\n", ECHO_DISTANCE);
}

void echoSensorCleanUp(void){
    digitalWrite(TRIGGER_PIN, LOW);
    digitalWrite(ECHO_PIN, LOW);
}