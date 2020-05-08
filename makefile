LIBS = -lpthreads -lwiringPi
CFLAGS = -Wall

# (This should be the actual list of C files)
SRC=$(wildcard '*.c')

test: $(SRC)
    gcc -o $@ $^ $(CFLAGS) $(LIBS)