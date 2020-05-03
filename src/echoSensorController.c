#include "./echoSensorController.h"

void echoSensorSet(void){
    wiringPiSetup();
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);

    digitalWrite(TRIGGER_PIN, LOW);
    digitalWrite(ECHO_PIN, HIGH);
}

void calculateDistance(unsigned int time){
    distance = (double) (time) * (SPEED_OF_SOUND) / (double) 1000;
}

void prepareTrigger(void){
    digitalWrite(TRIGGER_PIN, HIGH);
    delay(1);
    digitalWrite(TRIGGER_PIN, LOW);
}

unsigned int getTime(void){
    unsigned int start, end;
    while(digitalRead(ECHO_PIN) == 0){}
	start = millis();
    while(digitalRead(ECHO_PIN) == 1){}
    end = millis();
    unsigned int delta = end - start;
    pritnf("start: %d", start);
    pritnf("end: %d", end);
    pritnf("delta: %d", delta);
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