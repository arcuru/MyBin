CC=gcc
CFLAGS=-Wall -Wextra -g
INCLUDE_DIR=
AR=ar
LIBS=
SOURCES=./main.c
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.c=.o)
TARGET=TTT

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCES)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

test: all
	./$(TARGET)

clean:
	rm -rf $(OBJECTS) $(TARGET)
