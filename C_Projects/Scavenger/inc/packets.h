#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct packet_struct {
	int packet_num;      /* put the packet number here                */
	char one_bit_1;      /* put first bit of packet here              */
	char one_bit_2;      /* put second bit of packet here             */
	char one_bit_3;      /* put third bit of packet here              */
	char one_bit_4;      /* put fourth bit of packet here             */
	char four_bits;      /* put next four bits of packet here         */
	char one_byte;       /* put next 8 bits (one byte) of packet here */
	short two_bytes;     /* put next 2 bytes of packet here           */
	int four_bytes;      /* put next 4 bytes of packet here           */
} packet;

int parse_packet(FILE*,packet*);
int print_packet(FILE*,packet*);
