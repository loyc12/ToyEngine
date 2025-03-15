#include "../../inc/base.hpp"

bool diverror( const char *dividend, const char *divisor ){ log( "Trying to divide " + string( dividend ) + " by " + string( divisor ), ERROR ); return true; }

bool divtest( byte_t d   ){ if ( d == 0 ){ return diverror( "a byte_t",   "zero" ); } return false; }
bool divtest( word_t d   ){ if ( d == 0 ){ return diverror( "a word_t",   "zero" ); } return false; }
bool divtest( short d    ){ if ( d == 0 ){ return diverror( "a short",    "zero" ); } return false; }
bool divtest( int d      ){ if ( d == 0 ){ return diverror( "an int",     "zero" ); } return false; }
bool divtest( long d     ){ if ( d == 0 ){ return diverror( "a long",     "zero" ); } return false; }
bool divtest( uint32_t d ){ if ( d == 0 ){ return diverror( "a uint32_t", "zero" ); } return false; }
bool divtest( uint64_t d ){ if ( d == 0 ){ return diverror( "a uint64_t", "zero" ); } return false; }
bool divtest( fixed_t d  ){ if ( d == 0 ){ return diverror( "a fixed_t",  "zero" ); } return false; }

bool divtest( float d )
{
	if ( d == 0.0f ){ diverror( "a float", "zero" ); return true; }
	if ( d == NAN  ){ diverror( "a float", "NAN" );  return true; }
	if ( d == INFINITY  ){ diverror( "a float", "INFINITY" );  return true; }
	if ( d == -INFINITY ){ diverror( "a float", "-INFINITY" ); return true; }
	return false;
}

bool divtest( double d )
{
	if ( d == 0.0 ){ diverror( "a double", "zero" ); return true; }
	if ( d == NAN ){ diverror( "a double", "NAN" );  return true; }
	if ( d == INFINITY  ){ diverror( "a double", "INFINITY" );  return true; }
	if ( d == -INFINITY ){ diverror( "a double", "-INFINITY" ); return true; }
	return false;
}

bool divtest( long double d )
{
	if ( d == 0.0 ){ diverror( "a long double", "zero" ); return true; }
	if ( d == NAN ){ diverror( "a long double", "NAN" );  return true; }
	if ( d == INFINITY  ){ diverror( "a long double", "INFINITY" );  return true; }
	if ( d == -INFINITY ){ diverror( "a long double", "-INFINITY" ); return true; }
	return false;
}
