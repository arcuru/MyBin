#ifndef PACKETGEN_H
#define PACKETGEN_H

class PacketGen
{
	public:
		PacketGen ( );
		PacketGen ( uint32_t X, uint32_t Y );                             /* constructor      */
		~PacketGen ();                            /* destructor       */

		void SetAddr ( uint32_t X, uint32_t Y);
		void SetDirection ( Direction edge );
		EventTarget* GetTarget ( );
		void Connect ( EventTarget* target );
		void GenPacket ( );
		void RandomGenPacket ( double chances );
		void Process ( );


	protected:

	private:
		InputBuffer* ibuf;
		OutputBuffer* obuf;
		Direction dir;
		uint32_t addr_x;
		uint32_t addr_y;
		uint32_t packets_out;

};

#endif

