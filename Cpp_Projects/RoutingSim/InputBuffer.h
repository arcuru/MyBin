#ifndef INPUTBUFFER_H
#define INPUTBUFFER_H

class InputBuffer : public Buffer
{
	public:
		InputBuffer ();                             /* constructor      */
		InputBuffer ( size_t entries );
		~InputBuffer ();                            /* destructor       */

		void WriteBack ( OutputBuffer* write_back );
		void PopPacket ( );

	protected:

	private:
		OutputBuffer* obuf;

};

#endif

