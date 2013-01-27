CC=gcc
CFLAGS=-Wall -Wextra
INCLUDE_DIR=-I./inc -I../Primes/inc
AR=ar
LIBS=../Primes/libPrimes.a -lm
SOURCES=./src/main.c
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.c=.o)
TARGET=Goldbach

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCES)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
