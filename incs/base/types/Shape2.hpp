#ifndef SHAPE2_HPP
# define SHAPE2_HPP

# include "../defs.hpp"

typedef vector< Vector2 > V2Vect_t; // TODO : move me

V2Vect_t calcPolyVerts( byte_t facets );

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
		Vector2    _center;
		Vector2    _scales;
		float      _angle;
		V2Vect_t   _verts;

	public:
	// ================================== CONSTRUCTORS / DESTRUCTORS
		inline Shape2() : _type( SH2_NULL ), _center( Vector2() ), _scales({ 1, 1 }), _angle( 0 ) { _verts = V2Vect_t(); };

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

		static Shape2 Triangle( const Vector2 &p1,  const Vector2 &tip );
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
		inline sh2_type_e     getType()       const { return _type; };
		inline byte_t 			  getFacetCount() const { return _verts.size(); };
		inline const Vector2  &getCenter()    const { return _center; };
		inline const Vector2  &getScales()    const { return _scales; };
		inline const V2Vect_t &getRawVerts()  const { return _verts; };

		inline float   getAngle()       const { return _angle; };
		inline Vector2 getAngleVector() const { return { cosf( _angle ), sinf( _angle )}; };

		Vector2   getScaledVertex( int index ) const;
		V2Vect_t  getScaledVerts() const;

	// ================================== SHAPE PROPERTIES
		Vector2 getTop()   const;
		Vector2 getBot()   const;
		Vector2 getLeft()  const;
		Vector2 getRight() const;

		Vector2 getTopLeft()  const;
		Vector2 getTopRight() const;
		Vector2 getBotLeft()  const;
		Vector2 getBotRight() const;

		float getWidth()  const;
		float getHeight() const;
		float getArea()   const;
		float getPerim()  const;

		float getMinRadius() const;
		float getMaxRadius() const;
		float getAvgRadius() const;

	// ================================== MUTATORS
		void setAngle( float angle );           void changeAngle( float delta );
		void setCenter( const Vector2 &ctr );   void changeCenter( const Vector2 &delta );
		void setScales( const Vector2 &scl );   void changeScales( const Vector2 &factor );

	// ================================== PROPERTIES COMPARISON METHODS
		bool hasSameX(   const Shape2 &s ) const;
		bool hasSameY(   const Shape2 &s ) const;
		bool hasSameCtr( const Shape2 &s ) const;

		bool hasSameRadX( const Shape2 &s ) const;
		bool hasSameRadY( const Shape2 &s ) const;
		bool hasSameRads( const Shape2 &s ) const;

		bool hasSameType(  const Shape2 &s ) const;
		bool hasSameFaces( const Shape2 &s ) const;
		bool hasSameVerts( const Shape2 &s ) const;
		bool hasSameAngle( const Shape2 &s ) const;
		bool hasSameArea(  const Shape2 &s ) const;
		bool hasSamePerim( const Shape2 &s ) const;

		bool hasSameWidth(  const Shape2 &s ) const;
		bool hasSameHeight( const Shape2 &s ) const;

		bool isLarger(  const Shape2 &s ) const; // checks if s1's area is larger than s2
		bool isSmaller( const Shape2 &s ) const; // checks if s1's area is smaller than s2
		bool isLonger(  const Shape2 &s ) const; // checks if s1's perimeter is larger than s2
		bool isShorter( const Shape2 &s ) const; // checks if s1's perimeter is smaller than s2

		bool isCloserCirc( const Vector2 &p, float dist ) const;
		bool isCloserCart( const Vector2 &p, float dist ) const;

	// ================================== SHAPE COMPARISON METHODS
		bool overlaps( const Shape2 &s ) const; // checks if s1 overlaps s2
		bool isOnEdge( const Shape2 &s ) const; // checks if s1 overlaps the edge of s2
		bool isWithin( const Shape2 &s ) const; // checks if s1 is entirely within s2
		bool englobes( const Shape2 &s ) const; // checks if s2 is entirely within s1

	// ================================== POINT COMPARISON METHODS
		float getXDist( const Vector2 &p ) const;
		float getYDist( const Vector2 &p ) const;

		float getShortCartDist( const Vector2 &p ) const;
		float getLongCartDist(  const Vector2 &p ) const;

		float getCartDist( const Vector2 &p ) const;
		float getCircDist( const Vector2 &p ) const;

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
		friend Shape2 operator%( const Shape2 &lhs, float rhs );

	// ================================== ASSIGNMENT OPERATORS
		//friend Shape2 &operator+=( Shape2 &lhs, const Shape2 &rhs );
		//friend Shape2 &operator-=( Shape2 &lhs, const Shape2 &rhs );

		friend Shape2 &operator*=( float rhs, Shape2 &lhs );
		friend Shape2 &operator*=( Shape2 &lhs, float rhs );
		friend Shape2 &operator/=( Shape2 &lhs, float rhs );
		friend Shape2 &operator%=( Shape2 &lhs, float rhs );

};

#endif // SHAPE2_HPP