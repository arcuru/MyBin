CC=clang
CFLAGS=-Wall -Wextra
INCLUDE_DIR=-I./inc
AR=ar
LIBS=
SOURCES=./src/main.c
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.c=.o)
TARGET=Queens

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCES)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
