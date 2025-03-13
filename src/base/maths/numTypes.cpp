#include "../../../inc/def/numTypes.hpp"
#include "../../../inc/deps.hpp"

// ================================ SCALAR

scalar_t percentToScalar( int value )   { return ( scalar_t ) ( value * SCALAR_MAX / 100 ); }
scalar_t permileToScalar( int value )   { return ( scalar_t ) ( value * SCALAR_MAX / 1000 ); }
scalar_t floatToScalar( float value )   { return ( scalar_t ) ( value * SCALAR_MAX ); }
scalar_t doubleToScalar( double value ) { return ( scalar_t ) ( value * SCALAR_MAX ); }

int    scalarToPercent( scalar_t value ) { return ( int ) ( value * 100 / SCALAR_MAX ); }
int    scalarToPermile( scalar_t value ) { return ( int ) ( value * 1000 / SCALAR_MAX ); }
float  scalarToFloat( scalar_t value )   { return ( float ) value / SCALAR_MAX; }
double scalarToDouble( scalar_t value ) { return ( double ) value / SCALAR_MAX; }

// ================================ ANGLE

scalar_t angleToScalar(  angle_t rotation ) { return rotation * SCALAR_MAX / ANGLE_MAX; }
float    angleToRadians( angle_t rotation ) { return ( float ) rotation * 2 * PI / ANGLE_MAX; }
float    angleToDegrees( angle_t rotation ) { return ( float ) rotation * 360 / ANGLE_MAX; }

angle_t scalarToAngle( scalar_t value ) { return value; }
angle_t radToAngle( float radians ) { return ( angle_t ) ( radians * ANGLE_MAX / ( 2 * PI ) ); }
angle_t degToAngle( float degrees ) { return ( angle_t ) ( degrees * ANGLE_MAX / 360 ); }

angle_t vectorToAngle( Vector2 vector ) { return radToAngle( atan2( vector.y, vector.x )); }
Vector2 angleToVector( angle_t rotation )
{
	float x = cos( angleToRadians( rotation ));
	float y = sin( angleToRadians( rotation ));

	return { x, y };
}

angle_t invAngle(  angle_t a ) { return a + ( ANGLE_MAX / 2 ); }