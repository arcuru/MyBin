#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <sys/time.h>

/*!	\class Timer
 *
 *	Implementation of a simple timer class able to save and print the current time and act as a timer.
 *
 */
class Timer
{
	public:
		/* ====================  LIFECYCLE     ======================================= */
		Timer ();                             /* constructor      */
		Timer ( const Timer &other );   /* copy constructor */
		~Timer ();                            /* destructor       */

		/* ====================  ACCESSORS     ======================================= */
		inline timeval get_StartTime() const;		//!< Return the start time
		inline timeval get_EndTime() const;			//!< Return the end time
		inline void set_StartTime(timeval value);	//!< Manually set the start time
		inline void set_EndTime(timeval value);		//!< Manually set the end time
		double get_Time() const;					//!< Get the difference in seconds

		/* ====================  MUTATORS      ======================================= */
		void Start();								//!< Start the timer
		void End();									//!< Stop the timer

		/* ====================  OPERATORS     ======================================= */

		Timer& operator = ( const Timer &other );	//!< Assignment operator
		friend std::ostream& operator << (std::ostream &os, const Timer& t);

	protected:
		/* ====================  DATA MEMBERS  ======================================= */
		timeval StartTime;							//!< Start of timer
		timeval EndTime;							//!< End time

	private:
		/* ====================  DATA MEMBERS  ======================================= */

};

#endif
