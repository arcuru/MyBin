CC=gcc
CFLAGS=-Wall -Wextra
INCLUDE_DIR=-I./inc -I../NumberTheory/inc
AR=ar
LIBS=-lm ../NumberTheory/libNumberTheory.a
SOURCES=./src/main.c
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.c=.o)
TARGET=Calc

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCES)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)

test:
	./$(TARGET) tests/*
