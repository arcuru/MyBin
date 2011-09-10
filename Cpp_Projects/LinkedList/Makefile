CC=clang++
CFLAGS=-Wall -Wextra -O3
INCLUDE_DIR=-I./inc
AR=ar
LIBS=
SOURCES=./src/LinkedList.cc ./src/SingleLL.cc ./src/test.cc
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
