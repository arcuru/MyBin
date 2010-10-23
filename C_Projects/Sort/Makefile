CC=gcc
CFLAGS=-Wall -Wextra
AR=ar
INCLUDE_DIR=-I./inc
SOURCES=./src/BInSort.c ./src/BubbleSort.c
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.c=.o)
TARGET=libSort.a

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(AR) rcs $(TARGET) $(OBJECTS)

$(OBJECTS): $(SOURCES)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
