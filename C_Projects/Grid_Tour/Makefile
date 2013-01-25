CC=clang
CFLAGS=-Wall -Wextra -O3
LIBS=-pthread
THREAD_S=tour_threaded.c
THREAD_O=$(THREAD_S:.c=.o)
REC_S=tour_rec.c
REC_O=$(REC_S:.c=.o)
OBJECTS=$(THREAD_O) $(REC_O)
TOUR_THREADED=Tour_Threaded
TOUR_RECURSIVE=Tour_Recursive
TARGETS=$(TOUR_THREADED) $(TOUR_RECURSIVE)

all: $(TARGETS)

$(TOUR_THREADED): $(THREAD_O)
	$(CC) -o $(TOUR_THREADED) $(THREAD_O) $(LIBS)

$(TOUR_RECURSIVE): $(REC_O)
	$(CC) -o $(TOUR_RECURSIVE) $(REC_O) $(LIBS)

$(THREAD_O): $(THREAD_S)

$(REC_O): $(REC_S)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	echo "Running threaded test"
	time ./$(TOUR_THREADED)
	echo "Running recursive opt test"
	time ./$(TOUR_RECURSIVE)

clean:
	rm -rf $(OBJECTS) $(TOUR_THREADED) $(
