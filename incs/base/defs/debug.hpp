#ifndef DEBUG_HPP
# define DEBUG_HPP

# include "./_libs.hpp"
# include "./_colour.hpp"
# include "./clock.hpp"

typedef enum
{
	ERROR,
	WARN,
	INFO,
	DEBUG,
} log_level_e;

#define LOG_LVL DEBUG // DEBUG, INFO, WARN, ERROR ( each level excludes the previous one(s) )
#define LOG_FILE false
#define LOG_TIME true
#define SHOW_OBJ_MSG false

void log_time();
bool log( ostrs msg, log_level_e lvl = DEBUG, objID_t id = 0 );
bool log( string msg, log_level_e lvl = DEBUG, objID_t id = 0 );
bool log( const char *msg, log_level_e lvl = DEBUG, objID_t id = 0 );

// divtest.hpp

class FixedPoint; typedef FixedPoint fixed_t; // DUPLICATE from types.hpp

bool diverror( const char *dividend, const char *divisor );

bool divtest( byte_t d );
bool divtest( word_t d );
bool divtest( short d );
bool divtest( int d );
bool divtest( long d );
bool divtest( uint32_t d );
bool divtest( uint64_t d );
bool divtest( fixed_t d );

bool divtest( float d );
bool divtest( double d );
bool divtest( long double d );

#endif // DEBUG_HPP