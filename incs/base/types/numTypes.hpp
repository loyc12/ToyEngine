#ifndef NUMTYPES_HPP
# define NUMTYPES_HPP

# include "../defs.hpp"

// ================================ SCALAR

# define SCALAR_MAX 65535
typedef uint16_t scalar_t; // goes from 0 to 65535

scalar_t percentToScalar( int    value );
scalar_t permileToScalar( int    value );
scalar_t floatToScalar(   float  value );
scalar_t doubleToScalar(  double value );

int      scalarToPercent( scalar_t value );
int      scalarToPermile( scalar_t value );
float    scalarToFloat(   scalar_t value );
double   scalarToDouble(  scalar_t value );

// ================================ ANGLE

# define ANGLE_MAX 65535
typedef uint16_t angle_t; // goes from 0 to 65535

scalar_t angleToScalar(  angle_t rotation );
float    angleToRadians( angle_t rotation );
float    angleToDegrees( angle_t rotation );

angle_t scalarToAngle( scalar_t value );
angle_t radToAngle( float radians );
angle_t degToAngle( float degrees );

Vector2 angleToVector( angle_t rotation );
angle_t VectorToAngle( Vector2 vector );

angle_t invAngle(  angle_t a );

#endif // NUMTYPES_HPP