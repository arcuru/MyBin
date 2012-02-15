CC=clang++
CFLAGS=-std=c++0x -Wall -Wextra -g -pedantic -O4
INCLUDE_DIR=
LIBS=
HEADERS=Global.h
SOURCES=Packet.cc \
		EventQueue.cc \
		Buffer.cc \
		InputBuffer.cc \
		OutputBuffer.cc \
		Router.cc \
		PacketGen.cc \
		main.cc
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.cc=.o)
TARGET=RoutingSim

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

%.o: %.cc $(HEADERS)
	$(CC) -c -o $@ $< $(INCLUDE_DIR) $(CFLAGS)

clean:
	rm -rf $(OBJECTS) $(TARGET)

test: all
	./$(TARGET)
