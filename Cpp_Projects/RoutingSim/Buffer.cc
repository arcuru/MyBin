#include "Global.h"

Buffer::Buffer ()
{
	buf_index = 0;
	buf_valid = -1;
	buf_size = 4;
	buf = (Packet*) malloc(sizeof(Packet) * buf_size);
}

Buffer::Buffer ( size_t entries )
{
	buf_index = 0;
	buf_valid = -1;
	buf_size = entries;
	buf = (Packet*) malloc(sizeof(Packet) * buf_size);
}

Buffer::~Buffer ()
{
	free(buf);
}

/** Size
 *  returns the size of the buffer
 *
 *  @return Size of buffer
 */
uint32_t Buffer::Size ( )
{
	return buf_size;
}

/** ProcessPacket
 *  handles an incoming packet by adding it to the buffer
 *
 *  @p  Packet to add into buffer
 */
void Buffer::ProcessPacket ( Packet p )
{
	if (buf_index == buf_valid) {
		// Buffer full
		assert(false);
		return ;
	}
	if (buf_index < 0)
		assert(false);
	buf[buf_index] = p;
	if (-1 == buf_valid)
		buf_valid = buf_index;
	buf_index++;
	buf_index %= buf_size;
	return ;
}

/** PopPacket
 *  delete the oldest packet in buffer
 *
 */
void Buffer::PopPacket ( )
{
	if (-1 == buf_valid) {
		// No valid packets
		assert(false);
		return ;
	}
	buf_valid++;
	buf_valid %= buf_size;
	if (buf_valid == buf_index) {
		buf_valid = -1;
	}
	return ;
}

/** GetPacket
 *  retrieve oldest packet in buffer
 *
 *  @return Oldest packet in buffer
 */
Packet Buffer::GetPacket ( )
{
	if (-1 == buf_valid) {
		// No valid packets
		assert(false);
	}
	return buf[buf_valid];
}

/** PacketsRemaining
 *  returns the number of packets stored in the buffer
 *
 *  @return Number of packets in the buffer
 */
uint32_t Buffer::PacketsRemaining ( )
{
	if (-1 == buf_valid)
		return 0;
	int tmp = buf_index;
	if (tmp <= buf_valid)
		tmp += buf_size;
	return tmp - buf_valid;
}
