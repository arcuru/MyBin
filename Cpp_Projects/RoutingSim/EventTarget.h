#ifndef EVENTTARGET_H
#define EVENTTARGET_H
struct Packet;

class EventTarget
{
	public:
		EventTarget ()  {}
		~EventTarget () {}

		virtual void ProcessPacket( Packet p ) = 0;

	protected:

	private:

};

#endif
