#include "Timer.h"

/*!	Default constructor that does nothing
 */
Timer::Timer ()
{
}

/*!
 * 	\param	other	Timer object to copy
 */
Timer::Timer ( const Timer &other )
{
	StartTime = other.StartTime;
	EndTime = other.EndTime;
}

/*!	Class destructor that does nothing
 */
Timer::~Timer ()
{
}

/*!	Directly retrieve a copy of the StartTime variable
 * 	
 * 	\returns	Timeval object of the start of the timer
 */
inline timeval Timer::get_StartTime (  ) const
{
	return StartTime;
}

/*!	Directly set the starting time for the timer to a given timeval
 *
 *	\param	value	Time to assign to StartTime
 */
inline void Timer::set_StartTime ( timeval value )
{
	StartTime = value;
	return ;
}

/*!	Directly retrieve a copy of the EndTime variable
 * 	
 * 	\returns	Timeval object of the end of the timer
 */
inline timeval Timer::get_EndTime (  ) const
{
	return EndTime;
}

/*!	Directly set the ending time for the timer to a given timeval
 *
 *	\param	value	Time to assign to EndTime
 */
inline void Timer::set_EndTime ( timeval value )
{
	EndTime = value;
	return ;
}

/*!	Retrieve the time in seconds between Start and End
 *	
 *	\returns	Time in seconds with microsecond resolution
 */
double Timer::get_Time ( ) const
{
	double out = (EndTime.tv_sec - StartTime.tv_sec);
	out += (double)(EndTime.tv_usec - StartTime.tv_usec) / 1000000.0;
	return out;
}

/*!	Set the current time to the start of the timer
 */
void Timer::Start ( )
{
    gettimeofday(&StartTime, 0);
	return ;
}

/*!	Set the current time to the end of the timer
 */
void Timer::End ( )
{
    gettimeofday(&EndTime, 0);
	return ;
}

/*!	Assign the value in other to the current object
 *	
 *	\param	other	Object to get assignments from
 *	\returns		Reference to this object
 */
Timer& Timer::operator = ( const Timer &other )
{
	if ( this != &other ) {
		StartTime = other.StartTime;
		EndTime = other.EndTime;
	}
	return *this;
}

/*!	Default print this object to the command line
 * 	
 * 	\param	os	Output stream
 * 	\param	t	Timer to print
 * 	\returns	Reference to output stream
 */
std::ostream& operator << ( std::ostream &os, const Timer& t )
{
	os << t.get_Time();
	return os;
}

