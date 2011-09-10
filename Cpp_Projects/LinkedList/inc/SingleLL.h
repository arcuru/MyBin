
/*
 * =====================================================================================
 *        Class:  SingleLL
 *  Description:  Implementation of a singley linked list
 * =====================================================================================
 */
#include "LinkedList.h"

struct sll_t;

class SingleLL : public LinkedList
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		SingleLL ( queue_type init = LIFO );                             /* constructor      */
		SingleLL ( const SingleLL &other );   /* copy constructor */
		~SingleLL ();                            /* destructor       */

		/* ====================  ACCESSORS     ======================================= */

		/* ====================  MUTATORS      ======================================= */
		void PushFront( void* info );
		void PushBack( void* info );
		void* PopFront();
		void* PopBack();

		/* ====================  OPERATORS     ======================================= */

		SingleLL& operator = ( const SingleLL &other ); /* assignment operator */

	protected:
		/* ====================  DATA MEMBERS  ======================================= */
		sll_t* head;

	private:
		/* ====================  DATA MEMBERS  ======================================= */

};

