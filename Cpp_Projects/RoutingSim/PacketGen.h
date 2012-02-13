#ifndef PACKETGEN_H
#define PACKETGEN_H

class PacketGen
{
	public:
		PacketGen ( );
		PacketGen ( uint32_t X, uint32_t Y );
		~PacketGen ();

		void SetAddr ( uint32_t X, uint32_t Y);
		void SetDirection ( Direction edge );
		EventTarget* GetTarget ( );
		void Connect ( EventTarget* target );
		void GenPacket ( );
		void RandomGenPacket ( double chances );
		void Process ( );


	protected:

	private:
		InputBuffer* ibuf;       //!< Ejection queue 
		OutputBuffer* obuf;      //!< Injection queue
		Direction dir;           //!< Direction this generator is pointing
		uint32_t addr_x;         //!< X address of this generator
		uint32_t addr_y;         //!< Y address of this generator
		uint32_t packets_out;    //!< Total packets that arrived in the ejection queue
		uint32_t packets_sent;   //!< Total packets sent injected into the network
		uint32_t packets_blocked;//!< Total packets blocked from being inserted

};

#endif

