#ifndef DEBUG_HPP
# define DEBUG_HPP

# include "./_libs.hpp"
# include "./_colour.hpp"
# include "./clock.hpp"

typedef enum
{
	NONE = 0,
	ERROR,
	WARN,
	INFO,
	DEBUG,
	FUNCT,
} log_level_e;

# define LOG_LVL_NONE  0
# define LOG_LVL_ERROR 1
# define LOG_LVL_WARN  2
# define LOG_LVL_INFO  3
# define LOG_LVL_DEBUG 4
# define LOG_LVL_FUNCT 5

#	define LOG_LVL 4 // NONE, DEBUG, INFO, WARN, ERROR, FUNCT ( each level includes the previous one(s) )

#	define HERE __FILE__, __LINE__

#	define LOG_FILE false
#	define LOG_TIME true
#	define LOG_LINE true
#	define SHOW_OBJ_MSG true

#	if LOG_LVL > LOG_LVL_NONE
#	 define qlog( msg, lvl, id ) log( msg, lvl, id, HERE )
#	else
#	 define qlog( msg, lvl, id ) ;
#	endif

#	if LOG_LVL == LOG_LVL_FUNCT
#	 define flog( id ) log( __FUNCTION__, FUNCT, id, HERE )
#	else
#	 define flog( id ) ;
#	endif

void log_time();
bool log( ostrs msg,       log_level_e lvl = DEBUG, objID_t id = 0, const char *file = nullptr, int line = 0 );
bool log( string msg,      log_level_e lvl = DEBUG, objID_t id = 0, const char *file = nullptr, int line = 0 );
bool log( const char *msg, log_level_e lvl = DEBUG, objID_t id = 0, const char *file = nullptr, int line = 0 );

// divtest.hpp

class FixedPoint; typedef FixedPoint fixed_t; // DUPLICATE from types.hpp

bool diverror( const char *dividend, const char *divisor );

bool divtest( byte_t   d );
bool divtest( word_t   d );
bool divtest( short    d );
bool divtest( int      d );
bool divtest( long     d );
bool divtest( uint32_t d );
bool divtest( uint64_t d );
bool divtest( fixed_t  d );

bool divtest( float       d );
bool divtest( double      d );
bool divtest( long double d );

#endif // DEBUG_HPP