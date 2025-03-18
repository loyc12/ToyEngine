#ifndef POS2_HPP
# define POS2_HPP

# include "../defs.hpp"

typedef struct
{
	int x;
	int y;
} pos2_s;

typedef 	list< pos2_s > posList2_t ;
typedef vector< pos2_s > posVect2_t ;

pos2_s getNullPos2();

pos2_s getPos2( byte_t x, byte_t y );
pos2_s getPos2( word_t x, word_t y );
pos2_s getPos2( int x, int y );
pos2_s getPos2( long x, long y );
pos2_s getPos2( float x, float y );
pos2_s getPos2( double x, double y );

pos2_s getPos2( byte_t v );
pos2_s getPos2( word_t v );
pos2_s getPos2( int v );
pos2_s getPos2( long v );
pos2_s getPos2( float v );
pos2_s getPos2( double v );

// ================================ DISTANCE METHODS

float getXDist( const pos2_s &p1, const pos2_s &p2 );
float getYDist( const pos2_s &p1, const pos2_s &p2 );

float getShortLinearDist( const pos2_s &p1, const pos2_s &p2 );
float getLongLinearDist(  const pos2_s &p1, const pos2_s &p2 );

float getCartesianDist(   const pos2_s &p1, const pos2_s &p2 );
float getCircularDist(   const pos2_s &p1, const pos2_s &p2 );

// ================================ BOOLEAN METHODS

bool hasSameX(  const pos2_s &p1, const pos2_s &p2 );
bool hasSameY(  const pos2_s &p1, const pos2_s &p2 );
bool hasSameXY( const pos2_s &p1, const pos2_s &p2 );

// ================ AREAS

bool isWithin(     const pos2_s &point, const pos2_s &dists ); // sets the first point to 0,0,0
bool isInRect(     pos2_s const &point, pos2_s const &p1, pos2_s const &p2 );
bool isInSquare(   pos2_s const &point, pos2_s const &center, float radius );
bool isInCircle(   pos2_s const &point, pos2_s const &center, float radius );
bool isInEllipse(  pos2_s const &point, pos2_s const &center, float radX, float radY );
bool isInTirangle( pos2_s const &point, pos2_s const &p1, pos2_s const &p2, pos2_s const &p3 );


// ================================ LIST METHODS

posList2_t listPosInRect( pos2_s const &p1, pos2_s const &p2 );
posList2_t listPosInCube( pos2_s const &center, float radius );
posList2_t listPosInSphere( pos2_s const &center, float radius );


// ================================ COMPARISON OPERATORS

bool operator==( const pos2_s &lhs, const pos2_s &rhs );
bool operator!=( const pos2_s &lhs, const pos2_s &rhs );
bool operator>( const pos2_s &lhs, const pos2_s &rhs );
bool operator<( const pos2_s &lhs, const pos2_s &rhs );

// ================================ ARITHMETIC OPERATORS

pos2_s operator+( const pos2_s &lhs, const pos2_s &rhs );
pos2_s operator-( const pos2_s &lhs, const pos2_s &rhs );

pos2_s operator*( int lhs, const pos2_s &rhs );
pos2_s operator*( const pos2_s &lhs, int rhs );
pos2_s operator/( const pos2_s &lhs, int rhs );
pos2_s operator%( const pos2_s &lhs, int rhs );

pos2_s operator*( const pos2_s &lhs, float rhs );
pos2_s operator/( const pos2_s &lhs, float rhs );
pos2_s operator%( const pos2_s &lhs, float rhs );
pos2_s operator*( float lhs, const pos2_s &rhs );

pos2_s operator*( const pos2_s &lhs, double rhs );
pos2_s operator/( const pos2_s &lhs, double rhs );
pos2_s operator%( const pos2_s &lhs, double rhs );
pos2_s operator*( double lhs, const pos2_s &rhs );

// ================================ ASSIGNMENT OPERATORS

pos2_s &operator+=( pos2_s &lhs, const pos2_s &rhs );
pos2_s &operator-=( pos2_s &lhs, const pos2_s &rhs );

pos2_s &operator*=( pos2_s &lhs, int rhs );
pos2_s &operator/=( pos2_s &lhs, int rhs );
pos2_s &operator%=( pos2_s &lhs, int rhs );

pos2_s &operator*=( pos2_s &lhs, float rhs );
pos2_s &operator/=( pos2_s &lhs, float rhs );
pos2_s &operator%=( pos2_s &lhs, float rhs );

pos2_s &operator*= ( pos2_s &lhs, double rhs );
pos2_s &operator/= ( pos2_s &lhs, double rhs );
pos2_s &operator%= ( pos2_s &lhs, double rhs );

#endif // POS2_HPP