#include "../../inc/base.hpp"


void log_time()
{
	log( "< clock time", INFO );
}

int log( strstr msg, log_level_e lvl ){ return log( msg.str().c_str(), lvl ); }
int log( string msg, log_level_e lvl ){ return log( msg.c_str(), lvl ); }
int log( const char *msg, log_level_e lvl )
{
	if ( lvl > LOG_LVL ) return 1;
	switch ( lvl )
	{
		case DEBUG: cout << get_time_str() << " " << CLR_BLU << "[DEBUG] " << CLR_RST << msg << endl; break;
		case INFO:  cout << get_time_str() << " " << CLR_GRN << "[INFO]  " << CLR_RST << msg << endl; break;
		case WARN:  cout << get_time_str() << " " << CLR_YEL << "[WARN]  " << CLR_RST << msg << endl; break;
		case ERROR: cout << get_time_str() << " " << CLR_RED << "[ERROR] " << CLR_RST << msg << endl; break;
		default:    cout << get_time_str() << " " << CLR_MAG << "[?????] " << CLR_RST << msg << endl;
	}
	return 0;
}

bool divtest( byte_t d )
{
	if ( d == 0 )
	{
		log( "Trying to divide a byte_t by zero", ERROR );
		return true;
	}
	return false;
}

bool divtest( word_t d )
{
	if ( d == 0 )
	{
		log( "Trying to divide a word_t by zero", ERROR );
		return true;
	}
	return false;
}

bool divtest( short d )
{
	if ( d == 0 )
	{
		log( "Trying to divide a short by zero", ERROR );
		return true;
	}
	return false;
}

bool divtest( int d )
{
	if ( d == 0 )
	{
		log( "Trying to divide an int by zero", ERROR );
		return true;
	}
	return false;
}

bool divtest( long d )
{
	if ( d == 0 )
	{
		log( "Trying to divide a long by zero", ERROR );
		return true;
	}
	return false;
}

bool divtest( float d )
{
	if ( d == 0.0f )
	{
		log( "Trying to divide a float by zero", ERROR );
		return true;
	}
	if ( d == NAN )
	{
		log( "Trying to divide a float by NAN", ERROR );
		return true;
	}
	if ( d == INFINITY )
	{
		log( "Trying to divide a float by INFINITY", ERROR );
		return true;
	}
	if ( d == -INFINITY )
	{
		log( "Trying to divide a float by -INFINITY", ERROR );
		return true;
	}
	return false;
}

bool divtest( double d )
{
	if ( d == 0.0 )
	{
		log( "Trying to divide a double by zero", ERROR );
		return true;
	}
	if ( d == NAN )
	{
		log( "Trying to divide a double by NAN", ERROR );
		return true;
	}
	if ( d == INFINITY )
	{
		log( "Trying to divide a double by INFINITY", ERROR );
		return true;
	}
	if ( d == -INFINITY )
	{
		log( "Trying to divide a double by -INFINITY", ERROR );
		return true;
	}
	return false;
}