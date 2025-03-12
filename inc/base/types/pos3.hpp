#ifndef POS3_HPP
# define POS3_HPP

# include "../defs.hpp"

typedef struct
{
	int x;
	int y;
	int z;
} pos3_s;

typedef list<   pos3_s > posList3_t ;
typedef vector< pos3_s > posVect3_t ;

pos3_s getNullPos3();

pos3_s getPos3( byte_t x, byte_t y, byte_t z );
pos3_s getPos3( word_t x, word_t y, word_t z );
pos3_s getPos3( int x, int y, int z );
pos3_s getPos3( long x, long y, long z );
pos3_s getPos3( float x, float y, float z );
pos3_s getPos3( double x, double y, double z );

pos3_s getPos3( byte_t v );
pos3_s getPos3( word_t v );
pos3_s getPos3( int v );
pos3_s getPos3( long v );
pos3_s getPos3( float v );
pos3_s getPos3( double v );

// ================================ DISTANCE METHODS

float getXDist( const pos3_s &p1, const pos3_s &p2 );
float getZDist( const pos3_s &p1, const pos3_s &p2 );
float getYDist( const pos3_s &p1, const pos3_s &p2 );

float getShortLinearDist( const pos3_s &p1, const pos3_s &p2 );
float getLongLinearDist(  const pos3_s &p1, const pos3_s &p2 );

float getCartesianDist(   const pos3_s &p1, const pos3_s &p2 );
float getSphericalDist(   const pos3_s &p1, const pos3_s &p2 );
float getCylindricalDist( const pos3_s &p1, const pos3_s &p2 );

// Rotated versions of the above function, for when the cylinder is aligned with the X or Z axis instead of the Y axis ( upright )
float getCylindricalDistX( const pos3_s &p1, const pos3_s &p2 );
float getCylindricalDistZ( const pos3_s &p1, const pos3_s &p2 );

// ================================ BOOLEAN METHODS

bool hasSameX( const pos3_s &p1, const pos3_s &p2 );
bool hasSameZ( const pos3_s &p1, const pos3_s &p2 );
bool hasSameY( const pos3_s &p1, const pos3_s &p2 );

bool hasSameXZ( const pos3_s &p1, const pos3_s &p2 );
bool hasSameYZ( const pos3_s &p1, const pos3_s &p2 );
bool hasSameXY( const pos3_s &p1, const pos3_s &p2 );

// ================ RECTANGULAR VOLUMES

bool isWithin(  const pos3_s &point, const pos3_s &dists ); // sets the first point to 0,0,0
bool isInRect(  pos3_s const &point, pos3_s const &p1, pos3_s const &p2 );
bool isInCube(  pos3_s const &point, pos3_s const &center, float radius );
bool isInPrism( pos3_s const &point, pos3_s const &center, float radX, float radY, float radZ );

// bool isInTethraedron( pos3_s const &point, pos3_s const &p1, pos3_s const &p2, pos3_s const &p3, pos3_s const &p4 );

// ================ SPHERICAL VOLUMES

bool isInSphere(   pos3_s const &point, pos3_s const &center, float radius );
bool isInSpheroid( pos3_s const &point, pos3_s const &center, float radX, float radY, float radZ );

// ================ CYLINDRICAL VOLUMES

bool isInCylinder( pos3_s const &point, pos3_s const &center, float radius, float halfHeight );
bool isInCone(     pos3_s const &point, pos3_s const &center, float radius, float halfHeight );
bool isInInvCone(  pos3_s const &point, pos3_s const &center, float radius, float halfHeight );
bool isInConoid(   pos3_s const &point, pos3_s const &center, float radBot, float radTop, float halfHeight );

// Rotated versions of the above functions, for when the conoid is aligned with the X or Z axis instead of the Y axis ( upright )
bool isInXCylinder( pos3_s const &point, pos3_s const &center, float radius, float halfHeight );
bool isInZCylinder( pos3_s const &point, pos3_s const &center, float radius, float halfHeight );

bool isInXCone(     pos3_s const &point, pos3_s const &center, float radius, float halfHeight );
bool isInZCone(     pos3_s const &point, pos3_s const &center, float radius, float halfHeight );

bool isInXInvCone(  pos3_s const &point, pos3_s const &center, float radius, float halfHeight );
bool isInZInvCone(  pos3_s const &point, pos3_s const &center, float radius, float halfHeight );

bool isInXConoid(   pos3_s const &point, pos3_s const &center, float radSouth, float radNorth, float halfHeight );
bool isInZConoid(   pos3_s const &point, pos3_s const &center, float radEast, float radWest, float halfHeight );

// Rotated versions of the above functions, for when the conoid is arbitrary rotated ( p1-->p2 vector )
// TODO : implement these ( requires a lot of math Xd )
//bool isInCylinder( pos3_s const &point, pos3_s const &p1, pos3_s const &p2, float radius );
//bool isInCone(     pos3_s const &point, pos3_s const &p1, pos3_s const &p2, float r1 );
//bool isInInvCone(  pos3_s const &point, pos3_s const &p1, pos3_s const &p2, float r2 );
//bool isInConoid(   pos3_s const &point, pos3_s const &p1, pos3_s const &p2, float r1, float r2 );


// ================================ LIST METHODS

posList3_t listPosInRect( pos3_s const &p1, pos3_s const &p2 );
posList3_t listPosInCube( pos3_s const &center, float radius );
posList3_t listPosInSphere( pos3_s const &center, float radius );


// ================================ COMPARISON OPERATORS

bool operator==( const pos3_s &lhs, const pos3_s &rhs );
bool operator!=( const pos3_s &lhs, const pos3_s &rhs );
bool operator>( const pos3_s &lhs, const pos3_s &rhs );
bool operator<( const pos3_s &lhs, const pos3_s &rhs );

// ================================ ARITHMETIC OPERATORS

pos3_s operator+( const pos3_s &lhs, const pos3_s &rhs );
pos3_s operator-( const pos3_s &lhs, const pos3_s &rhs );

pos3_s operator*( int lhs, const pos3_s &rhs );
pos3_s operator*( const pos3_s &lhs, int rhs );
pos3_s operator/( const pos3_s &lhs, int rhs );
pos3_s operator%( const pos3_s &lhs, int rhs );

pos3_s operator*( const pos3_s &lhs, float rhs );
pos3_s operator/( const pos3_s &lhs, float rhs );
pos3_s operator%( const pos3_s &lhs, float rhs );
pos3_s operator*( float lhs, const pos3_s &rhs );

pos3_s operator*( const pos3_s &lhs, double rhs );
pos3_s operator/( const pos3_s &lhs, double rhs );
pos3_s operator%( const pos3_s &lhs, double rhs );
pos3_s operator*( double lhs, const pos3_s &rhs );

// ================================ ASSIGNMENT OPERATORS

pos3_s &operator+=( pos3_s &lhs, const pos3_s &rhs );
pos3_s &operator-=( pos3_s &lhs, const pos3_s &rhs );

pos3_s &operator*=( pos3_s &lhs, int rhs );
pos3_s &operator/=( pos3_s &lhs, int rhs );
pos3_s &operator%=( pos3_s &lhs, int rhs );

pos3_s &operator*=( pos3_s &lhs, float rhs );
pos3_s &operator/=( pos3_s &lhs, float rhs );
pos3_s &operator%=( pos3_s &lhs, float rhs );

pos3_s &operator*= ( pos3_s &lhs, double rhs );
pos3_s &operator/= ( pos3_s &lhs, double rhs );
pos3_s &operator%= ( pos3_s &lhs, double rhs );

#endif // POS3_HPP