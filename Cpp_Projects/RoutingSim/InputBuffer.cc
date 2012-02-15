#include "Global.h"


InputBuffer::InputBuffer ()
{
	obuf = NULL;
	buf_route = -1;
	routes = (Direction*) malloc(sizeof(Direction) * 4);
}

InputBuffer::InputBuffer ( size_t entries ) : Buffer(entries)
{
	obuf = NULL;
	buf_route = -1;
	routes = (Direction*) malloc(sizeof(Direction) * entries);
}

InputBuffer::~InputBuffer ()
{
	free(routes);
}

/** WriteBack
 *  sets corresponding output buffer for flow control
 *
 *  @args write_back  Pointer to corresponding output buffer
 */
void InputBuffer::WriteBack ( OutputBuffer* write_back )
{
	obuf = write_back;
	return ;
}

/** PopPacket
 *  overwrites Buffer::PopPacket for credit based flow control
 *
 */
void InputBuffer::PopPacket ( )
{
	Packet p( 0, 0, 0, 0, true, true, 1 );
	Global_Queue.Add(p, obuf, Global_Time+1);
	if ( buf_route == buf_valid )
		buf_route = -1;
	Buffer::PopPacket();
}

/** RoutePacket
 *  performs routing computation on the next packet to be routed
 *
 *  @args router_x X address of router
 *  @args router_y Y address of router
 */
void InputBuffer::RoutePacket ( uint32_t router_x, uint32_t router_y )
{
	if ( Routed() < PacketsRemaining() ) {
		// Routing packet buf[buf_route]
		if ( -1 == buf_route )
			buf_route = buf_valid;
		else {
			buf_route++;
			buf_route %= buf_size;
		}
		if ( -1 == buf_route )
			assert(false); // No valid packets

		// Route packet stored in buf[buf_route]
		if ( buf[buf_route].GetX() < router_x )
			routes[buf_route] = WEST;
		else if ( buf[buf_route].GetX() > router_x )
			routes[buf_route] = EAST;
		else if ( buf[buf_route].GetY() < router_y )
			routes[buf_route] = SOUTH;
		else if ( buf[buf_route].GetY() > router_y )
			routes[buf_route] = NORTH;
		else
			assert(false); // Packet should never be routed to this address
	}
}

/** GetRoute
 *  returns the direction that the next valid packet as been routed to
 *
 *  @return  Direction of output port
 */
Direction InputBuffer::GetRoute ( )
{
	if ( -1 == buf_valid || -1 == buf_route ) {
		// No routed packets
		assert(false);
	}
	return routes[buf_valid];
}

/** Routed
 *  returns the number of packets in the buffer that have been routed
 *
 *  @return  Number of routed packets
 */
size_t InputBuffer::Routed ( )
{
	if ( -1 == buf_route )
		return 0;
	int tmp = buf_index;
	if (tmp <= buf_route)
		tmp += buf_size;
	return tmp - buf_route;
}

void InputBuffer::ProcessPacket (Packet p)
{
	Buffer::ProcessPacket(p);
}
