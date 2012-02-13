#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

class InputBuffer : public Buffer
{
	public:
		InputBuffer ();
		InputBuffer ( size_t entries );
		~InputBuffer ();

		void WriteBack ( OutputBuffer* write_back );
		void PopPacket ( );

	protected:

	private:
		OutputBuffer* obuf;  //!< Paired Output Buffer for writeback information

};

#endif

