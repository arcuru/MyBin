#ifndef PACKET_H
#define PACKET_H

class Packet
{
	public:
		Packet ( uint8_t addr_x, uint8_t addr_y, uint8_t origin_x, uint8_t origin_y, bool head, bool credit, uint32_t data);
		~Packet ();

		uint8_t GetX ( );
		uint8_t GetY ( );
		uint8_t GetOriginX ( );
		uint8_t GetOriginY ( );
		bool GetHead ( );
		bool GetCredit ( );
		uint32_t GetData ( );

	protected:

	private:
		uint64_t info;     //!< 8 bytes of information that comprise the packet

};


#endif
