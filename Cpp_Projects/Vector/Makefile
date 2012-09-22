CC=clang++
CFLAGS=-std=c++0x -Wall -Wextra -O3 -g
INCLUDE_DIR=-I./inc -I./inc_test
AR=ar
LIBS=
SOURCES=./src_test/String.cc ./src_test/testVec.cc
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

test: all
	./$(TARGET) > tmp.txt
	diff tmp.txt data_test/expected-alltests.txt

