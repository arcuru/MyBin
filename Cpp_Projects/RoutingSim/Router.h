#ifndef ROUTER_H
#define ROUTER_H

class Router
{
	public:
		Router (uint32_t X, uint32_t Y);
		~Router ();

		void Connect( Direction edge, PacketGen* target);
		EventTarget* GetTarget ( Direction edge );
		uint32_t GetCollisions ( );
		void Process ( );

	protected:

	private:
		InputBuffer ibuf[4];       //!< Input buffers situated in this router
		OutputBuffer obuf[4];      //!< Output buffers situated in this router
		uint32_t addr_x;           //!< X value of address for this router
		uint32_t addr_y;           //!< Y value of address for this router
		uint32_t packet_collision; //!< Count of packet collisions

};

#endif

