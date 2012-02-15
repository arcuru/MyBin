#ifndef GLOBAL_H
#define GLOBAL_H

// Uncomment to disable assert's
#define NDEBUG

#include <cstdint>
#include <cassert>
#include <iostream>
using namespace std;
#include <cstdlib>

#define END_TIME 1000000

extern uint32_t Global_Time; //!< Current time step

enum direction {
	NORTH = 0,
	SOUTH = 1,
	EAST  = 2,
	WEST  = 3
}; //!< Cardinal direction for use in 2D Mesh

typedef enum direction Direction;

#include "Packet.h"
#include "EventTarget.h"
#include "EventQueue.h"
#include "OutputBuffer.h"
#include "InputBuffer.h"
#include "PacketGen.h"
#include "Router.h"

extern EventQueue Global_Queue; //!< Single global queue handling all events

extern uint32_t packet_injections;
extern uint32_t packet_ejections;

#endif
