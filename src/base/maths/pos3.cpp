#include "../../../inc/struct/pos3.hpp"
#include "../../../inc/deps.hpp"

pos3_s getNullPos3() { return { 0, 0, 0 }; }

pos3_s getPos3( byte_t x, byte_t y, byte_t z ) { return { x, y, z }; }
pos3_s getPos3( word_t x, word_t y, word_t z ) { return { x, y, z }; }
pos3_s getPos3( int x, int y, int z )          { return { x, y, z }; }
pos3_s getPos3( long x, long y, long z )       { return { ( int )x, ( int )y, ( int )z }; }
pos3_s getPos3( float x, float y, float z )    { return { ( int )x, ( int )y, ( int )z }; }
pos3_s getPos3( double x, double y, double z ) { return { ( int )x, ( int )y, ( int )z }; }

pos3_s getPos3( byte_t v ) { return { v, v, v }; }
pos3_s getPos3( word_t v ) { return { v, v, v }; }
pos3_s getPos3( int v )    { return { v, v, v }; }
pos3_s getPos3( long v )   { return { ( int )v, ( int )v, ( int )v }; }
pos3_s getPos3( float v )  { return { ( int )v, ( int )v, ( int )v }; }
pos3_s getPos3( double v ) { return { ( int )v, ( int )v, ( int )v }; }

pos3_s getRelPosFromSide( side_e side ) { return getRelPosFromDir( ( dir_e )side ); }
pos3_s getRelPosFromDir( dir_e dir )
{
	pos3_s pos = getNullPos3();

	switch ( dir )
	{
		case NOD:
			break;
		case XPD:
			pos.x = 1;
			break;
		case XND:
			pos.x = -1;
			break;
		case ZPD:
			pos.z = 1;
			break;
		case ZND:
			pos.z = -1;
			break;
		case YPD:
			pos.y = 1;
			break;
		case YND:
			pos.y = -1;
			break;

		default:
			log( "Invalid direction", ERROR );
			throw std::invalid_argument( "Invalid direction" );
			break;
	}
	return pos;
}

pos3_s getRelPosFromVertex( vertex_e vertex )
{
	pos3_s pos = getNullPos3();

	// Ugly af but does the job
	switch ( vertex )
	{
		case MMM:
			break;

		case NMM:
			pos.y = 1;
			break;
		case SMM:
			pos.y = -1;
			break;
		case MEM:
			pos.x = 1;
			break;
		case MWM:
			pos.x = -1;
			break;
		case MMT:
			pos.z = 1;
			break;
		case MMB:
			pos.z = -1;
			break;

		case NEM:
			pos.x = 1;
			pos.y = 1;
			break;
		case NWM:
			pos.x = -1;
			pos.y = 1;
			break;
		case NMT:
			pos.z = 1;
			pos.y = 1;
			break;
		case NMB:
			pos.z = -1;
			pos.y = 1;
			break;
		case SEM:
			pos.x = 1;
			pos.y = -1;
			break;
		case SWM:
			pos.x = -1;
			pos.y = -1;
			break;
		case SMT:
			pos.z = 1;
			pos.y = -1;
			break;
		case SMB:
			pos.z = -1;
			pos.y = -1;
			break;
		case MET:
			pos.x = 1;
			pos.z = 1;
			break;
		case MEB:
			pos.x = 1;
			pos.z = -1;
			break;
		case MWT:
			pos.x = -1;
			pos.z = 1;
			break;
		case MWB:
			pos.x = -1;
			pos.z = -1;
			break;

		case NET:
			pos.x = 1;
			pos.y = 1;
			pos.z = 1;
			break;
		case NEB:
			pos.x = 1;
			pos.y = 1;
			pos.z = -1;
			break;
		case NWT:
			pos.x = -1;
			pos.y = 1;
			pos.z = 1;
			break;
		case NWB:
			pos.x = -1;
			pos.y = 1;
			pos.z = -1;
			break;
		case SET:
			pos.x = 1;
			pos.y = -1;
			pos.z = 1;
			break;
		case SEB:
			pos.x = 1;
			pos.y = -1;
			pos.z = -1;
			break;
		case SWT:
			pos.x = -1;
			pos.y = -1;
			pos.z = 1;
			break;
		case SWB:
			pos.x = -1;
			pos.y = -1;
			pos.z = -1;
			break;

		default:
			log( "Invalid vertex", ERROR );
			throw std::invalid_argument( "Invalid vertex" );
			break;
	}
	return pos;
}

pos3_s getNeighbour( pos3_s const &pos, dir_e dir )
{
	pos3_s relPos = getRelPosFromDir( dir );
	return pos + relPos;
}

// ================================ DISTANCE METHODS

float getXDist( const pos3_s &p1, const pos3_s &p2 ) { return abs( p1.x - p2.x ); }
float getZDist( const pos3_s &p1, const pos3_s &p2 ) { return abs( p1.z - p2.z ); }
float getYDist( const pos3_s &p1, const pos3_s &p2 ) { return abs( p1.y - p2.y ); }

float getShortLinearDist( const pos3_s &p1, const pos3_s &p2 ) { return min3( abs( p1.x - p2.x ), abs( p1.y - p2.y ), abs( p1.z - p2.z )); }
float getLongLinearDist( const pos3_s &p1, const pos3_s &p2 ) { return max3( abs( p1.x - p2.x ), abs( p1.y - p2.y ), abs( p1.z - p2.z )); }

float getCartesianDist( const pos3_s &p1, const pos3_s &p2 ) { return abs( p1.x - p2.x ) + abs( p1.y - p2.y ) + abs( p1.z - p2.z ); }
float getSphericalDist( const pos3_s &p1, const pos3_s &p2 )
{
	int x = abs( p2.x - p1.x );
	int y = abs( p2.y - p1.y );
	int z = abs( p2.z - p1.z );

	int dsquare = sqr( y ) + sqr( x ) + sqr( z );

	return sqrt( dsquare );
}

float getCylindricalDist( const pos3_s &p1, const pos3_s &p2 )
{
	int x = abs( p2.x - p1.x );
	int z = abs( p2.z - p1.z );

	int dsquare = sqr( x ) + sqr( z );

	return sqrt( dsquare );
}

// Rotated versions of the above function, for when the cylinder is aligned with the X or Z axis instead of the Y axis ( upright )
float getCylindricalDistX( const pos3_s &p1, const pos3_s &p2 ) { return getCylindricalDist( getPos3( p1.y, p2.x, p1.z ), getPos3( p2.y, p2.x, p2.z )); }
float getCylindricalDistZ( const pos3_s &p1, const pos3_s &p2 ) { return getCylindricalDist( getPos3( p1.y, p1.x, p2.z ), getPos3( p2.y, p2.x, p2.z )); }


// ================================ LIST METHODS

posList3_t listPosInRect( pos3_s const &p1, pos3_s const &p2 )
{
	posList3_t list;
	pos3_s pos;

	for ( pos.x = min( p1.x, p2.x ); pos.x <= max( p1.x, p2.x ); pos.x++ )
	{
		for ( pos.z = min( p1.z, p2.z ); pos.z <= max( p1.z, p2.z ); pos.z++ )
		{
			for ( pos.y = min( p1.y, p2.y ); pos.y <= max( p1.y, p2.y ); pos.y++ )
			{
				list.push_back( pos );
			}
		}
	}
	return list;
}

posList3_t listPosInCube( pos3_s const &center, float radius )
{
	posList3_t list;
	pos3_s pos;

	for ( pos.x = center.x - radius; pos.x <= center.x + radius; pos.x++ )
	{
		for ( pos.z = center.z - radius; pos.z <= center.z + radius; pos.z++ )
		{
			for ( pos.y = center.y - radius; pos.y <= center.y + radius; pos.y++ )
			{
				list.push_back( pos );
			}
		}
	}
	return list;
}

posList3_t listPosInSphere( pos3_s const &center, float radius )
{
	posList3_t list;
	pos3_s pos;

	for ( pos.x = center.x - radius; pos.x <= center.x + radius; pos.x++ )
	{
		for ( pos.z = center.z - radius; pos.z <= center.z + radius; pos.z++ )
		{
			for ( pos.y = center.y - radius; pos.y <= center.y + radius; pos.y++ )
			{
				if ( isInSphere( pos, center, radius ))
					list.push_back( pos );
			}
		}
	}
	return list;
}


// ================================ BOOLEAN METHODS

bool hasSameX( const pos3_s &p1, const pos3_s &p2 ) { return p1.x == p2.x; }
bool hasSameZ( const pos3_s &p1, const pos3_s &p2 ) { return p1.z == p2.z; }
bool hasSameY( const pos3_s &p1, const pos3_s &p2 ) { return p1.y == p2.y; }

bool hasSameXZ( const pos3_s &p1, const pos3_s &p2 ) { return p1.x == p2.x && p1.z == p2.z; }
bool hasSameYZ( const pos3_s &p1, const pos3_s &p2 ) { return p1.y == p2.y && p1.z == p2.z; }
bool hasSameXY( const pos3_s &p1, const pos3_s &p2 ) { return p1.x == p2.x && p1.y == p2.y; }

// ================ RECTANGULAR VOLUMES

// Like isInRect but with 0,0,0 as the first point
bool isWithin( const pos3_s &point, const pos3_s &dists )
{
	if ( point.x >= 0 && point.x < dists.x &&
		 point.y >= 0 && point.y < dists.y &&
		 point.z >= 0 && point.z < dists.z )
		return true;
	return false;
}

bool isInRect( pos3_s const &point, pos3_s const &p1, pos3_s const &p2 )
{
	if ( point.x >= min( p1.x, p2.x ) && point.x <= max( p1.x, p2.x ) &&
		 point.y >= min( p1.y, p2.y ) && point.y <= max( p1.y, p2.y ) &&
		 point.z >= min( p1.z, p2.z ) && point.z <= max( p1.z, p2.z ))
		return true;
	return false;
}

bool isInCube( pos3_s const &point, pos3_s const &center, float radius )
{
	if ( isInRect( point, center - getPos3( radius, radius, radius ), center + getPos3( radius, radius, radius )))
		return true;
	return false;
}

bool isInPrism( pos3_s const &point, pos3_s const &center, float radX, float radY, float radZ )
{
	if ( isInRect( point, center - getPos3( radX, radY, radZ ), center + getPos3( radX, radY, radZ )))
		return true;
	return false;
}

// ================ SPHERICAL VOLUMES

bool isInSphere( pos3_s const &point, pos3_s const &center, float radius )
{
	if ( isInRect( point, center - getPos3( radius, radius, radius ), center + getPos3( radius, radius, radius )))
		if ( getSphericalDist( point, center ) <= radius )
			return true;
	return false;
}

bool isInSpheroid( pos3_s const &point, pos3_s const &center, float radX, float radY, float radZ )
{
	if ( isInRect( point, center - getPos3( radX, radY, radZ ), center + getPos3( radX, radY, radZ )))
	{
		float x = ( float )sqr( point.x - center.x ) / sqr( radX );
		float y = ( float )sqr( point.y - center.y ) / sqr( radY );
		float z = ( float )sqr( point.z - center.z ) / sqr( radZ );

		if ( x + y + z <= 1 )
			return true;
	}
	return false;
}

// ================ CYLINDRICAL VOLUMES

bool isInCylinder( pos3_s const &point, pos3_s const &center, float radius, float halfHeight )
{
	if ( isInRect( point, center - getPos3( radius, halfHeight, radius ), center + getPos3( radius, halfHeight, radius )))
	{
		float x = ( float )sqr( point.x - center.x ) / sqr( radius );
		float z = ( float )sqr( point.z - center.z ) / sqr( radius );

		if ( x + z <= 1 )
			return true;
	}
	return false;
}

bool isInCone(    pos3_s const &point, pos3_s const &center, float radius, float halfHeight ) { return isInConoid( point, center, radius, 0, halfHeight ); }
bool isInInvCone( pos3_s const &point, pos3_s const &center, float radius, float halfHeight ) { return isInConoid( point, center, 0, radius, halfHeight ); }

// Checks if a point is inside a conoid, aka a truncated cone section
bool isInConoid( pos3_s const &point, pos3_s const &center, float radBot, float radTop, float halfHeight )
{
	float maxRad = max( radBot, radTop );
	if ( isInRect( point, center - getPos3( maxRad, halfHeight, maxRad ), center + getPos3( maxRad, halfHeight, maxRad )))
	{
		if ( point.y < center.y - halfHeight || point.y > center.y + halfHeight )
			return false;

		float r = normFrom11(( float )( point.y - center.y ) / halfHeight, radBot, radTop );

		float x = ( float )sqr( point.x - center.x ) / sqr( r );
		float z = ( float )sqr( point.z - center.z ) / sqr( r );

		if ( x + z <= 1 )
			return true;

	}
	return false;
}

// Rotated versions of the above functions, for when the conoid is aligned with the X or Z axis instead of the Y axis ( upright )
bool isInXCylinder( pos3_s const &point, pos3_s const &center, float radius, float halfHeight ) { return isInCylinder( getPos3( point.y, point.x, point.z ), center, radius, halfHeight ); }
bool isInZCylinder( pos3_s const &point, pos3_s const &center, float radius, float halfHeight ) { return isInCylinder( getPos3( point.x, point.z, point.y ), center, radius, halfHeight ); }

bool isInXCone(		  pos3_s const &point, pos3_s const &center, float radius, float halfHeight ) { return isInCone(     getPos3( point.y, point.x, point.z ), center, radius, halfHeight ); }
bool isInZCone(		  pos3_s const &point, pos3_s const &center, float radius, float halfHeight ) { return isInCone(     getPos3( point.x, point.z, point.y ), center, radius, halfHeight ); }

bool isInXInvCone(	pos3_s const &point, pos3_s const &center, float radius, float halfHeight ) { return isInInvCone(  getPos3( point.y, point.x, point.z ), center, radius, halfHeight ); }
bool isInZInvCone(	pos3_s const &point, pos3_s const &center, float radius, float halfHeight ) { return isInInvCone(  getPos3( point.x, point.z, point.y ), center, radius, halfHeight ); }

bool isInXConoid( pos3_s const &point, pos3_s const &center, float radSouth, float radNorth, float halfHeight ) { return isInConoid( getPos3( point.y, point.x, point.z ), center, radSouth, radNorth, halfHeight ); }
bool isInZConoid( pos3_s const &point, pos3_s const &center, float radEast,  float radWest,  float halfHeight ) { return isInConoid( getPos3( point.x, point.z, point.y ), center, radEast,  radWest,  halfHeight ); }

// ================================ COMPARISON OPERATORS

bool operator==( const pos3_s &lhs, const pos3_s &rhs ) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
bool operator!=( const pos3_s &lhs, const pos3_s &rhs ) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z; }
bool operator>( const pos3_s &lhs, const pos3_s &rhs )  { return lhs.x + lhs.y + lhs.z > rhs.x + rhs.y + rhs.z; }
bool operator<( const pos3_s &lhs, const pos3_s &rhs )  { return lhs.x + lhs.y + lhs.z < rhs.x + rhs.y + rhs.z; }

// ================================ ARITHMETIC OPERATORS

pos3_s operator+( const pos3_s &lhs, const pos3_s &rhs )
{
	pos3_s pos = getPos3( lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z );
	return pos;
}

pos3_s operator-( const pos3_s &lhs, const pos3_s &rhs )
{
	pos3_s pos = getPos3( lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z );
	return pos;
}

pos3_s operator*( int  lhs, const pos3_s &rhs ) { return rhs * lhs; }
pos3_s operator*( const pos3_s &lhs, int rhs )
{
	pos3_s pos = getPos3( lhs.x * rhs, lhs.y * rhs, lhs.z * rhs );
	return pos;
}

pos3_s operator/( const pos3_s &lhs, int rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	pos3_s pos = getPos3( lhs.x / rhs, lhs.y / rhs, lhs.z / rhs );
	return pos;
}

pos3_s operator%( const pos3_s &lhs, int rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	pos3_s pos = getPos3( lhs.x % rhs, lhs.y % rhs, lhs.z % rhs );
	return pos;
}

// ================ FLOAT OPERATORS

pos3_s operator*( float lhs, const pos3_s &rhs) { return rhs * lhs; }
pos3_s operator*( const pos3_s &lhs, float rhs )
{
	pos3_s pos = { int( lhs.x * rhs ), int( lhs.y * rhs ), int( lhs.z * rhs )};
	return pos;
}

pos3_s operator/( const pos3_s &lhs, float rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	pos3_s pos = getPos3( lhs.x / rhs, lhs.y / rhs, lhs.z / rhs );
	return pos;
}

// ================ DOUBLE OPERATORS

pos3_s operator*( double lhs, const pos3_s &rhs ) { return rhs * lhs; }
pos3_s operator*( const pos3_s &lhs, double rhs )
{
	pos3_s pos = { int( lhs.x * rhs ), int( lhs.y * rhs ), int( lhs.z * rhs )};
	return pos;
}

pos3_s operator/( const pos3_s &lhs, double rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	pos3_s pos = getPos3( lhs.x / rhs, lhs.y / rhs, lhs.z / rhs );
	return pos;
}

// ================================ ASSIGNMENT OPERATORS

pos3_s &operator+=( pos3_s &lhs, const pos3_s &rhs )
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

pos3_s &operator-=( pos3_s &lhs, const pos3_s &rhs )
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

pos3_s &operator*=( pos3_s &lhs, int rhs )
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return lhs;
}

pos3_s &operator/=( pos3_s &lhs, int rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;
	return lhs;
}

pos3_s &operator%=( pos3_s &lhs, int rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x %= rhs;
	lhs.y %= rhs;
	lhs.z %= rhs;
	return lhs;
}

// ================ FLOAT

pos3_s &operator*=( pos3_s &lhs, float rhs )
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return lhs;
}

pos3_s &operator/=( pos3_s &lhs, float rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x = ( int )fmod( lhs.x, rhs );
	lhs.y = ( int )fmod( lhs.y, rhs );
	lhs.z = ( int )fmod( lhs.z, rhs );
	return lhs;
}

pos3_s &operator%=( pos3_s &lhs, float rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x = ( int )fmod( lhs.x, rhs );
	lhs.y = ( int )fmod( lhs.y, rhs );
	lhs.z = ( int )fmod( lhs.z, rhs );
	return lhs;
}

// ================ DOUBLE

pos3_s &operator*=( pos3_s &lhs, double rhs )
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return lhs;
}

pos3_s &operator/=( pos3_s &lhs, double rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x = ( int )fmod( lhs.x, rhs );
	lhs.y = ( int )fmod( lhs.y, rhs );
	lhs.z = ( int )fmod( lhs.z, rhs );
	return lhs;
}

pos3_s &operator%=( pos3_s &lhs, double rhs )
{
	if ( divtest( rhs )) { throw std::invalid_argument( "Invalid division" ); }
	lhs.x = ( int )fmod( lhs.x, rhs );
	lhs.y = ( int )fmod( lhs.y, rhs );
	lhs.z = ( int )fmod( lhs.z, rhs );
	return lhs;
}