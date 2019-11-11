.PHONY: all clean run
vpath %.o  src
CC=g++
CFLAGS=-std=c++11 -O2
LDFLAGS=-lm
TARGET = chord.o mps
all: $(TARGET)

mps: src/mps.cpp src/chord.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Iinc

chord.o: src/chord.h src/chord.cpp
	$(CC) -c src/chord.h src/chord.cpp $(CFLAGS)

clean:
	rm -f $(TARGET) src/*.o src/*.h.gch chord.o
