#ifndef OUTPUTBUFFER_H
#define OUTPUTBUFFER_H
#include "Buffer.h"

class OutputBuffer : public Buffer
{
	public:
		OutputBuffer ();
		OutputBuffer ( size_t entries );
		~OutputBuffer ();

		void ProcessBuffer ( );
		void Connect ( EventTarget* target );
		void ProcessPacket ( Packet p );

	protected:

	private:
		EventTarget* t;
		uint32_t last_processed;
		uint32_t available_space;

};

#endif
