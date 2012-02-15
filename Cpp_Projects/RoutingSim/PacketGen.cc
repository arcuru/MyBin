#include "Global.h"

PacketGen::PacketGen ( )
{
	ibuf = new InputBuffer(32);
	obuf = new OutputBuffer(32);
	packets_out = 0;
	packets_sent = 0;
	packets_blocked = 0;
}

PacketGen::PacketGen ( uint32_t X, uint32_t Y )
{
	SetAddr(X, Y);
	ibuf = new InputBuffer(32);
	obuf = new OutputBuffer(32);
	packets_out = 0;
	packets_sent = 0;
	packets_blocked = 0;
}

PacketGen::~PacketGen ()
{
	delete ibuf;
	delete obuf;
}

void PacketGen::SetAddr ( uint32_t X, uint32_t Y )
{
	addr_x = X;
	addr_y = Y;
}

/** SetDirection
 *  saves the direction this generator is pointing for valid
 *  generation of destination coords
 *
 *  @arg edge  Direction this packet generator is pointing
 */
void PacketGen::SetDirection ( Direction edge )
{
	dir = edge;
	return ;
}

/** GetTarget
 *  returns the inputbuffer for this packet generator
 *
 *  @return   Target input buffer
 */
EventTarget* PacketGen::GetTarget ( )
{
	return ibuf;
}

/** Connect
 *  sets up the wire from the output buffer to an input buffer
 *
 *  @arg target The connected input buffer
 */
void PacketGen::Connect ( EventTarget* target )
{
	obuf->Connect(target);
	((InputBuffer*)target)->WriteBack(obuf);
	return ;
}

/** GenPacket
 *  creates a packet with a valid address based on saved generator
 *  address and direction. We then add it to the OutputBuffer.
 *
 */
void PacketGen::GenPacket ( )
{
	uint32_t dest_x = addr_x;
	uint32_t dest_y = addr_y;
	if (NORTH == dir)
		dest_y += 2;
	else if (SOUTH == dir)
		dest_y -= 2;
	else if (WEST == dir || EAST == dir) {
		if ( rand() > (RAND_MAX/4) ) { // Higher chance of continuing straight
			if (WEST == dir)
				dest_x -= 2;
			else if (EAST == dir)
				dest_x += 2;
			else
				assert(false);
		}
		else {
			if (WEST == dir)
				dest_x--;
			else if (EAST == dir)
				dest_x++;
			else
				assert(false);
			if ( rand() < (RAND_MAX/2) )
				dest_y++;
			else
				dest_y--;
		}
	}
	else
		assert(false);

	// Generate packet and load appropriate data
	Packet p( dest_x, dest_y, addr_x, addr_y, true, false, rand() & 0xFFFFFFFF);

	// Check to make sure we aren't routing to (5, 5)
	assert((p.GetX() != p.GetY()) || (p.GetX() != 5));

	// Add packet to output buffer
	packet_injections++;
	if (obuf->PacketsRemaining() < 32) {
		obuf->ProcessPacket(p);
		packets_sent++;
	}
	else {
	//	cout << "PacketGen OutputBuffer full" << endl;
		packets_blocked++;
	}
	return ;
}

/** RandomGenPacket
 *  generate a packet based on random chance
 *
 *  @arg chances  Chance of generating a packet
 */
void PacketGen::RandomGenPacket ( double chances )
{
	if (rand() < (chances * (double)RAND_MAX))
		GenPacket();
	return ;
}

/** Process
 *  handles all necessary buffer operations for a single time step
 *
 */
void PacketGen::Process ( )
{
	if (ibuf->PacketsRemaining() != 0) {
		assert(1 == ibuf->PacketsRemaining());
		Packet p = ibuf->GetPacket();
		assert(p.GetX() == addr_x);
		assert(p.GetY() == addr_y);
		ibuf->PopPacket();
		packets_out++;
		packet_ejections++;
	}
	obuf->ProcessBuffer();
	return ;
}



