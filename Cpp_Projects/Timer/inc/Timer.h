#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <sys/time.h>

class Timer
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		Timer ();                             /* constructor      */
		Timer ( const Timer &other );   /* copy constructor */
		~Timer ();                            /* destructor       */

		/* ====================  ACCESSORS     ======================================= */
		inline timeval get_StartTime() const;
		inline timeval get_EndTime() const;
		inline void set_StartTime(timeval value);
		inline void set_EndTime(timeval value);
		
		double get_Time() const;

		/* ====================  MUTATORS      ======================================= */
		void Start();
		void End();

		/* ====================  OPERATORS     ======================================= */

		Timer& operator = ( const Timer &other ); /* assignment operator */
		friend std::ostream& operator << (std::ostream &os, const Timer& t);

	protected:
		/* ====================  DATA MEMBERS  ======================================= */
		timeval StartTime;
		timeval EndTime;

	private:
		/* ====================  DATA MEMBERS  ======================================= */

};

#endif
