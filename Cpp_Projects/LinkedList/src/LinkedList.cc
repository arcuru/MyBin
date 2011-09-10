#include "LinkedList.h"
#include <cstdlib>

#define DEBUG
#ifdef DEBUG
	#include <iostream>
	using namespace std;
#endif

#ifndef NULL
	#define NULL 0
#endif

/*
 *--------------------------------------------------------------------------------------
 *       Class:  LinkedList
 *      Method:  LinkedList
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
LinkedList::LinkedList ( queue_type init )
{
	type = init;
	length = 0;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  LinkedList
 *      Method:  LinkedList
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
LinkedList::LinkedList ( const LinkedList &other )
{
	type = other.get_type();
	length = 0;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  LinkedList
 *      Method:  ~LinkedList
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
LinkedList::~LinkedList ()
{
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  LinkedList
 *      Method:  get_length
 *--------------------------------------------------------------------------------------
 */
inline int LinkedList::get_length (  ) const
{
	return length;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  LinkedList
 *      Method:  get_type
 *--------------------------------------------------------------------------------------
 */
inline queue_type LinkedList::get_type (  ) const
{
	return type;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  LinkedList
 *      Method:  set_type
 *--------------------------------------------------------------------------------------
 */
inline void LinkedList::set_type ( queue_type value )
{
	type = value;
	return ;
}

void LinkedList::Push ( void* info )
{
	if ( FIFO == type || FILO == type )
		return PushBack(info);
	else if ( LIFO == type || LILO == type )
		return PushFront(info);
	return ;
}

void* LinkedList::Pop ( )
{
	if ( FIFO == type || LIFO == type )
		return PopFront();
	else if ( FILO == type || LILO == type )
		return PopBack();
	return NULL;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  LinkedList
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
LinkedList& LinkedList::operator = ( const LinkedList &other )
{
	if ( this != &other ) {
		this->type = other.type;
		this->length = other.length;
	}
	return *this;
}

