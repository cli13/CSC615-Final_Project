#include "./carController.h"

void cleanUp() {
    echoSensorCleanUp();
    lineSensorsCleanUp();
    motorsCleanUp();
    speedSensorsCleanUp();
}

int main(void) {
    signal(SIGINT, cleanUp);
}