#include "../../incs/base.hpp"

bool diverror( const char *dividend, const char *divisor ){ log( "Trying to divide " + string( dividend ) + " by " + string( divisor ), ERROR ); return false; }

bool divtest( byte_t d   ){ if ( d == 0 ){ return diverror( "a byte_t",   "zero" ); } return true; }
bool divtest( word_t d   ){ if ( d == 0 ){ return diverror( "a word_t",   "zero" ); } return true; }
bool divtest( short d    ){ if ( d == 0 ){ return diverror( "a short",    "zero" ); } return true; }
bool divtest( int d      ){ if ( d == 0 ){ return diverror( "an int",     "zero" ); } return true; }
bool divtest( long d     ){ if ( d == 0 ){ return diverror( "a long",     "zero" ); } return true; }
bool divtest( uint32_t d ){ if ( d == 0 ){ return diverror( "a uint32_t", "zero" ); } return true; }
bool divtest( uint64_t d ){ if ( d == 0 ){ return diverror( "a uint64_t", "zero" ); } return true; }
bool divtest( fixed_t d  ){ if ( d == 0 ){ return diverror( "a fixed_t",  "zero" ); } return true; }

bool divtest( float d )
{
	if ( d == 0.0f ){ diverror( "a float", "zero" ); return false; }
	if ( d == NAN  ){ diverror( "a float", "NAN" );  return false; }
	if ( d == INFINITY  ){ diverror( "a float", "INFINITY" );  return false; }
	if ( d == -INFINITY ){ diverror( "a float", "-INFINITY" ); return false; }
	return true;
}

bool divtest( double d )
{
	if ( d == 0.0 ){ diverror( "a double", "zero" ); return false; }
	if ( d == NAN ){ diverror( "a double", "NAN" );  return false; }
	if ( d == INFINITY  ){ diverror( "a double", "INFINITY" );  return false; }
	if ( d == -INFINITY ){ diverror( "a double", "-INFINITY" ); return false; }
	return true;
}

bool divtest( long double d )
{
	if ( d == 0.0 ){ diverror( "a long double", "zero" ); return false; }
	if ( d == NAN ){ diverror( "a long double", "NAN" );  return false; }
	if ( d == INFINITY  ){ diverror( "a long double", "INFINITY" );  return false; }
	if ( d == -INFINITY ){ diverror( "a long double", "-INFINITY" ); return false; }
	return true;
}
