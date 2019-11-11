.PHONY: all clean run

CC=g++
CFLAGS=-std=c++11 -O2
LDFLAGS=-lm
TARGET = mps
all: $(TARGET)

mps: src/mps.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) -Iinc

clean:
	rm -f $(TARGET)
