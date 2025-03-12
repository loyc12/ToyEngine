#ifndef CLOCK_HPP
# define CLOCK_HPP

# include "./_libs.hpp"

extern clock_t start_time;
extern struct timespec clock_res;

extern time_t clock_per_micro;
extern time_t clock_per_milli;
extern time_t clock_per_sec;
extern time_t clock_per_min;
extern time_t clock_per_hour;
extern time_t clock_per_day;
extern time_t clock_per_week;
extern time_t clock_per_year;

void start_clock();
ulong get_time();
ulong get_time_since( clock_t start );
ulong get_time_diff( clock_t start, clock_t end );

string get_time_str();
string get_time_str_raw();

#endif // CLOCK_HPP