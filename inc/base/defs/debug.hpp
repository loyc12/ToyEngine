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

int log( const char *msg, log_level_e lvl = DEBUG );

bool divtest( byte_t d );
bool divtest( word_t d );
bool divtest( short d );
bool divtest( int d );
bool divtest( long d );
bool divtest( float d );
bool divtest( double d );

#endif // DEBUG_HPP