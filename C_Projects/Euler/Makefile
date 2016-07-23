CC=gcc
CFLAGS=-Wall -Wextra -g -fopenmp -Werror -O3
INCLUDE_DIR=-I./inc \
			-I../Utils/inc \
			-I../Primes/inc \
			-I../NumberTheory/inc \
			-I../Sudoku/inc
MYLIBS=../Utils/libUtils.a \
	 ../Primes/libPrimes.a \
	 ../NumberTheory/libNumberTheory.a \
	 ../Sudoku/libSudoku.a
LIBS=-pthread -lgomp -lgmp -lm $(MYLIBS) -O3
HEADERS=./inc/Euler.h
SOURCES=./src/main.c \
		./src/108.c \
		./src/10.c \
		./src/112.c \
		./src/119.c \
		./src/122.c \
		./src/124.c \
		./src/125.c \
		./src/12.c \
		./src/145.c \
		./src/14.c \
		./src/15.c \
		./src/179.c \
		./src/17.c \
		./src/187.c \
		./src/191.c \
		./src/19.c \
		./src/1.c \
		./src/204.c \
		./src/206.c \
		./src/211.c \
		./src/214.c \
		./src/21.c \
		./src/229.c \
		./src/231.c \
		./src/234.c \
		./src/23.c \
		./src/24.c \
		./src/26.c \
		./src/27.c \
		./src/28.c \
		./src/29.c \
		./src/2.c \
		./src/30.c \
		./src/31.c \
		./src/32.c \
		./src/33.c \
		./src/34.c \
		./src/35.c \
		./src/36.c \
		./src/37.c \
		./src/38.c \
		./src/39.c \
		./src/3.c \
		./src/40.c \
		./src/41.c \
		./src/43.c \
		./src/44.c \
		./src/45.c \
		./src/46.c \
		./src/47.c \
		./src/48.c \
		./src/49.c \
		./src/4.c \
		./src/50.c \
		./src/51.c \
		./src/52.c \
		./src/53.c \
		./src/55.c \
		./src/57.c \
		./src/58.c \
		./src/59.c \
		./src/5.c \
		./src/60.c \
		./src/62.c \
		./src/69.c \
		./src/6.c \
		./src/70.c \
		./src/72.c \
		./src/73.c \
		./src/74.c \
		./src/75.c \
		./src/76.c \
		./src/77.c \
		./src/78.c \
		./src/7.c \
		./src/81.c \
		./src/85.c \
		./src/87.c \
		./src/89.c \
		./src/8.c \
		./src/92.c \
		./src/94.c \
		./src/95.c \
		./src/96.c \
		./src/97.c \
		./src/99.c \
		./src/9.c 
OBJECTS=$(SOURCES:.c=.o)
TARGET=Euler

all: $(TARGET)

$(TARGET): $(OBJECTS) $(MYLIBS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE_DIR)

clean:
	rm -rf $(OBJECTS) $(TARGET)
