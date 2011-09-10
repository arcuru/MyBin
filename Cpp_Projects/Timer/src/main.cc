#include "Timer.h"

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Timer
 *      Method:  Timer
 * Description:  constructor
 *--------------------------------------------------------------------------------------
 */
Timer::Timer ()
{
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Timer
 *      Method:  Timer
 * Description:  copy constructor
 *--------------------------------------------------------------------------------------
 */
Timer::Timer ( const Timer &other )
{
	StartTime = other.StartTime;
	EndTime = other.EndTime;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Timer
 *      Method:  ~Timer
 * Description:  destructor
 *--------------------------------------------------------------------------------------
 */
Timer::~Timer ()
{
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Timer
 *      Method:  get_StartTime
 *--------------------------------------------------------------------------------------
 */
inline timeval Timer::get_StartTime (  ) const
{
	return StartTime;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Timer
 *      Method:  set_StartTime
 *--------------------------------------------------------------------------------------
 */
inline void Timer::set_StartTime ( timeval value )
{
	StartTime = value;
	return ;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Timer
 *      Method:  get_EndTime
 *--------------------------------------------------------------------------------------
 */
inline timeval Timer::get_EndTime (  ) const
{
	return EndTime;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Timer
 *      Method:  set_EndTime
 *--------------------------------------------------------------------------------------
 */
inline void Timer::set_EndTime ( timeval value )
{
	EndTime = value;
	return ;
}

double Timer::get_Time ( ) const
{
	double out = (EndTime.tv_sec - StartTime.tv_sec);
	out += (EndTime.tv_usec - StartTime.tv_usec) / 1000000;
	return out;
}

void Timer::Start ( )
{
    gettimeofday(&StartTime, 0);
	return ;
}

void Timer::End ( )
{
    gettimeofday(&EndTime, 0);
	return ;
}

/*
 *--------------------------------------------------------------------------------------
 *       Class:  Timer
 *      Method:  operator =
 * Description:  assignment operator
 *--------------------------------------------------------------------------------------
 */
Timer& Timer::operator = ( const Timer &other )
{
	if ( this != &other ) {
		StartTime = other.StartTime;
		EndTime = other.EndTime;
	}
	return *this;
}

std::ostream& operator << ( std::ostream &os, const Timer& t )
{
	os << t.get_Time();
	return os;
}

