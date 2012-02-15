#include "Global.h"

OutputBuffer::OutputBuffer ()
{
	t = NULL;
	available_space = 4;
}

OutputBuffer::OutputBuffer ( size_t entries ) : Buffer(entries)
{
	t = NULL;
	available_space = 4;
}

OutputBuffer::~OutputBuffer ()
{
}

/** ProcessBuffer
 *  processes the current buffer in the event that we need to do something
 *
 */

void OutputBuffer::ProcessBuffer (  )
{
	if (PacketsRemaining() == 0)
		return;
	if ( 0 == available_space )
		return;
	Global_Queue.Add(GetPacket(), t, Global_Time+1); 
	available_space--;
	PopPacket();
	return ;
}


/** Connect
 *  sets up the wire from this output buffer to an input buffer
 *
 *  @arg target The connected input buffer
 */
void OutputBuffer::Connect ( EventTarget* target )
{
	t = target;
	return ;
}

/** ProcessPacket
 *  overwrites Buffer::ProcessPacket for credit based flow control
 *
 */
void OutputBuffer::ProcessPacket ( Packet p )
{
	if ( p.GetCredit() )
		available_space += p.GetData();
	else
		Buffer::ProcessPacket(p);
}
