#include "../../../incs/base.hpp"

pos2_s getNullPos2() { return { 0, 0 }; }

pos2_s getPos2( byte_t x, byte_t y ) { return { ( posint_t )x, ( posint_t )y }; }
pos2_s getPos2( word_t x, word_t y ) { return { ( posint_t )x, ( posint_t )y }; }
pos2_s getPos2( int x, int y )       { return { ( posint_t )x, ( posint_t )y }; }
pos2_s getPos2( long x, long y )     { return { ( posint_t )x, ( posint_t )y }; }
pos2_s getPos2( float x, float y )   { return { ( posint_t )x, ( posint_t )y }; }
pos2_s getPos2( double x, double y ) { return { ( posint_t )x, ( posint_t )y }; }

pos2_s getPos2( byte_t v ) { return { ( posint_t )v, ( posint_t )v }; }
pos2_s getPos2( word_t v ) { return { ( posint_t )v, ( posint_t )v }; }
pos2_s getPos2( int v )    { return { ( posint_t )v, ( posint_t )v }; }
pos2_s getPos2( long v )   { return { ( posint_t )v, ( posint_t )v }; }
pos2_s getPos2( float v )  { return { ( posint_t )v, ( posint_t )v }; }
pos2_s getPos2( double v ) { return { ( posint_t )v, ( posint_t )v }; }

// ================================ DISTANCE METHODS

float getXDist( const pos2_s &p1, const pos2_s &p2 ) { return abs( p1.x - p2.x ); }
float getYDist( const pos2_s &p1, const pos2_s &p2 ) { return abs( p1.y - p2.y ); }

float getShortLinearDist( const pos2_s &p1, const pos2_s &p2 ) { return min( abs( p1.x - p2.x ), abs( p1.y - p2.y )); }
float getLongLinearDist( const pos2_s &p1, const pos2_s &p2 ) { return max( abs( p1.x - p2.x ), abs( p1.y - p2.y )); }

float getCartesianDist( const pos2_s &p1, const pos2_s &p2 ) { return abs( p1.x - p2.x ) + abs( p1.y - p2.y ); }
float getCircularDist( const pos2_s &p1, const pos2_s &p2 )
{
	posint_t x = abs( p2.x - p1.x );
	posint_t y = abs( p2.y - p1.y );

	posint_t dsquare = sqr( y ) + sqr( x );

	return sqrt( dsquare );
}

// ================================ LIST METHODS

posList2_t listPosInRect( pos2_s const &p1, pos2_s const &p2 )
{
	posList2_t list;
	pos2_s pos;

	for ( pos.x = min( p1.x, p2.x ); pos.x <= max( p1.x, p2.x ); pos.x++ )
	{
		for ( pos.y = min( p1.y, p2.y ); pos.y <= max( p1.y, p2.y ); pos.y++ )
		{
			list.push_back( pos );
		}
	}
	return list;
}

posList2_t listPosInSquare( pos2_s const &center, float radius )
{
	posList2_t list;
	pos2_s pos;

	for ( pos.x = center.x - radius; pos.x <= center.x + radius; pos.x++ )
	{
		for ( pos.y = center.y - radius; pos.y <= center.y + radius; pos.y++ )
		{
			list.push_back( pos );
		}
	}
	return list;
}

posList2_t listPosInCircle( pos2_s const &center, float radius )
{
	posList2_t list;
	pos2_s pos;

	for ( pos.x = center.x - radius; pos.x <= center.x + radius; pos.x++ )
	{
		for ( pos.y = center.y - radius; pos.y <= center.y + radius; pos.y++ )
		{
			if ( isInCircle( pos, center, radius ))
				list.push_back( pos );
		}
	}
	return list;
}


// ================================ BOOLEAN METHODS

bool hasSameX( const pos2_s &p1, const pos2_s &p2 ) { return p1.x == p2.x; }
bool hasSameY( const pos2_s &p1, const pos2_s &p2 ) { return p1.y == p2.y; }
bool hasSameXY( const pos2_s &p1, const pos2_s &p2 ) { return p1.x == p2.x && p1.y == p2.y; }

// ================ RECTANGULAR VOLUMES

// Like isInRect but with 0,0,0 as the first point
bool isWithin( const pos2_s &point, const pos2_s &dists )
{
	if ( point.x >= 0 && point.x < dists.x && point.y >= 0 && point.y < dists.y )
		return true;
	return false;
}

bool isInRect( pos2_s const &point, pos2_s const &p1, pos2_s const &p2 )
{
	if ( point.x >= min( p1.x, p2.x ) && point.x <= max( p1.x, p2.x ) &&
		 point.y >= min( p1.y, p2.y ) && point.y <= max( p1.y, p2.y ))
		return true;
	return false;
}

bool isInSquare( pos2_s const &point, pos2_s const &center, float radius )
{
	if ( isInRect( point, center - getPos2( radius, radius ), center + getPos2( radius, radius )))
		return true;
	return false;
}

// ================ SPHERICAL VOLUMES

bool isInCircle( pos2_s const &point, pos2_s const &center, float radius )
{
	if ( isInRect( point, center - getPos2( radius, radius ), center + getPos2( radius, radius )))
		if ( getCircularDist( point, center ) <= radius )
			return true;
	return false;
}

bool isInEllipse( pos2_s const &point, pos2_s const &center, float radX, float radY )
{
	if ( isInRect( point, center - getPos2( radX, radY ), center + getPos2( radX, radY)))
	{
		float x = ( float )sqr( point.x - center.x ) / sqr( radX );
		float y = ( float )sqr( point.y - center.y ) / sqr( radY );

		if ( x + y<= 1 )
			return true;
	}
	return false;
}

bool isInTriangle( pos2_s const &point, pos2_s const &p1, pos2_s const &p2, pos2_s const &p3 )
{
	// COPILOTE : untested copilote added feature. wtf
	float A = 0.5f * ( -p2.y * p3.x + p1.y * ( p3.x - p2.x ) + p1.x * ( p2.y - p3.y ) + p2.x * p3.y );
	float sign = A < 0 ? -1 : 1;

	float s = ( p1.y * p3.x - p1.x * p3.y + ( p3.y - p1.y ) * point.x + ( p1.x - p3.x ) * point.y ) * sign;
	float t = ( p1.x * p2.y - p1.y * p2.x + ( p1.y - p2.y ) * point.x + ( p2.x - p1.x ) * point.y ) * sign;

	return ( s > 0 && t > 0 && ( s + t ) < 2 * A * sign );
}

// ================================ COMPARISON OPERATORS

bool operator==( const pos2_s &lhs, const pos2_s &rhs ) { return lhs.x == rhs.x && lhs.y == rhs.y; }
bool operator!=( const pos2_s &lhs, const pos2_s &rhs ) { return lhs.x != rhs.x || lhs.y != rhs.y; }
bool operator>( const pos2_s &lhs, const pos2_s &rhs )  { return lhs.x + lhs.y> rhs.x + rhs.y; }
bool operator<( const pos2_s &lhs, const pos2_s &rhs )  { return lhs.x + lhs.y < rhs.x + rhs.y ; }

// ================================ ARITHMETIC OPERATORS

pos2_s operator+( const pos2_s &lhs, const pos2_s &rhs )
{
	pos2_s pos = getPos2( lhs.x + rhs.x, lhs.y + rhs.y );
	return pos;
}

pos2_s operator-( const pos2_s &lhs, const pos2_s &rhs )
{
	pos2_s pos = getPos2( lhs.x - rhs.x, lhs.y - rhs.y );
	return pos;
}

pos2_s operator*( int  lhs, const pos2_s &rhs ) { return rhs * lhs; }
pos2_s operator*( const pos2_s &lhs, int rhs )
{
	pos2_s pos = getPos2( lhs.x * rhs, lhs.y * rhs );
	return pos;
}

pos2_s operator/( const pos2_s &lhs, int rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	pos2_s pos = getPos2( lhs.x / rhs, lhs.y / rhs );
	return pos;
}

pos2_s operator%( const pos2_s &lhs, int rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	pos2_s pos = getPos2( lhs.x % rhs, lhs.y % rhs );
	return pos;
}

// ================ FLOAT OPERATORS

pos2_s operator*( float lhs, const pos2_s &rhs) { return rhs * lhs; }
pos2_s operator*( const pos2_s &lhs, float rhs )
{
	pos2_s pos = { int( lhs.x * rhs ), int( lhs.y * rhs )};
	return pos;
}

pos2_s operator/( const pos2_s &lhs, float rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	pos2_s pos = getPos2( lhs.x / rhs, lhs.y / rhs );
	return pos;
}

// ================ DOUBLE OPERATORS

pos2_s operator*( double lhs, const pos2_s &rhs ) { return rhs * lhs; }
pos2_s operator*( const pos2_s &lhs, double rhs )
{
	pos2_s pos = { int( lhs.x * rhs ), int( lhs.y * rhs )};
	return pos;
}

pos2_s operator/( const pos2_s &lhs, double rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	pos2_s pos = getPos2( lhs.x / rhs, lhs.y / rhs );
	return pos;
}

// ================================ ASSIGNMENT OPERATORS

pos2_s &operator+=( pos2_s &lhs, const pos2_s &rhs )
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

pos2_s &operator-=( pos2_s &lhs, const pos2_s &rhs )
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

pos2_s &operator*=( pos2_s &lhs, int rhs )
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	return lhs;
}

pos2_s &operator/=( pos2_s &lhs, int rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x /= rhs;
	lhs.y /= rhs;
	return lhs;
}

pos2_s &operator%=( pos2_s &lhs, int rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x %= rhs;
	lhs.y %= rhs;
	return lhs;
}

// ================ FLOAT

pos2_s &operator*=( pos2_s &lhs, float rhs )
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	return lhs;
}

pos2_s &operator/=( pos2_s &lhs, float rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x = ( posint_t )fmod( lhs.x, rhs );
	lhs.y = ( posint_t )fmod( lhs.y, rhs );
	return lhs;
}

pos2_s &operator%=( pos2_s &lhs, float rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x = ( posint_t )fmod( lhs.x, rhs );
	lhs.y = ( posint_t )fmod( lhs.y, rhs );
	return lhs;
}

// ================ DOUBLE

pos2_s &operator*=( pos2_s &lhs, double rhs )
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	return lhs;
}

pos2_s &operator/=( pos2_s &lhs, double rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x = ( posint_t )fmod( lhs.x, rhs );
	lhs.y = ( posint_t )fmod( lhs.y, rhs );
	return lhs;
}

pos2_s &operator%=( pos2_s &lhs, double rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x = ( posint_t )fmod( lhs.x, rhs );
	lhs.y = ( posint_t )fmod( lhs.y, rhs );
	return lhs;
}