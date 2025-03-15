#include "../../inc/base.hpp"


void log_time()
{
	log( "< clock time", INFO );
}

bool log( strstr msg, log_level_e lvl, objID_t id ){ return log( msg.str().c_str(), lvl, id ); }
bool log( string msg, log_level_e lvl, objID_t id ){ return log( msg.c_str(), lvl, id ); }
bool log( const char *msg, log_level_e lvl, objID_t id )
{
	if ( lvl > LOG_LVL ) return EXIT_FAILURE;

	cout << get_time_str() << " ";

	switch ( lvl )
	{
		case DEBUG: cout << CLR_BLU << "[DEBUG] " << CLR_RST << msg; break;
		case INFO:  cout << CLR_GRN << "[INFO]  " << CLR_RST << msg; break;
		case WARN:  cout << CLR_YEL << "[WARN]  " << CLR_RST << msg; break;
		case ERROR: cout << CLR_RED << "[ERROR] " << CLR_RST << msg; break;
		default:    cout << CLR_MAG << "[?????] " << CLR_RST << msg; break;
	}

	if ( SHOW_OBJ_MSG && id > 0 ) cout << CLR_LGR << " [" << id << "]" << CLR_RST;

	cout << endl;

	return EXIT_SUCCESS;
}