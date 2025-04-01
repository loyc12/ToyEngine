#ifndef POS2_HPP
# define POS2_HPP

# include "../defs.hpp"

typedef int32_t posint_t;

typedef struct
{
	posint_t x; // left / right
	posint_t y; // up   / down

} pos2_s;

/*
typedef struct
{
	union
	{
		struct { float  x, y; };
		struct { int    i, j; };
		struct { byte_t b1, b2; };
	};
} pos2_s;
*/

typedef 	list< pos2_s > posList2_t ;
typedef vector< pos2_s > posVect2_t ;

// =============================== CONSTRUCTORS / CONVERTERS

pos2_s getNullPos2();

pos2_s  VtoP2( const Vector2 &vec );
Vector2 PtoV2( const pos2_s  &pos );

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

float getShortCartDist( const pos2_s &p1, const pos2_s &p2 );
float getLongCartDist(  const pos2_s &p1, const pos2_s &p2 );

float getCartDist( const pos2_s &p1, const pos2_s &p2 );
float getCircDist( const pos2_s &p1, const pos2_s &p2 );

// float getAngleWith(    const pos2_s &p1, const pos2_s &p2 );
// float getAngleBetween( const pos2_s &p1, const pos2_s &p2, const pos2_s &p3 );

// ================================ BOOLEAN METHODS

bool hasSameX(  const pos2_s &p1, const pos2_s &p2 );
bool hasSameY(  const pos2_s &p1, const pos2_s &p2 );
bool hasSameXY( const pos2_s &p1, const pos2_s &p2 );

// ================ AREAS

bool isWithin(     const pos2_s &p, const pos2_s &lens ); // sets the first point to 0,0,0
bool isInRect(     const pos2_s &p, const pos2_s &p1, pos2_s const &p2 );
bool isInSquare(   const pos2_s &p, const pos2_s &ctr, float rad );
bool isInCircle(   const pos2_s &p, const pos2_s &ctr, float rad );
bool isInEllipse(  const pos2_s &p, const pos2_s &ctr, float radX, float radY );
bool isInTriangle( const pos2_s &p, const pos2_s &p1, pos2_s const &p2, pos2_s const &p3 );

// ================================ LIST METHODS

posList2_t listPosInRect(   const pos2_s &p1, pos2_s const &p2 );
posList2_t listPosInCube(   const pos2_s &ctr, float rad );
posList2_t listPosInSphere( const pos2_s &ctr, float rad );

// ================================ COMPARISON OPERATORS

// TODO : implement these properly ( if needed )

bool operator==( const pos2_s &lhs, const pos2_s &rhs );
bool operator!=( const pos2_s &lhs, const pos2_s &rhs );
bool operator> ( const pos2_s &lhs, const pos2_s &rhs );
bool operator< ( const pos2_s &lhs, const pos2_s &rhs );

//bool operator>=( const pos2_s &lhs, const pos2_s &rhs );
//bool operator<=( const pos2_s &lhs, const pos2_s &rhs );
//bool operator&&( const pos2_s &lhs, const pos2_s &rhs );
//bool operator||( const pos2_s &lhs, const pos2_s &rhs );

//bool operator&( const pos2_s &lhs, const pos2_s &rhs );
//bool operator|( const pos2_s &lhs, const pos2_s &rhs );
//bool operator^( const pos2_s &lhs, const pos2_s &rhs );
//bool operator~( const pos2_s &lhs );
//bool operator!( const pos2_s &lhs );


// ================================ ARITHMETIC OPERATORS

pos2_s operator+(   const pos2_s &lhs, const pos2_s &rhs );
//pos2_s operator++(  const pos2_s &lhs, int ); // postfix
//pos2_s &operator++( const pos2_s &lhs ); //     prefix

pos2_s operator-(   const pos2_s &lhs, const pos2_s &rhs );
//pos2_s operator--(  const pos2_s &lhs, int ); // postfix
//pos2_s &operator--( const pos2_s &lhs ); //     prefix

pos2_s operator*( const pos2_s &lhs, const pos2_s &rhs );
pos2_s operator/( const pos2_s &lhs, const pos2_s &rhs );
pos2_s operator%( const pos2_s &lhs, const pos2_s &rhs );

//pos2_s operator+( const pos2_s &lhs, int rhs );
//pos2_s operator-( const pos2_s &lhs, int rhs );
pos2_s operator*( const pos2_s &lhs, int rhs );
pos2_s operator/( const pos2_s &lhs, int rhs );
pos2_s operator%( const pos2_s &lhs, int rhs );
pos2_s operator*( int lhs, const pos2_s &rhs );

//pos2_s operator+( const pos2_s &lhs, float rhs );
//pos2_s operator-( const pos2_s &lhs, float rhs );
pos2_s operator*( const pos2_s &lhs, float rhs );
pos2_s operator/( const pos2_s &lhs, float rhs );
pos2_s operator%( const pos2_s &lhs, float rhs );
pos2_s operator*( float lhs, const pos2_s &rhs );

//pos2_s operator+( const pos2_s &lhs, double rhs );
//pos2_s operator-( const pos2_s &lhs, double rhs );
pos2_s operator*( const pos2_s &lhs, double rhs );
pos2_s operator/( const pos2_s &lhs, double rhs );
pos2_s operator%( const pos2_s &lhs, double rhs );
pos2_s operator*( double lhs, const pos2_s &rhs );

// ================================ ASSIGNMENT OPERATORS

pos2_s &operator+=( pos2_s &lhs, const pos2_s &rhs );
pos2_s &operator-=( pos2_s &lhs, const pos2_s &rhs );

pos2_s &operator*=( pos2_s &lhs, const pos2_s &rhs );
pos2_s &operator/=( pos2_s &lhs, const pos2_s &rhs );
pos2_s &operator%=( pos2_s &lhs, const pos2_s &rhs );

//pos2_s &operator+=( pos2_s &lhs, int rhs );
//pos2_s &operator-=( pos2_s &lhs, int rhs );
pos2_s &operator*=( pos2_s &lhs, int rhs );
pos2_s &operator/=( pos2_s &lhs, int rhs );
pos2_s &operator%=( pos2_s &lhs, int rhs );

//pos2_s &operator+=( pos2_s &lhs, float rhs );
//pos2_s &operator-=( pos2_s &lhs, float rhs );
pos2_s &operator*=( pos2_s &lhs, float rhs );
pos2_s &operator/=( pos2_s &lhs, float rhs );
pos2_s &operator%=( pos2_s &lhs, float rhs );

//pos2_s &operator+=( pos2_s &lhs, double rhs );
//pos2_s &operator-=( pos2_s &lhs, double rhs );
pos2_s &operator*= ( pos2_s &lhs, double rhs );
pos2_s &operator/= ( pos2_s &lhs, double rhs );
pos2_s &operator%= ( pos2_s &lhs, double rhs );

#endif // POS2_HPP