# Makefile for OPENGL examples

LDFLAGS  = -g -O3 -lglut -lGLU -lGL -pthread
CCFLAGS = -g -O3 -Wall
CXXFLAGS = -g -O3 -Wall
CFLAGS = -

CXX = g++
CC  = g++

SOURCES=MBSet.cc complex.cc
OBJECTS=$(SOURCES:.cc=.o)

MBSet: $(OBJECTS)

clean:
	rm -f MBSet $(OBJECTS)

