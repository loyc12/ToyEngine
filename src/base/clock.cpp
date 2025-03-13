#include "../../inc/deps.hpp"
#include <cstdio>

clock_t start_time;
struct timespec clock_res;
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
	start_time = clock();
	clock_getres( CLOCK_REALTIME, &clock_res );

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
	std::stringstream ss;
	ss << std::setfill( '0' );

	clock_t time = get_time();

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
	stringstream ss;
	clock_t time = get_time();

	uint seconds = time / clock_per_sec;
	ss << seconds << ".";
	time -= seconds * clock_per_sec;

	uint microseconds = time / clock_per_micro;
	ss << std::setfill( '0' ) << std::setw( 6 ) << microseconds;

	return ss.str();
}

ulong  get_time() { return ( double )( clock() - start_time ); }
ulong  get_time_since( clock_t start ) { return ( double )( clock() - start ); }
ulong  get_time_diff( clock_t start, clock_t end ) { return ( double )( end - start ); }