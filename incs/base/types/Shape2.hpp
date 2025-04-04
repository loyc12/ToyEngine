#ifndef SHAPE2_HPP
# define SHAPE2_HPP

# include <raylib.h>
# include "../defs.hpp"

typedef vector< Vector2 > V2Vect_t; // TODO : move me

V2Vect_t CalcPolyVerts(   byte_t facets );
Vector2  RotateVertex(    const Vector2 &v, float angle );
float    getTriangleArea( const Vector2 &p1, const Vector2 &p2, const Vector2 &p3 );
float    getDistance(     const Vector2 &p1, const Vector2 &p2 );
float    getDistanceTo00( const Vector2 &p );

typedef enum : byte_t
{
	SH2_NULL,
	SH2_POIN,
	SH2_LINE,
	SH2_SQUR,
	SH2_RECT,
	SH2_CIRC,
	SH2_ELLI,
	SH2_TRIA,
	SH2_PENT,
	SH2_HEXA,
	SH2_OCTA,
	SH2_DODE,
	SH2_POLY,

} sh2_type_e;

class Shape2
{
	protected:
	// ================================== MEMBERS
		sh2_type_e _type;
		float      _angle;
		Vector2    _center;
		Vector2    _scales;
		V2Vect_t   _verts;

	public:
	// ================================== CONSTRUCTORS / DESTRUCTORS
		inline Shape2() : _type( SH2_NULL ), _angle( 0 ), _center( Vector2() ), _scales({ 1, 1 }) { _verts = V2Vect_t(); };

		Shape2( sh2_type_e type, const Vector2 &ctr, const Vector2 &scl = { 1, 1 }, float angle = 0 );

		Shape2( const Shape2 &s );
		Shape2 operator=( const Shape2 &s );

		~Shape2() = default;

	// ================================== FACTORY METHODS

		inline static Shape2 Null() { return Shape2(); };
		inline static Shape2 Point( const Vector2 &ctr ) { return Shape2( SH2_POIN, ctr ); };

		// returns a line with a given center and scale
		static Shape2 Line( const Vector2 &ctr, const Vector2 &scl );
		// returns a line from p at angle dir, with length dist
		static Shape2 Line( const Vector2 &p1, float angle, float dist = 1 );
		// returns a line from p1 to p2, with the mean of the two points as center
		static Shape2 Line2( const Vector2 &p1, const Vector2 &p2 );
		// returns a line going from p through the center to its opposite
		static Shape2 Line3( const Vector2 &ctr, const Vector2 &p );

		static Shape2 Triangle( const Vector2 &ctr, const Vector2 &tip );
		static Shape2 Triangle( const Vector2 &ctr, const Vector2 &scl, float angle );
		static Shape2 Triangle( const Vector2 &p1,  const Vector2 &p2,  const Vector2 &p3 );

		static Shape2 Square( const Vector2 &ctr, float scl,           float angle = 0 );
		static Shape2 Square( const Vector2 &ctr, const Vector2 &edge, float angle = 0 );

		static Shape2 Rectangle(   const Vector2 &ctr, const Vector2 &scl, float angle = 0 );
		static Shape2 RectCorners( const Vector2 &p1,  const Vector2 &p2,  float angle = 0 );

		static Shape2 Circle( const Vector2 &ctr, float scl );
		static Shape2 Circle( const Vector2 &ctr, const Vector2 &edge );
		static Shape2 Elipse( const Vector2 &ctr, const Vector2 &scl, float angle = 0 );

		static Shape2 Pentagon( const Vector2 &ctr, float scl,          float angle = 0 );
		static Shape2 Pentagon( const Vector2 &ctr, const Vector2 &scl, float angle = 0 );

		static Shape2 Hexagon( const Vector2 &ctr, float scl,           float angle = 0 );
		static Shape2 Hexagon( const Vector2 &ctr, const Vector2 &scl,  float angle = 0 );

		static Shape2 Octogon( const Vector2 &ctr, float scl,           float angle = 0 );
		static Shape2 Octogon( const Vector2 &ctr, const Vector2 &scl,  float angle = 0 );

		static Shape2 Dodecagon( const Vector2 &ctr, float scl,          float angle = 0 );
		static Shape2 Dodecagon( const Vector2 &ctr, const Vector2 &scl, float angle = 0 );

		static Shape2 Polygon( const Vector2 &ctr, float scl, int sides, float angle = 0 );
		static Shape2 Polygon( const Vector2 &ctr, const Vector2 &scl, int sides, float angle = 0 );

	// ================================== ACCESSORS
		inline sh2_type_e     getType()    const { return _type; };
		inline byte_t 			  getFacetC()  const { return _verts.size(); };
		inline const Vector2  &getCenter() const { return _center; };
		inline const Vector2  &getScales() const { return _scales; };

		inline float   getAngle()       const { return _angle; };
		inline Vector2 getAngleVector() const { return { cosf( _angle ), sinf( _angle )}; };

		inline const V2Vect_t &getRawVerts()  const;
		V2Vect_t getScaledVerts() const;
		V2Vect_t getWorldVerts() const;

		// NOTE : Wraps around the index
		Vector2  getRawVertex(    int index ) const;
		Vector2  getScaledVertex( int index ) const;
		Vector2  getWorldVertex(  int index ) const;

	// ================================== SHAPE PROPERTIES
		Vector2 getTop()   const;
		Vector2 getBot()   const;
		Vector2 getLeft()  const;
		Vector2 getRight() const;

		Vector2 getTopLeft()  const;
		Vector2 getTopRight() const;
		Vector2 getBotLeft()  const;
		Vector2 getBotRight() const;

		float getMinY() const;
		float getMaxY() const;
		float getMinX() const;
		float getMaxX() const;

		// NOTE : the bound is a box that entirely contains the shape
		inline Vector2 getBoundTopLeft()  const { return { getMinX(), getMinY() }; }
		inline Vector2 getBoundTopRight() const { return { getMaxX(), getMinY() }; }
		inline Vector2 getBoundBotLeft()  const { return { getMinX(), getMaxY() }; }
		inline Vector2 getBoundBotRight() const { return { getMaxX(), getMaxY() }; }

		inline float getMinDist()  const { return min( getMinX(), getMinY() ); }
		inline float getMaxDist()  const { return max( getMaxX(), getMaxY() ); }

		inline float getWidth()    const { return getMaxX() - getMinX(); }
		inline float getHeight()   const { return getMaxY() - getMinY(); }

		inline float getMaxPerim() const { return 2 * ( getWidth() + getHeight() ); }
		inline float getMaxArea()  const { return getWidth() * getHeight(); }

		// NOTE : the radius is the distance from the center to the furthest vertex
		float getMinRadius() const;
		float getMaxRadius() const;
		float getAvgRadius() const;

		float getPerim()     const;
		float getArea()      const;

	// ================================== MUTATORS
		void setAngle( float angle );           void changeAngle( float delta );
		void setCenter( const Vector2 &ctr );   void changeCenter( const Vector2 &delta );
		void setScales( const Vector2 &scl );   void changeScales( const Vector2 &factor );

	// ================================== PROPERTIES COMPARISON METHODS
		inline bool hasSameX(     const Shape2 &s ) const { return ( _center.x == s._center.x ); };
		inline bool hasSameY(     const Shape2 &s ) const { return ( _center.y == s._center.y ); };
		inline bool hasSameCtr(   const Shape2 &s ) const { return ( _center.x == s._center.x && _center.y == s._center.y ); };
		inline bool hasSameSclX(  const Shape2 &s ) const { return ( _scales.x == s._scales.x ); };
		inline bool hasSameSclY(  const Shape2 &s ) const { return ( _scales.y == s._scales.y ); };
		inline bool hasSameScl(   const Shape2 &s ) const { return ( _scales.x == s._scales.x && _scales.y == s._scales.y ); };

		inline bool hasSameType(   const Shape2 &s ) const { return ( _type == s._type ); };
		inline bool hasSameFacetC( const Shape2 &s ) const { return ( _verts.size() == s._verts.size() ); };
		inline bool hasSameAngle(  const Shape2 &s ) const { return ( _angle == s._angle ); };

		inline bool hasSameWidth(  const Shape2 &s ) const { return ( getWidth() == s.getWidth() ); };
		inline bool hasSameHeight( const Shape2 &s ) const { return ( getHeight() == s.getHeight() ); };

		inline bool hasSameArea( const Shape2 &s ) const { return ( getArea() == s.getArea() ); };
		inline bool isLarger(    const Shape2 &s ) const { return ( getArea() >  s.getArea() ); };
		inline bool isSmaller(   const Shape2 &s ) const { return ( getArea() <  s.getArea() ); };

		inline bool hasSamePerim( const Shape2 &s ) const { return ( getPerim() == s.getPerim() ); };
		inline bool isLonger(     const Shape2 &s ) const { return ( getPerim() >  s.getPerim() ); };
		inline bool isShorter(    const Shape2 &s ) const { return ( getPerim() <  s.getPerim() ); };

		inline bool hasSameMaxRadius( const Shape2 &s ) const { return ( getMaxRadius() == s.getMaxRadius() ); };
		inline bool hasSameMinRadius( const Shape2 &s ) const { return ( getMinRadius() == s.getMinRadius() ); };
		inline bool hasSameAvgRadius( const Shape2 &s ) const { return ( getAvgRadius() == s.getAvgRadius() ); };

		bool hasSameVerts( const Shape2 &s )  const;

		// ================================== SHAPE COMPARISON METHODS
		bool overlaps( const Shape2 &s ) const; // checks if s1 overlaps s2
		bool isOnEdge( const Shape2 &s ) const; // checks if s1 overlaps the edge of s2
		bool isWithin( const Shape2 &s ) const; // checks if s1 is entirely within s2
		bool englobes( const Shape2 &s ) const; // checks if s2 is entirely within s1

		// ================================== POINT DISTANCE COMPARISON METHODS
		inline float getXDist( const Vector2 &p ) const { return abs( p.x - _center.x ); }
		inline float getYDist( const Vector2 &p ) const { return abs( p.y - _center.y ); }
		inline float getDist(  const Vector2 &p ) const { return getDistance( p, _center ); }

		float getShortCartDist( const Vector2 &p ) const;
		float getLongCartDist(  const Vector2 &p ) const;
		float getSumCartDist(   const Vector2 &p ) const;

		float getAngleWith(    const Vector2 &p ) const;
		float getAngleBetween( const Vector2 &p1, const Vector2 &p2 ) const;

	// ================================== COMPARISON OPERATORS
		friend bool operator==( const Shape2 &lhs, const Shape2 &rhs );
		friend bool operator!=( const Shape2 &lhs, const Shape2 &rhs );
		friend bool operator> ( const Shape2 &lhs, const Shape2 &rhs );
		friend bool operator< ( const Shape2 &lhs, const Shape2 &rhs );
		friend bool operator>=( const Shape2 &lhs, const Shape2 &rhs );
		friend bool operator<=( const Shape2 &lhs, const Shape2 &rhs );

		//friend bool operator&&( const Shape2 &lhs, const Shape2 &rhs );
		//friend bool operator||( const Shape2 &lhs, const Shape2 &rhs );
		//friend bool operator&(  const Shape2 &lhs, const Shape2 &rhs );
		//friend bool operator|(  const Shape2 &lhs, const Shape2 &rhs );

		//friend bool operator^( const Shape2 &lhs, const Shape2 &rhs );
		//friend bool operator~( const Shape2 &lhs );
		//friend bool operator!( const Shape2 &lhs );

	// ================================== ARITHMETIC OPERATORS
		//friend Shape2 operator+(   const Shape2 &lhs, float rhs );
		//friend Shape2 operator+(   const Shape2 &lhs, const Shape2 &rhs );
		//friend Shape2 operator++(  const Shape2 &lhs, int ); // postfix
		//friend Shape2 &operator++( const Shape2 &lhs ); //     prefix

		//friend Shape2 operator-(   const Shape2 &lhs, float rhs );
		//friend Shape2 operator-(   const Shape2 &lhs, const Shape2 &rhs );
		//friend Shape2 operator--(  const Shape2 &lhs, int ); // postfix
		//friend Shape2 &operator--( const Shape2 &lhs ); //     prefix

		friend Shape2 operator*( float lhs, const Shape2 &rhs );
		friend Shape2 operator*( const Shape2 &lhs, float rhs );
		friend Shape2 operator/( const Shape2 &lhs, float rhs );
		//friend Shape2 operator%( const Shape2 &lhs, float rhs );

	// ================================== ASSIGNMENT OPERATORS
		//friend Shape2 &operator+=( Shape2 &lhs, const Shape2 &rhs );
		//friend Shape2 &operator-=( Shape2 &lhs, const Shape2 &rhs );

		friend Shape2 &operator*=( float rhs, Shape2 &lhs );
		friend Shape2 &operator*=( Shape2 &lhs, float rhs );
		friend Shape2 &operator/=( Shape2 &lhs, float rhs );
		//friend Shape2 &operator%=( Shape2 &lhs, float rhs );

};

#endif // SHAPE2_HPP