#ifndef SHAPE2_HPP
# define SHAPE2_HPP

# include "../defs.hpp"
#include "pos2.hpp"

typedef vector< Vector2 > V2Vect_t; // TODO : move me

typedef enum : byte_t
{
	SHAPE2_NULL,
	SHAPE2_POINT,
	SHAPE2_LINE,
	SHAPE2_TRIA,
	SHAPE2_RECT,
	SHAPE2_SQUR,
	SHAPE2_CIRC,
	SHAPE2_ELLI,
	SHAPE2_HEXA,
	SHAPE2_POLY,

} shape2Type_e;

typedef struct
{
	V2Vect_t verts;
	Vector2 center;
	float angle;
	shape2Type_e type;

} shape2_s;

// ================================ CONSTRUCTORS / CONVERTERS

shape2_s getNullShape2();
shape2_s getBaseShape2( shape2Type_e type, const Vector2 &ctr );
shape2_s getBaseShape2( shape2Type_e type, const Vector2 &ctr, float rad );
shape2_s getBaseShape2( shape2Type_e type, const Vector2 &ctr, float radX, float radY );

shape2_s getShape2Point( const Vector2 &ctr );

shape2_s getShape2Line( const Vector2 &p1,   const Vector2 &p2 );
shape2_s getShape2Line( const Vector2 &strt, const Vector2 &dir, float dist );
shape2_s getShape2Line( const Vector2 &ctr,  float angle,        float dist );

shape2_s getShape2Tri(  const Vector2 &p1,   const Vector2 &p2, const Vector2 &p3 );

shape2_s getShape2Rect( const Vector2 &p1,   const Vector2 &p2 );
shape2_s getShape2Rect( const Vector2 &ctr,  float radX, float radY );

shape2_s getShape2Square( const Vector2 &ctr, float rad );

shape2_s getShape2Circle( const Vector2 &ctr, float rad );
shape2_s getShape2Circle( const Vector2 &ctr, const Vector2 &edge );

shape2_s getShape2Ellipse( const Vector2 &ctr, float radX, float radY );

shape2_s getShape2Hexagon( const Vector2 &ctr, float rad );
shape2_s getShape2Hexagon( const Vector2 &ctr, float rad, float dir );

shape2_s getShape2Polygon( const Vector2 &ctr, float rad, int sides );
shape2_s getShape2Polygon( const Vector2 &ctr, float rad, int sides, float dir );


// ================================ DISTANCE METHODS

float getXDist( const shape2_s &s1, const shape2_s &s2 );
float getYDist( const shape2_s &s1, const shape2_s &s2 );

float getShortLinearDist( const shape2_s &s1, const shape2_s &s2 );
float getLongLinearDist(  const shape2_s &s1, const shape2_s &s2 );

float getCartesianDist( const shape2_s &s1, const shape2_s &s2 );
float getCircularDist(  const shape2_s &s1, const shape2_s &s2 );

// ================================ COMPARISON METHODS



// ================================ ACCESSORS

inline const V2Vect_t &getVerts(  const shape2_s &shape ) { return shape.verts; };
inline const Vector2  &getCenter( const shape2_s &shape ) { return shape.center; };
inline float           getAngle(  const shape2_s &shape ) { return shape.angle; };
inline shape2Type_e    getType(   const shape2_s &shape ) { return shape.type; };

Vector2 getTop(   const shape2_s &shape );
Vector2 getBot(   const shape2_s &shape );
Vector2 getLeft(  const shape2_s &shape );
Vector2 getRight( const shape2_s &shape );

Vector2 getTopLeft(  const shape2_s &shape );
Vector2 getTopRight( const shape2_s &shape );
Vector2 getBotLeft(  const shape2_s &shape );
Vector2 getBotRight( const shape2_s &shape );

float getWidth(  const shape2_s &shape );
float getHeight( const shape2_s &shape );
float getArea(   const shape2_s &shape );
float getPerim(  const shape2_s &shape );

float getMinRadius( const shape2_s &shape );
float getMaxRadius( const shape2_s &shape );
float getAvgRadius( const shape2_s &shape );

// =============================== SHAPE COMPARISON METHODS

bool hasSameX( const shape2_s &s1, const shape2_s &s2 );
bool hasSameY( const shape2_s &s1, const shape2_s &s2 );

bool hasSameCtr(   const shape2_s &s1, const shape2_s &s2 );
bool hasSameVert(  const shape2_s &s1, const shape2_s &s2 );
bool hasSameType(  const shape2_s &s1, const shape2_s &s2 );
bool hasSameAngle( const shape2_s &s1, const shape2_s &s2 );
bool hasSameArea(  const shape2_s &s1, const shape2_s &s2 );
bool hasSamePerim( const shape2_s &s1, const shape2_s &s2 );

bool overlaps( const shape2_s &s1, const shape2_s &s2 ); // checks if s1 overlaps s2
bool isOnEdge( const shape2_s &s1, const shape2_s &s2 ); // checks if s1 overlaps the edge of s2
bool isWithin( const shape2_s &s1, const shape2_s &s2 ); // checks if is entirely within s2
bool englobes( const shape2_s &s1, const shape2_s &s2 ); // checks if s2 is entirely within s1

bool isLarger(  const shape2_s &s1, const shape2_s &s2 ); // checks if s1's area is larger than s2
bool isSmaller( const shape2_s &s1, const shape2_s &s2 ); // checks if s1's area is smaller than s2
bool isLonger(  const shape2_s &s1, const shape2_s &s2 ); // checks if s1's perimeter is larger than s2
bool isShorter( const shape2_s &s1, const shape2_s &s2 ); // checks if s1's perimeter is smaller than s2

bool isCloseCirc(     const shape2_s &shape, const shape2_s &p, float dist );
bool isCloseCart( const shape2_s &shape, const shape2_s &p, float dist );

// ================================ POINT COMPARISON METHODS

float getXDist( const shape2_s &shape, const Vector2 &p );
float getYDist( const shape2_s &shape, const Vector2 &p );

float getShortCartDist( const shape2_s &shape, const Vector2 &p );
float getLongCartDist(  const shape2_s &shape, const Vector2 &p );

float getCartDist( const shape2_s &shape, const Vector2 &p );
float getCircDist( const shape2_s &shape, const Vector2 &p );

float getAngleWith(    const shape2_s &shape, const Vector2 &p );
float getAngleBetween( const shape2_s &shape, const Vector2 &p1, const Vector2 &p2 );

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


pos2_s operator*( int lhs, const pos2_s &rhs );
pos2_s operator*( const pos2_s &lhs, int rhs );
pos2_s operator/( const pos2_s &lhs, int rhs );
pos2_s operator%( const pos2_s &lhs, int rhs );

pos2_s operator*( float lhs, const pos2_s &rhs );
pos2_s operator*( const pos2_s &lhs, float rhs );
pos2_s operator/( const pos2_s &lhs, float rhs );
pos2_s operator%( const pos2_s &lhs, float rhs );

pos2_s operator*( double lhs, const pos2_s &rhs );
pos2_s operator*( const pos2_s &lhs, double rhs );
pos2_s operator/( const pos2_s &lhs, double rhs );
pos2_s operator%( const pos2_s &lhs, double rhs );

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

#endif // SHAPE2_HPP