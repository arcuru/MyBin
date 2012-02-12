#include "Global.h"

uint32_t Global_Time;
EventQueue Global_Queue;

int main ( )
{
	// Seed random number generator
	//srand(4);
	srand(time(NULL));

	// Create Router and packet generators
	Router sim(5, 5);
	PacketGen pg[4];

	// Set up generators
	pg[NORTH].SetAddr(5, 6);
	pg[NORTH].SetDirection(SOUTH);
	pg[NORTH].Connect( sim.GetTarget(NORTH) );

	pg[SOUTH].SetAddr(5, 4);
	pg[SOUTH].SetDirection(NORTH);
	pg[SOUTH].Connect( sim.GetTarget(SOUTH) );

	pg[EAST].SetAddr(6, 5);
	pg[EAST].SetDirection(WEST);
	pg[EAST].Connect( sim.GetTarget(EAST) );

	pg[WEST].SetAddr(4, 5);
	pg[WEST].SetDirection(EAST);
	pg[WEST].Connect( sim.GetTarget(WEST) );

	// Set up router connections
	sim.Connect( NORTH, &pg[NORTH]);
	sim.Connect( SOUTH, &pg[SOUTH]);
	sim.Connect( EAST, &pg[EAST]);
	sim.Connect( WEST, &pg[WEST]);

	for (Global_Time = 0; Global_Time < END_TIME; Global_Time++) {
		// Run packet generation for this timestep
		for (int i = 0; i < 4; i++) {
			pg[i].RandomGenPacket(1);
		}
		Global_Queue.Process(); // Process all packet movements in the queue
		sim.Process(); // Process all buffers in the router
		for (int i = 0; i < 4; i++) { // Process all buffers in the generators
			pg[i].Process();
		}
	}

	return EXIT_SUCCESS;
}
