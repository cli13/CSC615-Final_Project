#include "./echoSensorController.h"

void echoSensorSet(void){
    wiringPiSetup();
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);

    digitalWrite(TRIGGER_PIN, LOW);
    digitalWrite(ECHO_PIN, HIGH);
}

void calculateDistance(unsigned int time){
    distance = (time * 1000) * (SPEED_OF_SOUND / 2);
}

void prepareTrigger(void){
    digitalWrite(TRIGGER_PIN, HIGH);
    delay(1);
    digitalWrite(TRIGGER_PIN, LOW);
}

unsigned int getTime(void){
    while(digitalRead(ECHO_PIN) == 0){
        unsigned int start = millis();
    }
    while(digitalRead(ECHO_PIN) == 1){
        unsigned int end = millis();
    }
    unsigned int delta = end - start;

    return delta;
}

float getDistance(){
    return distance;
}

void displayDistance(){
    printf("Distance: "+ getDistance() + "cm\n")
}

//testing sensor functions
int main(void){
    echoSensorSet();
    prepareTrigger();
    calculateDistance(getTime());
    displayDistance();
}