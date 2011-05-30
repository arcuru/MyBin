CC=gcc
CFLAGS=-Wall -Wextra 
SUDOKU_VER=Sudoku
INCLUDE_DIR=-I./inc \
			-I../Utils/inc \
			-I../$(SUDOKU_VER)/inc
AR=ar
LIBS=../$(SUDOKU_VER)/libSudoku.a \
	 ../Utils/libUtils.a
SOURCES=./src/main.c
ASOBJECTS=$(ASSOURCES:.s=.o)
OBJECTS=$(SOURCES:.c=.o)
TARGET=Sudoku_Solver

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

$(OBJECTS): $(SOURCES)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)
