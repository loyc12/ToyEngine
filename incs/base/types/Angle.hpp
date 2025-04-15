#ifndef ANGLE_HPP
# define ANGLE_HPP

# include <raylib.h>
# include "../defs.hpp"

class Angle
{
	protected:
		float _angle; // angle stored in radians

	public:
		// ============================ CONSTRUCTORS / DESTRUCTORS
		inline Angle() : _angle( 0.0f ){}
		inline Angle( const Angle &a ) :   _angle( a._angle ){}
		inline Angle( int angle ) :        _angle( pmod( angle * RtoD, TAU )){} // angle in degrees
		inline Angle( float angle ) :      _angle( pmod( angle, TAU )){} //        angle in radians
		inline Angle( double angle ) :     _angle( pmod( angle, TAU )){} //        angle in radians
		inline Angle( const Vector2 &v ) : _angle( atan2f( v.y, v.x )){} //        angle as a vector
		inline ~Angle(){};

		inline Angle operator=( const Angle &a ){   _angle = a._angle; return *this; }
		inline Angle operator=( int angle ){        _angle = pmod( angle * RtoD, TAU ); return *this; } // angle in degrees
		inline Angle operator=( float angle ){      _angle = pmod( angle, TAU ); return *this; } //        angle in radians
		inline Angle operator=( double angle ){     _angle = pmod( angle, TAU ); return *this; } //        angle in radians
		inline Angle operator=( const Vector2 &v ){ _angle = atan2f( v.y, v.x ); return *this; } //        angle as a vector

		// ============================ ACCESSORS / MUTATORS
		inline float get()    const { return _angle; } //       returns the angle in the range [0, TAU]
		inline float getPos() const { return _angle; } //       returns the angle in the range [0, TAU]
		inline float getCen() const { return _angle - PI; } //  returns the angle in the range [-PI, PI]
		inline float getNeg() const { return _angle - TAU; } // returns the angle in the range [-TAU, 0]

		inline void  set( int angle ){        _angle = pmod( angle * RtoD, TAU ); } // angle in degrees
		inline void  set( float angle ){      _angle = pmod( angle, TAU ); } //        angle in radians
		inline void  set( double angle ){     _angle = pmod( angle, TAU ); } //        angle in radians
		inline void  set( const Vector2 &v ){ _angle = atan2f( v.y, v.x ); } //        angle as a vector

		inline float toRad() const { return _angle; } //                 returns the angle in the range [0, TAU]
		inline float toDeg() const { return _angle * RtoD; } //          returns the angle in the range [0, 360]
		inline float toOne() const { return _angle / TAU; } //           returns the angle in the range [0, 1]
		inline float toTwo() const { return ( _angle / PI ) - 1.0f; } // returns the angle in the range [-1, 1]

		inline float cos() const { return cosf( _angle ); }
		inline float sin() const { return sinf( _angle ); }
		inline float tan() const { return tanf( _angle ); }

		inline float acos() const { return acosf( _angle ); }
		inline float asin() const { return asinf( _angle ); }
		inline float atan() const { return atanf( _angle ); }

		inline float cotan() const { return 1.0f / tanf( _angle ); }
		inline float sec()   const { return 1.0f / cosf( _angle ); }
		inline float csc()   const { return 1.0f / sinf( _angle ); }

		inline operator int()      const { return (int)_angle * RtoD; } // returns the angle in degrees
		inline operator float()    const { return (float)_angle; } //      returns the angle in radians
		inline operator double()   const { return (double)_angle; } //     returns the angle in radians
		inline operator Vector2()  const { return toVector2(); } //        returns the angle as a vector
		inline Vector2 toVector2() const { Vector2 v = { cosf( _angle ), sinf( _angle )}; return v; }

		// ============================ OPERATORS

		inline Angle operator+( const Angle &a ) const { return Angle( pmod( _angle + a._angle, TAU )); }
		inline Angle operator-( const Angle &a ) const { return Angle( pmod( _angle - a._angle, TAU )); }
		//inline Angle operator*( const Angle &a ) const { return Angle( pmod( _angle * a._angle, TAU )); }
		//inline Angle operator/( const Angle &a ) const { return Angle( pmod( _angle / a._angle, TAU )); }
		//inline Angle operator%( const Angle &a ) const { return Angle( pmod( _angle, a._angle )); }

		inline Angle operator==( const Angle &a ) const { return _angle == a._angle; }
		inline Angle operator!=( const Angle &a ) const { return _angle != a._angle; }

		//Checks the relative position of the angles // NOTE : check if all this is correct
		inline Angle operator<=( const Angle &a ) const { return cosf( a._angle - _angle ) <= +EPS; } // check if a is left  or equal to this
		inline Angle operator>=( const Angle &a ) const { return cosf( a._angle - _angle ) >= -EPS; } // check if a is right or equal to this

		inline Angle operator<(  const Angle &a ) const { return cosf( a._angle - _angle ) < 0.0f; } // check if a is left  of this
		inline Angle operator>(  const Angle &a ) const { return cosf( a._angle - _angle ) > 0.0f; } // check if a is right of this

		inline Angle operator|( const Angle &a ) const { return sinf( a._angle - _angle ) < 0.0f; } // check if a points the opposite way as this
		inline Angle operator^( const Angle &a ) const { return sinf( a._angle - _angle ) > 0.0f; } // check if a points the same way as this

		inline Angle operator&( const Angle &a ) const { return abs( sinf( a._angle - _angle )) < EPS; } // check if a points perpendicular to this



		// Moves the angle by n * 45 degrees in the given direction
		inline Angle operator<<( int n ){ _angle = pmod( _angle - ( n * PI / 4.0f ), TAU ); return *this; }
		inline Angle operator>>( int n ){ _angle = pmod( _angle + ( n * PI / 4.0f ), TAU ); return *this; }

		inline Angle operator!() const { return Angle( pmod( _angle - PI, TAU )); } // flips the angle
		inline Angle operator+() const { return Angle( pmod( _angle, TAU )); }
		inline Angle operator-() const { return Angle( pmod( -_angle, TAU )); }

		// increments / decrements the angle by 0.1 degrees
		inline Angle operator++(){ _angle = pmod( _angle + ( 0.1f * RtoD ), TAU ); return *this; }
		inline Angle operator--(){ _angle = pmod( _angle - ( 0.1f * RtoD ), TAU ); return *this; }

		// increments / decrements the angle by 0.1 degrees and returns the old value
		inline Angle operator++( int ){ Angle a = *this; _angle = pmod( _angle + ( 0.1f * RtoD ), TAU ); return a; }
		inline Angle operator--( int ){ Angle a = *this; _angle = pmod( _angle - ( 0.1f * RtoD ), TAU ); return a; }

		inline Angle operator+=( const Angle &a ){ _angle = pmod( _angle + a._angle, TAU ); return *this; }
		inline Angle operator-=( const Angle &a ){ _angle = pmod( _angle - a._angle, TAU ); return *this; }
		//inline Angle operator*=( const Angle &a ){ _angle = pmod( _angle * a._angle, TAU ); return *this; }
		//inline Angle operator/=( const Angle &a ){ _angle = pmod( _angle / a._angle, TAU ); return *this; }
		//inline Angle operator%=( const Angle &a ){ _angle = pmod( _angle, a._angle );       return *this; }

		friend std::ostream &operator<<( std::ostream &os, const Angle &a ){ os << a.toDeg() << " degrees"; return os;}
};

typedef Angle angle_t;

#endif // ANGLE_HPP