#include "Global.h"

uint32_t Global_Time;
EventQueue Global_Queue;
uint32_t packet_injections = 0;
uint32_t packet_ejections = 0;
void RunSimulation( uint32_t simulation_end, double injection_chance );

int main ( int argc, char** argv )
{
	uint32_t simulation_end = END_TIME;
	double injection_chance = 0.6;

	// Generate lots of output
	cout << "Packet Injections, ";
	cout << "Packet Ejections, ";
	cout << "Offered Load, ";
	cout << "Switch Throughput, ";
	cout << "Packet Collisions, ";
	cout << "Simulation Time, ";
	cout << "Injection Chance" << endl;
	if (argc > 1) {
		simulation_end = atoi(argv[1]);
		if (argc > 2) {
			injection_chance = atof(argv[2]);
		}
		RunSimulation( simulation_end, injection_chance );
	}
	else {
		// Set number of tests
		uint32_t tests = 100;

		// Iterate and run tests
		for (int i = tests; i >= 0; i--) {
			injection_chance = ((double)i) / tests;
			RunSimulation( simulation_end, injection_chance );
			Global_Queue.Clear();
		}
	}

}

/** RunSimulation
 *  execute a full simulation of a single router + 4 PacketGens with the
 *  provided parameters. Prints output.
 *
 *  @args simulation_end   Total time to run the simulation
 *  @args injection_chance Chance of each Packet Generator injecting a
 *                          packet each cycle
 */
void RunSimulation( uint32_t simulation_end, double injection_chance )
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

	for (Global_Time = 0; Global_Time < simulation_end; Global_Time++) {
		// Run packet generation for this timestep
		for (int i = 0; i < 4; i++) {
			pg[i].RandomGenPacket(injection_chance);
		}
		Global_Queue.Process(); // Process all packet movements in the queue
		sim.Process(); // Process all buffers in the router
		for (int i = 0; i < 4; i++) { // Process all buffers in the generators
			pg[i].Process();
		}
	}

	cout << packet_injections << ", ";
	cout << packet_ejections << ", ";
	cout << ((double)packet_injections)/simulation_end << ", ";
	cout << ((double)packet_ejections)/simulation_end << ", ";
	cout << sim.GetCollisions() << ", ";
	cout << simulation_end << ", ";
	cout << injection_chance << endl;
	packet_injections = 0;
	packet_ejections = 0;

	return ;
}
