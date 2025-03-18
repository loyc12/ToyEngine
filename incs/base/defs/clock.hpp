#ifndef CLOCK_HPP
# define CLOCK_HPP

# include "./_libs.hpp"

extern time_t clock_per_micro;
extern time_t clock_per_milli;
extern time_t clock_per_sec;
extern time_t clock_per_min;
extern time_t clock_per_hour;
extern time_t clock_per_day;
extern time_t clock_per_week;
extern time_t clock_per_year;

extern struct timeval clock_start_time;
extern bool clock_started;

struct timeval &start_clock();
struct timeval &get_start_time();

string get_time_str();
string get_time_str_raw();
string get_start_time_str();

ulong get_runtime();
ulong get_time_since( struct timeval &since );
ulong get_time_diff( struct timeval &start, struct timeval &end );

#endif // CLOCK_HPP