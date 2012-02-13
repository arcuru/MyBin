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
		EventTarget* t;            //!< Corresponding Input Buffer for packet destination
		uint32_t available_space;  //!< Keeping track of how many available spaces are left in corresponding input buffer

};

#endif
