#ifndef MATH_HPP
# define MATH_HPP

# include <cmath>
# include "./_libs.hpp"

#define E		2.71828182845904523536f
#define TAU	6.28318530717958647692f
#define PHI	1.61803398874989484820f

// fabs( ), pow( ) and sqrt( ) are already defined in cmath
// floor( ), ceil( ) and round( )( ? ) are already defined in cmath

inline int    abs( int a )     { return a < 0 ? -a : a; }
inline long   abs( long a )    { return a < 0 ? -a : a; }
inline float  abs( float a )   { return a < 0 ? -a : a; }
inline double abs( double a )  { return a < 0 ? -a : a; }

inline int    sign( int a )    { return a < 0 ? -1 : 1; }
inline long   sign( long a )   { return a < 0 ? -1 : 1; }
inline float  sign( float a )  { return a < 0 ? -1 : 1; }
inline double sign( double a ) { return a < 0 ? -1 : 1; }

inline int    sqr(  int a )    { return a * a; }
inline long   sqr(  long a )   { return a * a; }
inline float  sqr(  float a )  { return a * a; }
inline double sqr(  double a ) { return a * a; }

inline int    cub(  int a )    { return a * a * a; }
inline long   cub(  long a )   { return a * a * a; }
inline float  cub(  float a )  { return a * a * a; }
inline double cub(  double a ) { return a * a * a; }

inline float  cbrt( float a )  { return pow( a, 1.0f/3.0f ); }
inline double cbrt( double a ) { return pow( a, 1.0/3.0 ); }

inline float  root( float a, float n )   { return pow( a, 1.0f/n ); }
inline double root( double a, double n ) { return pow( a, 1.0/n ); }


inline int    avg( int a, int b )        { return ( a + b ) / 2; }
inline long   avg( long a, long b )      { return ( a + b ) / 2; }
inline float  avg( float a, float b )    { return ( a + b ) / 2; }
inline double avg( double a, double b )  { return ( a + b ) / 2; }

inline int    min( int a, int b )        { return a < b ? a : b; }
inline long   min( long a, long b )      { return a < b ? a : b; }
inline float  min( float a, float b )    { return a < b ? a : b; }
inline double min( double a, double b )  { return a < b ? a : b; }

inline int    max( int a, int b )        { return a > b ? a : b; }
inline long   max( long a, long b )      { return a > b ? a : b; }
inline float  max( float a, float b )    { return a > b ? a : b; }
inline double max( double a, double b )  { return a > b ? a : b; }

inline int    span( int a, int b )       { return abs( a - b ); }
inline long   span( long a, long b )     { return abs( a - b ); }
inline float  span( float a, float b )   { return abs( a - b ); }
inline double span( double a, double b ) { return abs( a - b ); }


inline int    avg3( int a, int b, int c )          { return ( a + b + c ) / 3; }
inline long   avg3( long a, long b, long c )       { return ( a + b + c ) / 3; }
inline float  avg3( float a, float b, float c )    { return ( a + b + c ) / 3; }
inline double avg3( double a, double b, double c ) { return ( a + b + c ) / 3; }

inline int    min3( int a, int b, int c )          { return min( min( a, b ), c ); }
inline long   min3( long a, long b, long c )       { return min( min( a, b ), c ); }
inline float  min3( float a, float b, float c )    { return min( min( a, b ), c ); }
inline double min3( double a, double b, double c ) { return min( min( a, b ), c ); }

inline int    max3( int a, int b, int c )          { return max( max( a, b ), c ); }
inline long   max3( long a, long b, long c )       { return max( max( a, b ), c ); }
inline float  max3( float a, float b, float c )    { return max( max( a, b ), c ); }
inline double max3( double a, double b, double c ) { return max( max( a, b ), c ); }

inline int    clamp( int mn, int a, int mx )          { return min( max( mn, a ), mx ); }
inline long   clamp( long mn, long a, long mx )       { return min( max( mn, a ), mx ); }
inline float  clamp( float mn, float a, float mx )    { return min( max( mn, a ), mx ); }
inline double clamp( double mn, double a, double mx ) { return min( max( mn, a ), mx ); }


inline float  deg2rad( float d )  { return d * PI / 180; }
inline double deg2rad( double d ) { return d * PI / 180; }

inline float  rad2deg( float r )  { return r * 180 / PI; }
inline double rad2deg( double r ) { return r * 180 / PI; }


inline float  lerp( float a, float b, float t )    { return a + ( t * ( b - a )); }
inline double lerp( double a, double b, double t ) { return a + ( t * ( b - a )); }

inline float  norm( float x, float a, float b, float c, float d )      { return lerp( c, d, ( x - a ) / ( b - a )); }
inline double norm( double x, double a, double b, double c, double d ) { return lerp( c, d, ( x - a ) / ( b - a )); }

inline float  normFrom01( float x, float a, float b )    { return norm( x,  0, 1, a, b ); }
inline double normFrom01( double x, double a, double b ) { return norm( x,  0, 1, a, b ); }

inline float  normFrom11( float x, float a, float b )    { return norm( x, -1, 1, a, b ); }
inline double normFrom11( double x, double a, double b ) { return norm( x, -1, 1, a, b ); }

inline float  normTo01(  float x, float a, float b )     { return norm( x, a, b,  0, 1 ); }
inline double normTo01( double x, double a, double b )   { return norm( x, a, b,  0, 1 ); }

inline float  normTo11( float x, float a, float b )      { return norm( x, a, b, -1, 1 ); }
inline double normTo11( double x, double a, double b )   { return norm( x, a, b, -1, 1 ); }


// float  operator%( float a, float b )   { return fmod( a, b ); }
// double operator%( double a, double b ) { return fmod( a, b ); }

// float  &operator%=( float &a, float b )   { a = fmod( a, b ); return a; }
// double &operator%=( double &a, double b ) { a = fmod( a, b ); return a; }

#endif // MATH_HPP