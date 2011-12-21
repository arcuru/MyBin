# Makefile for ECE 3035 Project 2-1 - Data Structures

# The compiler being used

CC= gcc

# compiler options

CFLAGS= -g -Wall

# linker

LN= $(CC)

# linker options

LNFLAGS= -g

# extra libraries used in linking (use -l command)

LDLIBS=

# source files

SOURCES= test.c P2-1.c

# include files

INCLUDES= P2-1.h

# object files

OBJECTS=$(SOURCES:.c=.o)

all: 	P2-2Test

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $*.c

P2-2Test:	$(OBJECTS)
	$(LN) $(LNFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

clean:
	rm -f *.o
	rm -f *~

test:	P2-test
	./P2-test

