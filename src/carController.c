#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "echoSensorController.h"
#include "speedSensorsController.h"
#include "lineSensorsController.h"
#include "motorsController.h"

bool OBSTACLE_AVOIDANCE_PROTOCOL = false;
bool MOVED_LEFT = false;
int LAST_READ = 0;

void cleanUp() {
    echoSensorCleanUp();
    lineSensorsCleanUp();
    motorsCleanUp();
    exit(0);
}


void setUp() {
    motorsSet();
    lineSensorSetup();
    echoSensorSet();
    speedSensorSet();
}


void *adjustCar(void *ptr) {
    bool MADE_BACK = true;

    while(1) {
        if (!OBSTACLE_AVOIDANCE_PROTOCOL) {
            if( readLinePin(LINESENSOR_LEFT_PIN) ) {
		        MADE_BACK = true;
	            printf("Adjusting to the right.\n");
                adjustMotorsSpeed(0);
                delay(125); 
	       
            }
            if( readLinePin(LINESENSOR_RIGHT_PIN) ) {
		        MADE_BACK = true;
                printf("Adjusting to the left.\n");
	            adjustMotorsSpeed(1);
                delay(125);
		
            }
	        if(!readLinePin(LINESENSOR_MIDDLE_PIN)) {
		
	            if(LAST_READ == 1) {
		    
		            moveLeft();
		            delay(100);
		            moveRegular();

		        } else if (LAST_READ == 2){
		    
		            moveRight();
		            delay(100);
		            moveRegular();
                    
		        }
	        } 
	        if(!readLinePin(LINESENSOR_MIDDLE_PIN) && !readLinePin(LINESENSOR_LEFT_PIN) && !readLinePin(LINESENSOR_RIGHT_PIN) && MADE_BACK) {
	            MADE_BACK = false;
	            if (LAST_READ == 1) {
	                stopMotors();
		            delay(500);
		            moveLeft();
		            while(!readLinePin(LINESENSOR_MIDDLE_PIN)){}
		            moveRegular();
	            } else if (LAST_READ == 2) {
	                stopMotors();
		            delay(500);
		            moveRight();
		            while(!readLinePin(LINESENSOR_MIDDLE_PIN)){}
		            moveRegular();
	            }
            }
        } else {
	        if(readLinePin(LINESENSOR_MIDDLE_PIN) && MOVED_LEFT) {
		        printf("Middle detected.\n");
		        OBSTACLE_AVOIDANCE_PROTOCOL = false;
		        moveLeft();
	            delay(1300);
	
		        MOVED_LEFT=false;
	        
          	    moveRegular();
	        }
	    }

	    if(readLinePin(LINESENSOR_LEFT_PIN)) {
	        LAST_READ = 1;
	    }
	    if(readLinePin(LINESENSOR_RIGHT_PIN)) {
	        LAST_READ = 2;
	    }
    }
}

//calculates crash time in parallel
void *calculateCrashTime(void *ptr) {

    double speed;
    double distance;
    int TIME_TO_CRASH = 100;
    int SAFE_TIME = 4;

    while (1) {
		
        distance = readDistance();
        speed    = averageSpeed();
        
        if (speed > 0) {
            TIME_TO_CRASH = distance / speed;
        }

	    printf("speed: %f\ndistance: %f\ntime to crash:%i\n", speed, distance, TIME_TO_CRASH);

        if(TIME_TO_CRASH < SAFE_TIME) {
		    OBSTACLE_AVOIDANCE_PROTOCOL = true;
            stopMotors();
            delay(5000);
            distance = readDistance();
            if (distance > 1000) {
		        OBSTACLE_AVOIDANCE_PROTOCOL = false;    
                moveRegular();
                break;
            }
            
            TIME_TO_CRASH = 100;
            moveLeft();
            delay(700);
	        MOVED_LEFT=true;
	        moveRegular();
	        delay(800);
            moveRight();
            delay(700);
	        stopMotors();
	        delay(100);
	        moveRegular();
		    delay(1500);
	        moveRight();
		    delay(700);
		    moveRegular();
        }
	
    }

}

void moveforward() {

    pthread_t t1, t2, t3, t4, t5, t6, t7, t8;
    int s1, s2, s3, s4, motor1 = 1, motor2 = 2, motor3 = 3, motor4 = 4;
    void *m1 = &motor1;
    void *m2 = &motor2;
    void *m3 = &motor3;
    void *m4 = &motor4;
    int sp1 = SPEED_SENSOR_THREE_PIN, sp2 = SPEED_SENSOR_ONE_PIN, s5, s6, s7, s8;
    void *sd1 = &sp1;
    void *sd2 = &sp2;

    printf("initialize motors\n");
    if ((s1 = pthread_create(&t1, NULL, motorToControlForward, m1))) {
        printf("thread creation failed: %d\n", s1);
    }
    if ((s2 = pthread_create(&t2, NULL, motorToControlForward, m2))) {
        printf("thread creation failed: %d\n", s2);
    }
    if ((s3 = pthread_create(&t3, NULL, motorToControlForward, m3))) {
        printf("thread creation failed: %d\n", s3);
    }
    if ((s4 = pthread_create(&t4, NULL, motorToControlForward, m4))) {
        printf("thread creation failed: %d\n", s4);
    }

    printf("join motor threads.\n");
    pthread_join( t1, NULL);
    pthread_join( t2, NULL);
    pthread_join( t3, NULL);
    pthread_join( t4, NULL);
    
        
    if ((s5 = pthread_create(&t5, NULL, useSpeedSensor, sd1))) {
        printf("thread creation failed: %i\n", s5);
    }
    if ((s6 = pthread_create(&t7, NULL, useSpeedSensor, sd2))) {
        printf("thread creation failed: %i\n", s6);
    }

    if ((s7 = pthread_create(&t6, NULL, calculateCrashTime, NULL))) {
        printf("thread creation failed: %i\n", s7);
    }

    if ((s8 = pthread_create(&t8, NULL, adjustCar, NULL))) {
        printf("thread creation failed: %i\n", s8);
    }

   while(1) {} 
}

int main() {
    signal(SIGINT, cleanUp);

    setUp();

    moveforward();
    
    cleanUp();
    
    return 0;
}
