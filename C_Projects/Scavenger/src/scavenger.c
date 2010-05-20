#include "packets.h"

void usage(char* progname) {
	fprintf(stderr,"USAGE: %s [-file <log>] [-debug] <tracefile>\n",progname);
	exit(1);
}

int main(int argc, char* argv[]) {
	if ( argc < 2 || argc > 5 ) {
		usage(argv[0]);
	}
	int i=0;
	int debug=0;
	char* trace_filename=NULL;
	char* log_filename=NULL;
	for (i=1;i<argc;i++) {
		if ( strcmp("-debug",argv[i]) == 0 ) {
			if ( debug )
				usage(argv[0]);
			debug=1;
		}
		else if ( strcmp("-file",argv[i]) == 0 ) {
			if ( (i+1 == argc) || (log_filename != NULL) )
				usage(argv[0]);
			log_filename=argv[++i];
			if ( strcmp("-debug",log_filename) == 0 )
				usage(argv[0]);
		}
		else if ( i == argc-1 )
			trace_filename=argv[i];
	}
	FILE* log = NULL;
	if ( !(log=fopen(log_filename,"w")) )
		log=stdout;
	FILE* trace=NULL;
	if ( !(trace=fopen(trace_filename,"r")) )
		usage(argv[0]);
	packet p;
	while ( !parse_packet(trace,&p)) {
		print_packet(log,&p);
		if ( debug )
			printf("%d\n",debug++);
	}
	if ( log != stdout )
		fclose(log);
	fclose(trace);
	return 0;
}
