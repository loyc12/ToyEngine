#include "../../incs/base.hpp"

time_t clock_per_micro = 1; // implied by the use of timeval
time_t clock_per_milli = clock_per_micro * 1000;
time_t clock_per_sec   = clock_per_milli * 1000;
time_t clock_per_min   = clock_per_sec   * 60;
time_t clock_per_hour  = clock_per_min   * 60;
time_t clock_per_day   = clock_per_hour  * 24;
time_t clock_per_week  = clock_per_day   * 7;
time_t clock_per_year  = clock_per_day   * 365.2422;

struct timeval clock_start_time;
bool clock_started = false;

struct timeval &start_clock()
{
	if ( clock_started ){ qlog( "start_clock : Clock already started", WARN, 0 ); return clock_start_time; }

	gettimeofday( &clock_start_time, NULL );

	clock_started = true;
	qlog( "start_clock : Clock started", INFO, 0 );
	return clock_start_time;
}

struct timeval &get_start_time()
{
	if ( !clock_started ){ start_clock(); }
	return clock_start_time;
}

string get_time_str()
{
	if ( !clock_started ){ start_clock(); }

	ostrs out; out << std::setfill( '0' );

	ulong time = get_runtime();

	// uint years = time / clock_per_year;
	// out << years << "y";
	// time -= years * clock_per_year;

	//uint days = time / clock_per_day;
	//out << std::setw( 3 ) << days << "d";
	//time -= days * clock_per_day;

	//uint hours = time / clock_per_hour;
	//out << std::setw( 2 ) << hours << "h";
	//time -= hours * clock_per_hour;

	uint minutes = time / clock_per_min;
	out << std::setw( 2 ) << minutes << "m";
	time -= minutes * clock_per_min;

	uint seconds = time / clock_per_sec;
	out << std::setw( 2 ) << seconds << "s";
	time -= seconds * clock_per_sec;

	//uint milliseconds = time / clock_per_milli;
	//out << std::setw( 3 ) << milliseconds << "ms";
	//time -= milliseconds * clock_per_milli;

	uint microseconds = time / clock_per_micro;
	out << std::setw( 6 ) << microseconds << "us";

	return out.str();
}
string get_time_str_raw()
{
	if ( !clock_started ){ qlog( "get_time_str_raw : Clock not yet started : Starting it now", WARN, 0 ); start_clock(); }

	ostrs out;
	ulong time = get_runtime();

	uint seconds = time / clock_per_sec;
	out << seconds << ".";
	time -= seconds * clock_per_sec;

	uint microseconds = time / clock_per_micro;
	out << std::setfill( '0' ) << std::setw( 6 ) << microseconds;

	return out.str();
}
string get_start_time_str()
{
	if ( !clock_started ){ qlog( "get_start_time_str : Clock not yet started : Starting it now", WARN, 0 ); start_clock(); }

	ostrs out; out << std::setfill( '0' );

	struct tm *timeinfo = localtime( &get_start_time().tv_sec );

	out << timeinfo->tm_year - 100; // epoch is 2000 now
	out << std::setw( 2 ) << timeinfo->tm_mon + 1; // month is 0-indexed, unlike the rest
	out << std::setw( 2 ) << timeinfo->tm_mday << "_";
	out << std::setw( 2 ) << timeinfo->tm_hour;
	out << std::setw( 2 ) << timeinfo->tm_min;
	out << std::setw( 2 ) << timeinfo->tm_sec;

	return out.str();
}


ulong get_time_diff( struct timeval &start, struct timeval &end )
{
  time_t sec_diff = end.tv_sec - start.tv_sec;
  suseconds_t usec_diff = end.tv_usec - start.tv_usec;

  return sec_diff * clock_per_sec + usec_diff; // Microseconds
}
ulong get_time_since( struct timeval &since )
{
	struct timeval now;
	gettimeofday( &now, NULL );

	return get_time_diff( since, now );
}
ulong get_runtime()
{
	return get_time_since( get_start_time() );
}

