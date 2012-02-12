CC=clang++
CFLAGS=-std=c++0x -Wall -Wextra -O3 -g
INCLUDE_DIR=-I./inc
AR=ar
LIBS=
SOURCES=./src/Primes.cc ./src/test.cc
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.cc=.o)
TARGET=Test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

%.o: %.cc
	$(CC) -c -o $@ $< $(INCLUDE_DIR) $(CFLAGS)

clean:
	rm -rf $(OBJECTS) $(TARGET)
