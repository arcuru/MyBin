#include "Global.h"


Router::Router (uint32_t X, uint32_t Y)
{
	addr_x = X;
	addr_y = Y;
	packet_collision = 0;
}


Router::~Router ()
{
}

/** GetTarget
 *  Returns the inputbuffer found at the specified edge
 *
 *  @arg edge Edge of router to return
 *  @return   Target input buffer
 */
EventTarget* Router::GetTarget ( Direction edge )
{
	return &ibuf[edge];
}

/** GetCollisions
 *  returns the total number of packet collisions observed by this router
 *
 * @return  Number of packet collisions
 */
uint32_t Router::GetCollisions ( )
{
	return packet_collision;
}

/** Connect
 *  sets up the connection between this routers output buffer
 *  and target routers input buffer
 *
 *  @arg edge   Edge of this router we are connecting
 *  @arg target Target packet generator
 */
void Router::Connect( Direction edge, PacketGen* target)
{
	obuf[edge].Connect(target->GetTarget());
	((InputBuffer*)target->GetTarget())->WriteBack(&obuf[edge]);
	return ;
}

/** Process
 *  handles a single cycle of router operation
 *
 */
void Router::Process ( )
{
	// Process all the output buffers
	for (int i=0; i < 4; i++)
		obuf[i].ProcessBuffer();

	// Traverse packets through the switch
	bool sent[4];
	for (int i=0; i < 4; i++)
		sent[i] = false;

	// Start sending from a random side
	int start = rand() % 4;
	for (int k=start; k < 4+start; k++) {
		int i = k % 4;
		if (ibuf[i].Routed() > 0) {
			// Valid packets are routed
			Packet p = ibuf[i].GetPacket();
			Direction d = ibuf[i].GetRoute();
			if ( false == sent[d] ) {
				if (obuf[d].PacketsRemaining() < obuf[d].Size()-1) {
					Global_Queue.Add(p, &obuf[d], Global_Time+1);
					sent[d] = true;
					ibuf[i].PopPacket();
				}
				else {
					packet_collision++;
				}
			}
			else {
				// Outgoing buffer full
				packet_collision++;
			}
		}
		/*
		if (ibuf[i].PacketsRemaining() > 0) {
			// Process packet
			Packet p = ibuf[i].GetPacket();
			if ( (p.GetX() < addr_x) && (false == sent[WEST]) ) {
				if ( obuf[WEST].PacketsRemaining() < obuf[WEST].Size() ) {
					Global_Queue.Add(p, &obuf[WEST], Global_Time+1);
					sent[WEST] = true;
					ibuf[i].PopPacket();
				}
			}
			else if ( (p.GetX() > addr_x) && (false == sent[EAST]) ) {
				if ( obuf[EAST].PacketsRemaining() < obuf[EAST].Size() ) {
					Global_Queue.Add(p, &obuf[EAST], Global_Time+1);
					sent[EAST] = true;
					ibuf[i].PopPacket();
				}
			}
			else if ( (p.y < addr_y) && (false == sent[SOUTH]) ) {
				if ( obuf[SOUTH].PacketsRemaining() < obuf[SOUTH].Size() ) {
					Global_Queue.Add(p, &obuf[SOUTH], Global_Time+1);
					sent[SOUTH] = true;
					ibuf[i].PopPacket();
				}
			}
			else if ( (p.y > addr_y) && (false == sent[NORTH]) ) {
				if ( obuf[NORTH].PacketsRemaining() < obuf[NORTH].Size() ) {
					Global_Queue.Add(p, &obuf[NORTH], Global_Time+1);
					sent[NORTH] = true;
					ibuf[i].PopPacket();
				}
			}
			else if ( (p.GetX() == addr_x) && (p.y == addr_y) ) {
				// Packet routed to this address
				// Shouldn't happen in this simulation yet
				assert(false);
			}
			else {
				// Outgoing buffer full
				packet_collision++;
			}
		}
		*/
	}

	// Route packets
	for (int i=0; i < 4; i++)
		ibuf[i].RoutePacket( addr_x, addr_y );

	return ;
}

