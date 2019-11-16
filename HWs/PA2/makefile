.PHONY: all clean run
vpath %.o  src
CC=g++
CFLAGS=-std=c++11
OPTFLAGS= -O2
LDFLAGS=-lm
TARGET = link mps
all: $(TARGET)

# mps: src/mps.cpp src/chord.o
# 	$(CC) -o $@ $^ $(CFLAGS)

# chord.o: src/chord.h src/chord.cpp
# 	# $(CC) -c src/chord.h src/chord.cpp $(CFLAGS)
# 	$(CC) -c  $(CFLAGS) 

link: src/chord.cpp
	$(CC) -c -o src/chord.o src/chord.cpp $(CFLAGS) $(OPTFLAGS)

mps: src/mps.cpp src/chord.o
	$(CC) -o $@ $^ $(CFLAGS) $(OPTFLAGS)

check: src/check.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(OPTFLAGS)
clean:
	rm -f $(TARGET) src/*.o
