CC=clang++
CFLAGS=-std=c++0x -Wall -Wextra -O3 -g -lglut -lGLU -lGL
LDFLAGS  = -g -O3 -lglut -lGLU -lGL -pthread
INCLUDE_DIR=
AR=ar
LIBS=
SOURCES=MBSet.cc complex.cc
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.cc=.o)
TARGET=MBSet

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

%.o: %.cc
	$(CC) -c -o $@ $< $(INCLUDE_DIR) $(CFLAGS)

clean:
	rm -rf $(OBJECTS) $(TARGET)
