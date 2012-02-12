#ifndef GLOBAL_H
#define GLOBAL_H

// Uncomment to disable assert's
//#define NDEBUG

#include <cstdint>
#include <cassert>
#include <iostream>
using namespace std;
#include <cstdlib>

#define END_TIME 10000

extern uint32_t Global_Time;

struct Packet {
	uint8_t x;
	uint8_t y;
	uint16_t size;
	uint32_t data;
};

typedef struct Packet Packet;


enum direction {
	NORTH = 0,
	SOUTH = 1,
	EAST  = 2,
	WEST  = 3
};

typedef enum direction Direction;

#include "EventTarget.h"
#include "EventQueue.h"
#include "OutputBuffer.h"
#include "InputBuffer.h"
#include "PacketGen.h"
#include "Router.h"

extern EventQueue Global_Queue;

#endif
