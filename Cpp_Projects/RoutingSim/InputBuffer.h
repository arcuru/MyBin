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
		void RoutePacket ( uint32_t router_x, uint32_t router_y );
		Direction GetRoute ( );
		size_t Routed ( );
		void ProcessPacket(Packet p);

	protected:

	private:
		Direction* routes;   //!< Buffer holding the routes of all the packets
		OutputBuffer* obuf;  //!< Paired Output Buffer for writeback information
		int buf_route;       //!< Pointer to next buffer space that needs to be routed

};

#endif

