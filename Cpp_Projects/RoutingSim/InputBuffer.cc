#include "Global.h"


InputBuffer::InputBuffer ()
{
	obuf = NULL;
}

InputBuffer::InputBuffer ( size_t entries ) : Buffer(entries)
{
	obuf = NULL;
}

InputBuffer::~InputBuffer ()
{
}


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
	Packet p;
	p.size = 0;
	p.x = 1;
	Global_Queue.Add(p, obuf, Global_Time+1);
	Buffer::PopPacket();
}
