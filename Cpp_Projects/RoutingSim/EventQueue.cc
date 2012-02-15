#include "Global.h"

struct sll_t {
	Packet p;
	EventTarget* t;
	uint32_t arrival;
	struct sll_t* next;
};

typedef struct sll_t sll_t;

EventQueue::EventQueue ()
{
	head = NULL;
}

EventQueue::~EventQueue ()
{
	Clear();
}

/** Add
 *  schedules a new event
 *
 *  @arg p       Packet to be delivered
 *  @arg target  Device that will receive the packet
 *  @arg arrival Arrival time step
 */
void EventQueue::Add ( Packet p, EventTarget* target, uint32_t arrival )
{
	assert(target);
	sll_t* n = (sll_t*) malloc(sizeof(sll_t));
	n->p = p;
	n->t = target;
	n->arrival = arrival;
	n->next = NULL;
	if (head) {
		if (n->arrival < head->arrival) {
			n->next = head;
			head = n;
		}
		else {
			sll_t* cur = head;
			while (cur->next && cur->next->arrival < n->arrival)
				cur = cur->next;
			n->next = cur->next;
			cur->next = n;
		}
	}
	else
		head = n;
	return ;
}

/** Process
 *  deals with all of the events at the current time step
 */
void EventQueue::Process ( )
{
	while (head && head->arrival <= Global_Time) {
		assert(head->arrival == Global_Time);
		assert(head->t);
		head->t->ProcessPacket(head->p);
		sll_t* tmp = head->next;
		free(head);
		head = tmp;
	}
	return ;
}

/** Clear
 *  removes all leftover elements in the queue
 *
 */
void EventQueue::Clear ( )
{
	while (head) {
		sll_t* tmp = head->next;
		free(head);
		head = tmp;
	}
}

