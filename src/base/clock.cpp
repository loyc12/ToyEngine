#include "../../inc/base.hpp"
#include <bits/types/struct_timeval.h>

struct timeval start_time;
time_t clock_per_micro;
time_t clock_per_milli;
time_t clock_per_sec;
time_t clock_per_min;
time_t clock_per_hour;
time_t clock_per_day;
time_t clock_per_week;
time_t clock_per_year;

void start_clock()
{
	gettimeofday( &start_time, NULL );

	clock_per_micro = 1;
	clock_per_milli = clock_per_micro * 1000;
	clock_per_sec = clock_per_milli * 1000;
	clock_per_min = clock_per_sec * 60;
	clock_per_hour = clock_per_min * 60;
	clock_per_day = clock_per_hour * 24;
	clock_per_week = clock_per_day * 7;
	clock_per_year = clock_per_day * 365;

	log( "Clock started", INFO );
}

string get_time_str()
{
	strstr ss;
	ss << std::setfill( '0' );

	ulong time = get_runtime();

	// uint years = time / clock_per_year;
	// ss << years << "y";
	// time -= years * clock_per_year;

	//uint days = time / clock_per_day;
	//ss << std::setw( 3 ) << days << "d";
	//time -= days * clock_per_day;

	//uint hours = time / clock_per_hour;
	//ss << std::setw( 2 ) << hours << "h";
	//time -= hours * clock_per_hour;

	uint minutes = time / clock_per_min;
	ss << std::setw( 2 ) << minutes << "m";
	time -= minutes * clock_per_min;

	uint seconds = time / clock_per_sec;
	ss << std::setw( 2 ) << seconds << "s";
	time -= seconds * clock_per_sec;

	//uint milliseconds = time / clock_per_milli;
	//ss << std::setw( 3 ) << milliseconds << "ms";
	//time -= milliseconds * clock_per_milli;

	uint microseconds = time / clock_per_micro;
	ss << std::setw( 6 ) << microseconds << "us";

	return ss.str();
}
string get_time_str_raw()
{
	strstr ss;
	ulong time = get_runtime();

	uint seconds = time / clock_per_sec;
	ss << seconds << ".";
	time -= seconds * clock_per_sec;

	uint microseconds = time / clock_per_micro;
	ss << std::setfill( '0' ) << std::setw( 6 ) << microseconds;

	return ss.str();
}

ulong get_time_diff( struct timeval start, struct timeval end )
{
  time_t sec_diff = end.tv_sec - start.tv_sec;
  suseconds_t usec_diff = end.tv_usec - start.tv_usec;

  return sec_diff * clock_per_sec + usec_diff; // Microseconds
}
ulong get_time_since( struct timeval since )
{
	struct timeval now;
	gettimeofday( &now, NULL );

	return get_time_diff( since, now );
}
ulong get_runtime()
{
	return get_time_since( start_time );
}
