#ifndef BUFFER_H
#define BUFFER_H
#include "EventTarget.h"

class Buffer : public EventTarget 
{
	public:
		Buffer ();                             /* constructor      */
		Buffer ( size_t entries );
		~Buffer ();                            /* destructor       */

		uint32_t Size ( );
		void ProcessPacket ( Packet p );
		void PopPacket ( );
		Packet GetPacket ( );
		uint32_t PacketsRemaining ( );

	protected:

	private:
		Packet* buf;
		int buf_index;
		int buf_valid;
		size_t buf_size;

};


#endif

