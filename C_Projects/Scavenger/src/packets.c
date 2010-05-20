#include "packets.h"

int read4(FILE *in) {
	int c=0;
	fscanf(in,"%1x",&c);
	return c;
}

int read8(FILE *in) {
	return (read4(in)<<4) | read4(in);
}

int read16(FILE *in) {
	return (read8(in)<<8) | read8(in);
}
int read32(FILE *in) {
	return (read16(in)<<16) | read16(in);
}

int parse_packet(FILE *in, packet *p) {
	int c=0;
	fscanf(in,"%d",&c);
	if ( c == EOF )
		return 1;
	p->packet_num=c;
	c=read4(in);
	p->one_bit_4=c&0x1;
	p->one_bit_3=(c&0x2)>>1;
	p->one_bit_2=(c&0x4)>>2;
	p->one_bit_1=(c&0x8)>>3;
	p->four_bits=read4(in);
	p->one_byte=read8(in);
	p->two_bytes=read16(in);
	p->four_bytes=read32(in);
	while ( (c=fgetc(in)) != '\n' && c != EOF ) {}
	if ( c == EOF )
		return 1;
	return 0;
}

int print_packet(FILE *log, packet *p) {
	fprintf(log,"*****************************************************************\n");
	fprintf(log,"* Packet Number %d\n",p->packet_num);
	fprintf(log,"*       Bit 1: 0x%1x\n",p->one_bit_1);
	fprintf(log,"*       Bit 2: 0x%1x\n",p->one_bit_2);
	fprintf(log,"*       Bit 3: 0x%1x\n",p->one_bit_3);
	fprintf(log,"*       Bit 4: 0x%1x\n",p->one_bit_4);
	fprintf(log,"*   Four Bits: 0x%1x\n",p->four_bits);
	fprintf(log,"*    One Byte: 0x%02x\n",p->one_byte);
	fprintf(log,"*   Two Bytes: 0x%04x\n",p->two_bytes);
	fprintf(log,"*  Four Bytes: 0x%08x\n",p->four_bytes);
	fprintf(log,"*****************************************************************\n");
	return 0;
}
