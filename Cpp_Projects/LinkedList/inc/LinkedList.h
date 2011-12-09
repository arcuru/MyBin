
/*
 * =====================================================================================
 *        Class:  LinkedList
 *  Description:  Base Class for linked lists
 * =====================================================================================
 */

typedef enum queue_type {
	FIFO,
	FILO,
	LIFO,
	LILO
} queue_type;

class LinkedList
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		LinkedList ( queue_type init = LIFO );                             /* constructor      */
		LinkedList ( const LinkedList &other );   /* copy constructor */
		~LinkedList ();                            /* destructor       */

		/* ====================  ACCESSORS     ======================================= */
		inline int get_length() const;
		inline queue_type get_type() const;
		inline void set_type( queue_type value );

		/* ====================  MUTATORS      ======================================= */
		void Push( void* info );
		virtual void PushFront( void* info ) = 0;
		virtual void PushBack( void* info ) = 0;
		void* Pop();
		virtual void* PopFront() = 0;
		virtual void* PopBack() = 0;

		/* ====================  OPERATORS     ======================================= */

		LinkedList& operator = ( const LinkedList &other ); /* assignment operator */

	protected:
		/* ====================  DATA MEMBERS  ======================================= */
		int length;
		queue_type type;

	private:
		/* ====================  DATA MEMBERS  ======================================= */

};

