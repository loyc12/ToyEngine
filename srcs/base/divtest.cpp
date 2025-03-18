#include "../../incs/base.hpp"

bool diverror( const char *dividend, const char *divisor ){ log( "Trying to divide " + string( dividend ) + " by " + string( divisor ), ERROR ); return EXIT_FAILURE; }

bool divtest( byte_t d   ){ if ( d == 0 ){ return diverror( "a byte_t",   "zero" ); } return EXIT_SUCCESS; }
bool divtest( word_t d   ){ if ( d == 0 ){ return diverror( "a word_t",   "zero" ); } return EXIT_SUCCESS; }
bool divtest( short d    ){ if ( d == 0 ){ return diverror( "a short",    "zero" ); } return EXIT_SUCCESS; }
bool divtest( int d      ){ if ( d == 0 ){ return diverror( "an int",     "zero" ); } return EXIT_SUCCESS; }
bool divtest( long d     ){ if ( d == 0 ){ return diverror( "a long",     "zero" ); } return EXIT_SUCCESS; }
bool divtest( uint32_t d ){ if ( d == 0 ){ return diverror( "a uint32_t", "zero" ); } return EXIT_SUCCESS; }
bool divtest( uint64_t d ){ if ( d == 0 ){ return diverror( "a uint64_t", "zero" ); } return EXIT_SUCCESS; }
bool divtest( fixed_t d  ){ if ( d == 0 ){ return diverror( "a fixed_t",  "zero" ); } return EXIT_SUCCESS; }

bool divtest( float d )
{
	if ( d == 0.0f ){ diverror( "a float", "zero" ); return EXIT_FAILURE; }
	if ( d == NAN  ){ diverror( "a float", "NAN" );  return EXIT_FAILURE; }
	if ( d == INFINITY  ){ diverror( "a float", "INFINITY" );  return EXIT_FAILURE; }
	if ( d == -INFINITY ){ diverror( "a float", "-INFINITY" ); return EXIT_FAILURE; }
	return EXIT_SUCCESS;
}

bool divtest( double d )
{
	if ( d == 0.0 ){ diverror( "a double", "zero" ); return EXIT_FAILURE; }
	if ( d == NAN ){ diverror( "a double", "NAN" );  return EXIT_FAILURE; }
	if ( d == INFINITY  ){ diverror( "a double", "INFINITY" );  return EXIT_FAILURE; }
	if ( d == -INFINITY ){ diverror( "a double", "-INFINITY" ); return EXIT_FAILURE; }
	return EXIT_SUCCESS;
}

bool divtest( long double d )
{
	if ( d == 0.0 ){ diverror( "a long double", "zero" ); return EXIT_FAILURE; }
	if ( d == NAN ){ diverror( "a long double", "NAN" );  return EXIT_FAILURE; }
	if ( d == INFINITY  ){ diverror( "a long double", "INFINITY" );  return EXIT_FAILURE; }
	if ( d == -INFINITY ){ diverror( "a long double", "-INFINITY" ); return EXIT_FAILURE; }
	return EXIT_SUCCESS;
}
