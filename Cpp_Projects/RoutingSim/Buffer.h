#ifndef BUFFER_H
#define BUFFER_H
#include "EventTarget.h"

class Buffer : public EventTarget 
{
	public:
		Buffer ();
		Buffer ( size_t entries );
		virtual ~Buffer ();

		uint32_t Size ( );
		void ProcessPacket ( Packet p );
		void PopPacket ( );
		Packet GetPacket ( );
		uint32_t PacketsRemaining ( );

	protected:
		Packet* buf;     //!< Pointer to buffer space
		int buf_index;   //!< Pointer to next empty buffer space
		int buf_valid;   //!< Pointer to oldest valid data
		size_t buf_size; //!< Size of buffer

	private:

};


#endif

