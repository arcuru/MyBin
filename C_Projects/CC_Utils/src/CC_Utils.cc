#include "CC_Utils.h"
#include <sys/time.h>

//Returns number of digits of inputted number in base 10
int Length(int n) {
	int digits = 0;
	while (n) {
		n /= 10;
		digits++;
	}
	return digits;
}

int Length(uns64 n) {
	int digits = 0;
	while (n) {
		n /= 10;
		digits++;
	}
	return digits;
}

int Length(int64 n) {
	int digits = 0;
	while (n) {
		n /= 10;
		digits++;
	}
	return digits;
}

//Returns number of digits of inputed number in base 2
int LengthBin(int n) {
	int digits = 0;
	while (n) {
		n >>= 1;
		digits++;
	}
	return digits;
}

int LengthBin(uns64 n) {
	int digits = 0;
	while (n) {
		n >>= 1;
		digits++;
	}
	return digits;
}

//Sets a list of given length to 0's
int* Clear(int* list, int length) {
	for (int i = 0; i < length; i++) {
		list[i] = 0;
	}
	return list;
}

//Returns current time in microseconds
int GetMicrosecondClock() {
	timeval tv;
	gettimeofday(&tv, 0);
	static int startsec = 0;
	static bool first = true;
	if (first) {
		startsec = tv.tv_sec;
		first = false;
	}
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

//Returns current time in milliseconds
float GetMillisecondClock() {
	return (float) GetMicrosecondClock() / 1000;
}

//Returns current time in seconds
float GetSecondClock() {
	return GetMillisecondClock() / 1000;
}

