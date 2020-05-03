#include "./echoSensorController.h"

void echoSensorSet(void){
    wiringPiSetup();
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);

    digitalWrite(TRIGGER_PIN, LOW);
    digitalWrite(ECHO_PIN, HIGH);
}

void calculateDistance(double time){
    distance = (time) * (SPEED_OF_SOUND);
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

double getDistance(){
    return distance;
}

void displayDistance(){
    printf("Distance: %.2f cm\n", getDistance());
}

void echoSensorCleanUp(){
    digitalWrite(TRIGGER_PIN, LOW);
    digitalWrite(ECHO_PIN, LOW);
}

//testing sensor functions
int main(void){
    echoSensorSet();
    prepareTrigger();
    calculateDistance(getTime());
    displayDistance();
}