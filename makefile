output : carController.o echoSensorsController.o lineSensorsController.o motorsController.o speedSensorsController.o
        gcc -o output carController.o echoSensorsController.o lineSensorsController.o motorsController.o speedSensorsController.o -lpthread -lwiringPi

carController.o : carController.c carController.h
        gcc -c carController.c
echoSensorsController.o : echoSensorsController.c echoSensorsController.h
        gcc -c echoSensorsController.c
lineSensorsController.o : lineSensorsController.c lineSensorsController.h
        gcc -c lineSensorsController.c
motorsController.o : motorsController.c motorsController.h
        gcc -c motorsController.c
speedSensorsController.o : speedSensorsController.c speedSensorsController.h
        gcc -c speedSensorsController.c
clean :
        rm output carController.o echoSensorsController.o lineSensorsController.o motorsController.o speedSensorsController.o
