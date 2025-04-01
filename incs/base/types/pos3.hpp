#ifndef POS3_HPP
# define POS3_HPP

# include "../defs.hpp"
# include "./pos2.hpp"

typedef struct
{
	posint_t x; // left  / right
	posint_t y; // up    / down
	posint_t z; // front / back

} pos3_s;

typedef 	list< pos3_s > posList3_t ;
typedef vector< pos3_s > posVect3_t ;

// =============================== CONSTRUCTORS / CONVERTERS

pos3_s getNullPos3();

pos2_s  P3toP2( const pos3_s  &pos );
pos3_s  P2toP3( const pos2_s  &pos );
pos3_s  VtoP3(  const Vector3 &vec );
Vector3 PtoV3(  const pos3_s  &pos );

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

float getShortCartDist( const pos3_s &p1, const pos3_s &p2 );
float getLongCartDist(  const pos3_s &p1, const pos3_s &p2 );

float getCartDist(  const pos3_s &p1, const pos3_s &p2 );
float getSpheDist(  const pos3_s &p1, const pos3_s &p2 );
float getCylinDist( const pos3_s &p1, const pos3_s &p2 );

// Rotated versions of the above function, for when the cylinder is aligned with the X or Z axis instead of the Y axis ( upright )
float getCylinDistX( const pos3_s &p1, const pos3_s &p2 );
float getCylinDistZ( const pos3_s &p1, const pos3_s &p2 );

// ================================ BOOLEAN METHODS

bool hasSameX( const pos3_s &p1, const pos3_s &p2 );
bool hasSameZ( const pos3_s &p1, const pos3_s &p2 );
bool hasSameY( const pos3_s &p1, const pos3_s &p2 );

bool hasSameXZ( const pos3_s &p1, const pos3_s &p2 );
bool hasSameYZ( const pos3_s &p1, const pos3_s &p2 );
bool hasSameXY( const pos3_s &p1, const pos3_s &p2 );

// ================ RECTANGULAR VOLUMES

bool isWithin(  const pos3_s &p, const pos3_s &lens ); // sets the first point to 0,0,0
bool isInRect(  const pos3_s &p, const pos3_s &p1, const pos3_s &p2 );
bool isInCube(  const pos3_s &p, const pos3_s &ctr, float rad );
bool isInPrism( const pos3_s &p, const pos3_s &ctr, float radX, float radY, float radZ );

// bool isInTethraedron( pos3_s const &p, pos3_s const &p1, pos3_s const &p2, pos3_s const &p3, pos3_s const &p4 );

// ================ SPHERICAL VOLUMES

bool isInSphere(   const pos3_s &p, const pos3_s &ctr, float rad );
bool isInSpheroid( const pos3_s &p, const pos3_s &ctr, float radX, float radY, float radZ );

// ================ CYLINDRICAL VOLUMES

bool isInCylin(   const pos3_s &p, const pos3_s &ctr, float rad, float halfH );
bool isInCone(    const pos3_s &p, const pos3_s &ctr, float rad, float halfH );
bool isInInvCone( const pos3_s &p, const pos3_s &ctr, float rad, float halfH );
bool isInConoid(  const pos3_s &p, const pos3_s &ctr, float radBot, float radTop, float halfH );

// Rotated versions of the above functions, for when the conoid is aligned with the X or Z axis instead of the Y axis ( upright )
bool isInXCylin(   const pos3_s &p, const pos3_s &ctr, float rad, float halfH );
bool isInZCylin(   const pos3_s &p, const pos3_s &ctr, float rad, float halfH );

bool isInXCone(    const pos3_s &p, const pos3_s &ctr, float rad, float halfH );
bool isInZCone(    const pos3_s &p, const pos3_s &ctr, float rad, float halfH );

bool isInXInvCone( const pos3_s &p, const pos3_s &ctr, float rad, float halfH );
bool isInZInvCone( const pos3_s &p, const pos3_s &ctr, float rad, float halfH );

bool isInXConoid(  const pos3_s &p, const pos3_s &ctr, float radSouth, float radNorth, float halfH );
bool isInZConoid(  const pos3_s &p, const pos3_s &ctr, float radEast,  float radWest,  float halfH );

// TODO : implement these ( requires a lot of math Xd )
// Rotated versions of the above functions, for when the conoid is arbitrary rotated ( p1-->p2 vector )
//bool isInCylinder( pos3_s const &p, pos3_s const &p1, pos3_s const &p2, float rad );
//bool isInCone(     pos3_s const &p, pos3_s const &p1, pos3_s const &p2, float r1 );
//bool isInInvCone(  pos3_s const &p, pos3_s const &p1, pos3_s const &p2, float r2 );
//bool isInConoid(   pos3_s const &p, pos3_s const &p1, pos3_s const &p2, float r1, float r2 );

// ================================ LIST METHODS

posList3_t listPosInRect(   const pos3_s &p1, pos3_s const &p2 );
posList3_t listPosInCube(   const pos3_s &ctr, float rad );
posList3_t listPosInSphere( const pos3_s &ctr, float rad );

// ================================ COMPARISON OPERATORS

// TODO : implement these properly ( if needed )

bool operator==( const pos3_s &lhs, const pos3_s &rhs );
bool operator!=( const pos3_s &lhs, const pos3_s &rhs );
bool operator> ( const pos3_s &lhs, const pos3_s &rhs );
bool operator< ( const pos3_s &lhs, const pos3_s &rhs );

//bool operator>=( const pos3_s &lhs, const pos3_s &rhs );
//bool operator<=( const pos3_s &lhs, const pos3_s &rhs );
//bool operator&&( const pos3_s &lhs, const pos3_s &rhs );
//bool operator||( const pos3_s &lhs, const pos3_s &rhs );

//bool operator&( const pos3_s &lhs, const pos3_s &rhs );
//bool operator|( const pos3_s &lhs, const pos3_s &rhs );
//bool operator^( const pos3_s &lhs, const pos3_s &rhs );
//bool operator~( const pos3_s &lhs );
//bool operator!( const pos3_s &lhs );


// ================================ ARITHMETIC OPERATORS

pos3_s operator+(   const pos3_s &lhs, const pos3_s &rhs );
//pos3_s operator++(  const pos3_s &lhs, int ); // postfix
//pos3_s &operator++( const pos3_s &lhs ); //     prefix

pos3_s operator-(   const pos3_s &lhs, const pos3_s &rhs );
//pos3_s operator--(  const pos3_s &lhs, int ); // postfix
//pos3_s &operator--( const pos3_s &lhs ); //     prefix

pos3_s operator*( const pos3_s &lhs, const pos3_s &rhs );
pos3_s operator/( const pos3_s &lhs, const pos3_s &rhs );
pos3_s operator%( const pos3_s &lhs, const pos3_s &rhs );

pos3_s operator*( int lhs, const pos3_s &rhs );
pos3_s operator*( const pos3_s &lhs, int rhs );
pos3_s operator/( const pos3_s &lhs, int rhs );
pos3_s operator%( const pos3_s &lhs, int rhs );

pos3_s operator*( float lhs, const pos3_s &rhs );
pos3_s operator*( const pos3_s &lhs, float rhs );
pos3_s operator/( const pos3_s &lhs, float rhs );
pos3_s operator%( const pos3_s &lhs, float rhs );

pos3_s operator*( double lhs, const pos3_s &rhs );
pos3_s operator*( const pos3_s &lhs, double rhs );
pos3_s operator/( const pos3_s &lhs, double rhs );
pos3_s operator%( const pos3_s &lhs, double rhs );

// ================================ ASSIGNMENT OPERATORS

pos3_s &operator+=( pos3_s &lhs, const pos3_s &rhs );
pos3_s &operator-=( pos3_s &lhs, const pos3_s &rhs );

pos3_s &operator*=( pos3_s &lhs, const pos3_s &rhs );
pos3_s &operator/=( pos3_s &lhs, const pos3_s &rhs );
pos3_s &operator%=( pos3_s &lhs, const pos3_s &rhs );

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