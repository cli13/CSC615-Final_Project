LIBS = -lpthreads -lwiringPi
CFLAGS = -Wall

OBJ = carController.o               \
      echoSensorController.o        \
      lineSensorsController.o       \
      motorsController.o            \
      speedSensorsController.o      
      
SRCS = $(OBJ:%.o=%.c)

all: $(SRCS)
    gcc -o $@  $(CFLAGS) $(LIBS) $(SRCS)
