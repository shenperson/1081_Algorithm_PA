.PHONY: all clean run
vpath %.o  src
CC=g++
CFLAGS=-std=c++11
OPTFLAGS= -O3
LDFLAGS=-lm
TARGET = link cb
all: $(TARGET)

# mps: src/mps.cpp src/chord.o
# 	$(CC) -o $@ $^ $(CFLAGS)

# chord.o: src/chord.h src/chord.cpp
# 	# $(CC) -c src/chord.h src/chord.cpp $(CFLAGS)
# 	$(CC) -c  $(CFLAGS) 

link: src/graph.cpp
	$(CC) -c -o src/graph.o src/graph.cpp $(CFLAGS) $(OPTFLAGS)

cb: src/cb.cpp src/graph.o
	$(CC) -o $@ $^ $(CFLAGS) $(OPTFLAGS)

gen: src/graph_gen.cpp
	$(CC) -o $@ $^ $(CFLAGS) $(OPTFLAGS)
# check: src/check.cpp
# 	$(CC) -o $@ $^ $(CFLAGS) $(OPTFLAGS)
clean:
	rm -f  src/*.o
