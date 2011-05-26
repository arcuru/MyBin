CC=gcc
CFLAGS=-Wall -Wextra
INCLUDE_DIR=-I./inc \
			$(shell pkg-config --cflags gtk+-2.0)
AR=ar
LIBS=$(shell pkg-config --libs gtk+-2.0)
SOURCES=./src/main.c \
		./src/callback.c
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.c=.o)
TARGET=GTK_Pong

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCES)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
