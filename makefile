output : carController.o echoSensorsController.o lineSensorsController.o motorsController.o speedSensorsController.o
	gcc -o output carController.o echoSensorsController.o lineSensorsController.o motorsController.o speedSensorsController.o -lpthread -lwiringP
carController.o : src/carController.c headers/carController.h
	gcc -c src/carController.c
echoSensorsController.o : src/echoSensorsController.c headers/echoSensorsController.h
	gcc -c echoSensorsController.c
lineSensorsController.o : src/lineSensorsController.c headers/lineSensorsController.h
	gcc -c lineSensorsController.c
motorsController.o : src/motorsController.c headers/motorsController.h
	gcc -c motorsController.c
speedSensorsController.o : src/speedSensorsController.c headers/speedSensorsController.h
	gcc -c speedSensorsController.c
clean :
	rm output carController.o echoSensorsController.o lineSensorsController.o motorsController.o speedSensorsController.o
