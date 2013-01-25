CC=clang
CFLAGS=-Wall -Wextra -O3
LIBS=-pthread
THREAD_S=tour_threaded.c
THREAD_O=$(THREAD_S:.c=.o)
REC_OPT_S=tour_rec_opt.c
REC_OPT_O=$(REC_OPT_S:.c=.o)
OBJECTS=$(THREAD_O) $(REC_OPT_O)
TOUR_THREADED=Tour_Threaded
TOUR_RECURSIVE_OPT=Tour_Recursive_Opt
TARGETS=$(TOUR_THREADED) $(TOUR_RECURSIVE_OPT)

all: $(TARGETS)

$(TOUR_THREADED): $(THREAD_O)
	$(CC) -o $(TOUR_THREADED) $(THREAD_O) $(LIBS)

$(TOUR_RECURSIVE_OPT): $(REC_OPT_O)
	$(CC) -o $(TOUR_RECURSIVE_OPT) $(REC_OPT_O) $(LIBS)

$(THREAD_O): $(THREAD_S)

$(REC_OPT_O): $(REC_OPT_S)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	echo "Running threaded test"
	time ./$(TOUR_THREADED)
	echo "Running recursive opt test"
	time ./$(TOUR_RECURSIVE_OPT)

clean:
	rm -rf $(OBJECTS) $(TOUR_THREADED) $(
