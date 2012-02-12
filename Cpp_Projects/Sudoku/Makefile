CC=g++
CFLAGS=-std=c++0x -Wall -Wextra -O3 -g
INCLUDE_DIR=-I./inc -I./../Timer/inc
AR=ar
LIBS=
SOURCES=./src/Sudoku.cc ./src/test.cc ./../Timer/src/Timer.cc
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
