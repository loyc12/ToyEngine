#include <raylib.h>
#include "../../../incs/base.hpp"

V2Vect_t calcPolyVerts( byte_t facets )
{
	if ( facets < 2 )
	{
		log( "calcPolyVerts() : facets must be >= 2", WARN );
		return V2Vect_t();
	}

	V2Vect_t verts;   float angle = 360.0f / facets;

	for ( int i = 0; i < facets; i++ ){ verts.push_back( { cosf( angle * i * DtoR ), sinf( angle * i * DtoR  )}); }

	return verts;
}

// ================================== CONSTRUCTORS

Shape2::Shape2( sh2_type_e type, const Vector2 &ctr, const Vector2 &scl, float angle )
	: _type( type ), _center( ctr ), _scales( scl ), _angle( angle )
{
	_verts = V2Vect_t();
	switch ( type )
	{
		case SH2_NULL: // makes a null shape
			log("Shape2::Shape2() : Generating a null shape", DEBUG );
			break;

		case SH2_POIN: // makes a point at the center
			_verts.push_back( Vector2() );
			break;

		case SH2_LINE: // makes a diagonal line going from 1,1 to -1,-1 - scale acordingly to change orientation
			_verts.push_back( { 1,  1 });
			_verts.push_back( { -1, -1 });
			break;

		case SH2_SQUR: // use the smallest scale as the scale - rotate by 45 degrees for a diamond
			_scales.x = _scales.y = min( _scales.x, _scales.y );
			[[fallthrough]];

		case SH2_RECT: // makes a rectangle ( verts are corners )
			_verts.push_back( { 1,  1 });
			_verts.push_back( { 1,  -1 });
			_verts.push_back( { -1, -1 });
			_verts.push_back( { -1, 1 });
			break;

		case SH2_CIRC: // use the smallest scale as the scale
			_scales.x = _scales.y = min( _scales.x, _scales.y );
			[[fallthrough]];

		case SH2_ELLI: // makes an ellipse ( verts are +/- radii )
			_verts.push_back( { 1,  0 });
			_verts.push_back( { 0,  1 });
			_verts.push_back( { -1, 0 });
			_verts.push_back( { 0,  -1 });
			break;

		case SH2_TRIA: // makes a upright equilateral triangle
			_verts = calcPolyVerts( 3 );   break;

		case SH2_PENT: // makes a pointy top pentagon - rotate by 36 degrees for a flat top pentagon
			_verts = calcPolyVerts( 5 );   break;

		case SH2_HEXA: // makes a pointy top hexagon - rotate by 30 degrees for a flat top hexagon
			_verts = calcPolyVerts( 6 );   break;

		case SH2_OCTA: // makes a pointy top octagon - rotate by 22.5 degrees for a flat top octagon
			_verts = calcPolyVerts( 8 );   break;

		case SH2_DODE: // makes a pointy top dodecagon - rotate by 15 degrees for a flat top dodecagon
			_verts = calcPolyVerts( 12 );  break;

		case SH2_POLY:
			log( "Shape2::Shape2() : Vertex need to be manually set for polygons", DEBUG );
			break;

		default:
			log( "Shape2::Shape2() : Unknown shape type", WARN );
			_type = SH2_NULL;
			break;
	}
}

Shape2::Shape2( const Shape2 &s ) : _type( s._type ), _center( s._center ), _scales( s._scales ), _angle( s._angle )
{
	_verts = V2Vect_t();
	for ( auto &v : s._verts ){ _verts.push_back( v ); }
}

Shape2 Shape2::operator=( const Shape2 &s )
{
	if ( this != &s )
	{
		_type   = s._type;
		_center = s._center;
		_scales = s._scales;
		_angle  = s._angle;

		_verts.clear();
		for ( auto &v : s._verts ){ _verts.push_back( v ); }
	}

	return *this;
}

// ================================== FACTORY METHODS

// returns a line with a given center and scale
Shape2 Shape2::Line( const Vector2 &ctr, const Vector2 &scl ) { return Shape2( SH2_LINE, ctr, scl ); }
// returns a line from p at angle dir, with length dist
Shape2 Shape2::Line( const Vector2 &p1, float angle, float dist )
{
	Vector2 p2 = { p1.x + cosf( angle * DtoR ) * dist, p1.y + sinf( angle * DtoR ) * dist };
	return Shape2::Line2( p1, p2 );
}
// returns a line from p1 to p2, with the mean of the two points as center
Shape2 Shape2::Line2( const Vector2 &p1, const Vector2 &p2 )
{
	Vector2 ctr = { ( p1.x + p2.x ) / 2, ( p1.y + p2.y ) / 2 };
	Vector2 scl = { ( p2.x - p1.x ) / 2, ( p2.y - p1.y ) / 2 }; // TODO : check if this is correct
	return Shape2( SH2_LINE, ctr, scl );
}
// returns a line going from p through the center to its opposite
Shape2 Shape2::Line3( const Vector2 &ctr, const Vector2 &p )
{
	Vector2 scl = { p.x - ctr.x, p.y - ctr.y };
	return Line( ctr, scl );
}

// returns a equilateral triangle with the tip at p1
Shape2 Shape2::Triangle( const Vector2 &p1, const Vector2 &tip )
{
	float scale = sqrt( sqr( p1.x - tip.x ) + sqr( p1.y - tip.y ));
	float angle =  RtoD * atan2( tip.y - p1.y, tip.x - p1.x );
	return Shape2( SH2_TRIA, tip, { scale, scale }, angle );
}
// returns a triangle with the center at ctr and a scale of scl
Shape2 Shape2::Triangle( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	return Shape2( SH2_TRIA, ctr, scl, angle );
}
// returns a triangle with the center at the mean of p1, p2 and p3, and with normalized vertexes
// NOTE : the triangle is not guaranteed to be equilateral, not its rotation upright
Shape2 Shape2::Triangle( const Vector2 &p1, const Vector2 &p2, const Vector2 &p3 )
{
	Vector2 ctr = { ( p1.x + p2.x + p3.x ) / 3, ( p1.y + p2.y + p3.y ) / 3 };
	Vector2 np1 = { p1.x - ctr.x, p1.y - ctr.y };
	Vector2 np2 = { p2.x - ctr.x, p2.y - ctr.y };
	Vector2 np3 = { p3.x - ctr.x, p3.y - ctr.y };

	float d1 = sqrt( sqr( np1.x ) + sqr( np1.y ) ); // TODO : check if this isn't redundant
	float d2 = sqrt( sqr( np2.x ) + sqr( np2.y ) );
	float d3 = sqrt( sqr( np3.x ) + sqr( np3.y ) );
	float scl = ( d1 + d2 + d3 ) / 3;

	return Shape2( SH2_TRIA, ctr, { scl, scl }); // TODO : check if this is correct
}

Shape2 Shape2::Square( const Vector2 &ctr, float scl, float angle )
{
	return Shape2( SH2_SQUR, ctr, { scl, scl }, angle );
}
Shape2 Shape2::Square( const Vector2 &ctr, const Vector2 &edge, float angle )
{ // NOTE : ignores the angle when finding a square that fits
	// TODO : stop ignoring it
	float scl = min( edge.x - ctr.x, edge.y - ctr.y );
	return Shape2( SH2_SQUR, ctr, { scl, scl }, angle );
}
Shape2 Shape2::Rectangle( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	return Shape2( SH2_RECT, ctr, scl, angle );
}
Shape2 Shape2::RectCorners( const Vector2 &p1, const Vector2 &p2, float angle )
{ // NOTE : ignores the angle when finding a rectangle that fits
	// TODO : stop ignoring it
	Vector2 ctr = { ( p1.x + p2.x ) / 2, ( p1.y + p2.y ) / 2 };
	Vector2 scl = { ( p2.x - p1.x ) / 2, ( p2.y - p1.y ) / 2 };
	return Shape2( SH2_RECT, ctr, scl, angle );
}

Shape2 Shape2::Circle( const Vector2 &ctr, float scl )
{
	return Shape2( SH2_CIRC, ctr, { scl, scl } );
}
Shape2 Shape2::Circle( const Vector2 &ctr, const Vector2 &edge )
{
	float scl = sqrt( sqr( edge.x - ctr.x) + sqr( edge.y - ctr.y ));
	return Shape2( SH2_CIRC, ctr, { scl, scl } );
}
Shape2 Shape2::Elipse( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	return Shape2( SH2_ELLI, ctr, scl, angle );
}

Shape2 Shape2::Pentagon( const Vector2 &ctr, float scl, float angle ) { return Pentagon( ctr, { scl, scl }, angle ); }
Shape2 Shape2::Pentagon( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	Shape2 s( SH2_PENT, ctr, scl, angle );
	s._verts = calcPolyVerts( 5 );
	return s;
}

Shape2 Shape2::Hexagon( const Vector2 &ctr, float scl, float angle ){ return Hexagon( ctr, { scl, scl }, angle ); }
Shape2 Shape2::Hexagon( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	Shape2 s( SH2_HEXA, ctr, scl, angle );
	s._verts = calcPolyVerts( 6 );
	return s;
}

Shape2 Shape2::Octogon( const Vector2 &ctr, float scl, float angle ){ return Octogon( ctr, { scl, scl }, angle ); }
Shape2 Shape2::Octogon( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	Shape2 s( SH2_OCTA, ctr, scl, angle );
	s._verts = calcPolyVerts( 8 );
	return s;
}

Shape2 Shape2::Dodecagon( const Vector2 &ctr, float scl, float angle ){ return Dodecagon( ctr, { scl, scl }, angle ); }
Shape2 Shape2::Dodecagon( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	Shape2 s( SH2_DODE, ctr, scl, angle );
	s._verts = calcPolyVerts( 12 );
	return s;
}

Shape2 Shape2::Polygon( const Vector2 &ctr, float scl, int sides, float angle ){ return Polygon( ctr, { scl, scl }, sides, angle ); }
Shape2 Shape2::Polygon( const Vector2 &ctr, const Vector2 &scl, int sides, float angle )
{
	if ( sides < 3 )
	{
		log( "Shape2::Polygon() : sides must be >= 3", WARN );
		return Shape2();
	}

	Shape2 s( SH2_POLY, ctr, scl, angle );
	s._verts = calcPolyVerts( sides );
	return s;
}

// ================================== ACCESSORS



