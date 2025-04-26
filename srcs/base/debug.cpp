#include "../../incs/base.hpp"


void log_time(){ log( "< clock time", INFO ); }

bool open_log_file( ofstream &log_file ) // orivate function
{
	if ( !log_file.is_open() )
	{
		printf( "Generating log file\n" );

		string file_name = "logs/" + get_start_time_str() + ".log";
		printf( "Log file name : %s\n", file_name.c_str() ); // DEBUG

		log_file.open( file_name, std::ios::out | std::ios::app );

		if ( !log_file.is_open() ){ return false; }

		printf( "Log file Generated successfully\n" );
	}
	return true;
}

bool log( ostrs msg,       log_level_e lvl, objID_t id, const char *file, int line ) { return log( msg.str().c_str(), lvl, id, file, line ); }
bool log( string msg,      log_level_e lvl, objID_t id, const char *file, int line ) { return log( msg.c_str(), lvl, id, file, line ); }
bool log( const char *msg, log_level_e lvl, objID_t id, const char *file, int line )
{
	if ( lvl > LOG_LVL )           return true;
	if ( !SHOW_OBJ_MSG && id > 0 ) return true;

	ostream *log_out = &cout;

	static bool disregard_log_file = false;

	if ( LOG_FILE && !disregard_log_file )
	{
		static ofstream log_file;
		if ( open_log_file( log_file ) == EXIT_FAILURE )
		{
			disregard_log_file = true;
			log( "Failed to open log file. Logging to console instead", ERROR );
		}
		else { log_out = &log_file; }
	}

	if ( LOG_TIME ) *log_out << get_time_str() << " ";

	static bool use_clr = ( log_out == &cout );

	switch ( lvl )
	{
		case DEBUG: *log_out << ( use_clr ? CLR_BLU : "" ) << "[DEBUG] " << ( use_clr ? CLR_RST : "" ) << msg; break;
		case INFO:  *log_out << ( use_clr ? CLR_GRN : "" ) << "[INFO]  " << ( use_clr ? CLR_RST : "" ) << msg; break;
		case WARN:  *log_out << ( use_clr ? CLR_YEL : "" ) << "[WARN]  " << ( use_clr ? CLR_RST : "" ) << msg; break;
		case ERROR: *log_out << ( use_clr ? CLR_RED : "" ) << "[ERROR] " << ( use_clr ? CLR_RST : "" ) << msg; break;
		default:    *log_out << ( use_clr ? CLR_MAG : "" ) << "[?????] " << ( use_clr ? CLR_RST : "" ) << msg; break;
	}

	if ( LOG_LINE && file != nullptr ) *log_out << " [" << file << ":" << line << "]";

	if ( id > 0 ) *log_out << ( use_clr ? CLR_LGR : "" ) << " [" << id << "]" << ( use_clr ? CLR_RST : "" );

	*log_out << endl;

	return true;
}