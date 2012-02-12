#ifndef ROUTER_H
#define ROUTER_H

class Router
{
	public:
		Router (uint32_t X, uint32_t Y);
		~Router ();

		void Connect( Direction edge, PacketGen* target);
		EventTarget* GetTarget ( Direction edge );
		void Process ( );

	protected:

	private:
		InputBuffer ibuf[4];
		OutputBuffer obuf[4];
		uint32_t addr_x;
		uint32_t addr_y;
		uint32_t packets_routed;
		uint32_t packet_collision;

};

#endif

