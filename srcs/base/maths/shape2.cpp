#include <raylib.h>
#include "../../../incs/base.hpp"

V2Vect_t CalcPolyVerts( byte_t facets )
{
	if ( facets < 2 )
	{
		qlog( "CalcPolyVerts : facets must be >= 2", WARN, 0 );
		return V2Vect_t();
	}
	V2Vect_t verts;   float angle = 360.0f / facets;

	for ( int i = 0; i < facets; i++ )
	{
		verts.push_back( { cosf( angle * i * DtoR ), sinf( angle * i * DtoR  )});
	}
	return verts;
}

Vector2 RotateVertex( const Vector2 &v, float angle ) // TODO : check if this is correct
{
	float x = v.x * cosf( angle * DtoR ) - v.y * sinf( angle * DtoR );
	float y = v.x * sinf( angle * DtoR ) + v.y * cosf( angle * DtoR );

	return { x, y };
}
float findAngle( const Vector2 &p1, const Vector2 &p2 ) // TODO : check if this is correct
{
	float angle = atan2( p2.y - p1.y, p2.x - p1.x ) * RtoD;
	if ( angle < 0 ){ angle += 360.0f; }

	return angle;
}

float getDistanceTo00( const Vector2 &p ){ return sqrt( sqr( p.x ) + sqr( p.y )); }
float getDistance(     const Vector2 &p1, const Vector2 &p2 ){ return sqrt( sqr( p1.x - p2.x ) + sqr( p1.y - p2.y )); }
float getTriangleArea( const Vector2 &p1, const Vector2 &p2, const Vector2 &p3 )
{
	return abs( ( p1.x * ( p2.y - p3.y ) + p2.x * ( p3.y - p1.y ) + p3.x * ( p1.y - p2.y )) / 2 );
}

// ================================== CONSTRUCTORS

Shape2::Shape2( sh2_type_e type, const Vector2 &ctr, const Vector2 &scl, float angle )
	: _type( type ), _angle( fmod( angle, 360.0f )), _center( ctr ), _scales( { scl.x, scl.y })
{
	flog( 0 );
	_verts = V2Vect_t();
	switch ( type )
	{
		case SH2_NULL: // makes a null shape
			qlog( "Shape2 : Generating a null shape", DEBUG, 0 );
			break;

		case SH2_POIN: // makes a point at the center
			_verts.push_back( Vector2() );
			break;

		case SH2_LINE: // makes a diagonal line going from 1,1 to -1,-1 - scale acordingly to change orientation
			_verts.push_back( { 1,  1  });
			_verts.push_back( { -1, -1 });
			break;

		case SH2_DIAM: // makes a diamond ( verts are corners )
			_verts.push_back( { 1,  0  });
			_verts.push_back( { 0,  1  });
			_verts.push_back( { -1, 0  });
			_verts.push_back( { 0, -1  });
			break;

		case SH2_SQUR: // use the smallest scale as the scale - rotate by 45 degrees for a diamond
			_scales.x = _scales.y = min( _scales.x, _scales.y );
			[[fallthrough]];

		case SH2_RECT: // makes a rectangle ( verts are corners )
			_verts.push_back( { 1,  1  });
			_verts.push_back( { -1, 1  });
			_verts.push_back( { -1, -1 });
			_verts.push_back( { 1,  -1 });
			break;

		case SH2_CIRC: // use the smallest scale as the scale
			_scales.x = _scales.y = min( _scales.x, _scales.y );
			[[fallthrough]];

		case SH2_ELLI: // makes an ellipse ( verts are +/- radii )
			_verts.push_back( { 1,  0  });
			_verts.push_back( { 0,  1  });
			_verts.push_back( { -1, 0  });
			_verts.push_back( { 0,  -1 });
			break;

		case SH2_TRIA: // makes a upright equilateral triangle
			_verts = CalcPolyVerts( 3 );   break;

		case SH2_PENT: // makes a pointy top pentagon - rotate by 36 degrees for a flat top pentagon
			_verts = CalcPolyVerts( 5 );   break;

		case SH2_HEXA: // makes a pointy top hexagon - rotate by 30 degrees for a flat top hexagon
			_verts = CalcPolyVerts( 6 );   break;

		case SH2_OCTA: // makes a pointy top octagon - rotate by 22.5 degrees for a flat top octagon
			_verts = CalcPolyVerts( 8 );   break;

		case SH2_DODE: // makes a pointy top dodecagon - rotate by 15 degrees for a flat top dodecagon
			_verts = CalcPolyVerts( 12 );  break;

		case SH2_POLY:
			qlog( "Shape2 : Vertex need to be manually set for polygons", INFO, 0 );
			break;

		default:
			qlog( "Shape2 : Unknown shape type : Generating a null shape instead", WARN, 0 );
			_type = SH2_NULL;
			break;
	}
}

Shape2::Shape2( const Shape2 &s ) : _type( s._type ), _angle( fmod( s._angle, 360.0f )), _center( s._center ), _scales( s._scales )
{
	flog( 0 );
	_verts = V2Vect_t();
	for ( auto &v : s._verts ){ _verts.push_back( v ); }
}

Shape2 Shape2::operator=( const Shape2 &s )
{
	flog( 0 );
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

// returns a line from p at angle dir, with length dist
Shape2 Shape2::Line( const Vector2 &p1, float angle, float dist )
{
	Vector2 p2 = { p1.x + cosf( angle * DtoR ) * dist, p1.y + sinf( angle * DtoR ) * dist };
	return Shape2::Line( p1, p2 );
}
// returns a line from p1 to p2, with the mean of the two points as center
Shape2 Shape2::Line( const Vector2 &p1, const Vector2 &p2 )
{
	Vector2 ctr = { ( p1.x + p2.x ) / 2, ( p1.y + p2.y ) / 2 };
	Vector2 scl = { ( p2.x - p1.x ) / 2, ( p2.y - p1.y ) / 2 }; // TODO : check if this is correct
	return Shape2( SH2_LINE, ctr, scl );
}
// returns a line with a given center and scale
Shape2 Shape2::Line2( const Vector2 &ctr, const Vector2 &scl ){ return Shape2( SH2_LINE, ctr, scl ); }
// returns a line going from p through the center to its opposite
Shape2 Shape2::Line3( const Vector2 &ctr, const Vector2 &p )
{
	Vector2 scl = { p.x - ctr.x, p.y - ctr.y };
	return Line2( ctr, scl );
}

// returns a equilateral triangle with the tip at p1
Shape2 Shape2::Triangle( const Vector2 &ctr, const Vector2 &tip ) // TODO : check if this is correct
{
	float scale = getDistance( ctr, tip );
	float angle = RtoD * atan2( tip.y - ctr.y, tip.x - ctr.x );
	return Shape2( SH2_TRIA, ctr, { scale, scale }, angle );
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

	float d1 = getDistanceTo00( np1 ); // TODO : check if this redundant maths
	float d2 = getDistanceTo00( np2 );
	float d3 = getDistanceTo00( np3 );
	float scl = ( d1 + d2 + d3 ) / 3;

	return Shape2( SH2_TRIA, ctr, { scl, scl }); // TODO : check if this is correct : forces it to be equilateral
}
Shape2 Shape2::Diamond( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	return Shape2( SH2_DIAM, ctr, scl, angle );
}

Shape2 Shape2::Square( const Vector2 &ctr, float scl, float angle )
{
	return Shape2( SH2_SQUR, ctr, { scl, scl }, angle );
}
Shape2 Shape2::Square( const Vector2 &ctr, const Vector2 &edge, float angle ) // TODO : check if this is correct
{
	Vector2 v = { edge.x - ctr.x, edge.y - ctr.y }; // gets the relative position of the edge from the center

	v = RotateVertex( v, -angle ); //               cancels out the rotation of the final shape

	float scl = max( abs( v.x ), abs( v.y )); // finds the scale needed for both axes to touch the edge

	return Shape2( SH2_SQUR, ctr, { scl, scl }, angle );
}
Shape2 Shape2::Rectangle( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	return Shape2( SH2_RECT, ctr, scl, angle );
}
Shape2 Shape2::Rectangle2( const Vector2 &p1, const Vector2 &p2, float angle ) // TODO : check if this is correct
{
	Vector2 ctr = { ( p1.x + p2.x ) / 2, ( p1.y + p2.y ) / 2 }; // finds the center of the rectangle

	Vector2 rp = { p1.x - ctr.x, p1.y - ctr.y }; // gets the relative position of a corner from the center

	rp = RotateVertex( rp, -angle ); //            cancels out the rotation of the final shape

	return Shape2( SH2_RECT, ctr, rp, angle ); // rp == scl here
}

Shape2 Shape2::Circle( const Vector2 &ctr, float scl )
{
	return Shape2( SH2_CIRC, ctr, { scl, scl } );
}
Shape2 Shape2::Circle( const Vector2 &ctr, const Vector2 &edge )
{
	float scl = getDistance( ctr, edge );
	return Shape2( SH2_CIRC, ctr, { scl, scl } );
}
Shape2 Shape2::Ellipse( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	return Shape2( SH2_ELLI, ctr, scl, angle );
}

Shape2 Shape2::Pentagon( const Vector2 &ctr, float scl, float angle ){ return Pentagon( ctr, { scl, scl }, angle ); }
Shape2 Shape2::Pentagon( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	Shape2 s( SH2_PENT, ctr, scl, angle );
	s._verts = CalcPolyVerts( 5 );
	return s;
}

Shape2 Shape2::Hexagon( const Vector2 &ctr, float scl, float angle ){ return Hexagon( ctr, { scl, scl }, angle ); }
Shape2 Shape2::Hexagon( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	Shape2 s( SH2_HEXA, ctr, scl, angle );
	s._verts = CalcPolyVerts( 6 );
	return s;
}

Shape2 Shape2::Octogon( const Vector2 &ctr, float scl, float angle ){ return Octogon( ctr, { scl, scl }, angle ); }
Shape2 Shape2::Octogon( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	Shape2 s( SH2_OCTA, ctr, scl, angle );
	s._verts = CalcPolyVerts( 8 );
	return s;
}

Shape2 Shape2::Dodecagon( const Vector2 &ctr, float scl, float angle ){ return Dodecagon( ctr, { scl, scl }, angle ); }
Shape2 Shape2::Dodecagon( const Vector2 &ctr, const Vector2 &scl, float angle )
{
	Shape2 s( SH2_DODE, ctr, scl, angle );
	s._verts = CalcPolyVerts( 12 );
	return s;
}

Shape2 Shape2::Polygon( const Vector2 &ctr, float scl, byte_t sides, float angle ){ return Polygon( ctr, { scl, scl }, sides, angle ); }
Shape2 Shape2::Polygon( const Vector2 &ctr, const Vector2 &scl, byte_t sides, float angle )
{
	if ( sides < 3 )
	{
		qlog( "Polygon : Polygon needs at least 3 vertices", WARN, 0 );
		return Shape2();
	}

	Shape2 s( SH2_POLY, ctr, scl, angle );
	s._verts = CalcPolyVerts( sides );
	return s;
}

Shape2 Shape2::Polygon( const V2Vect_t &worldVerts )
{
	if ( worldVerts.size() < 3 )
	{
		qlog( "Polygon : Polygon needs at least 3 vertices", WARN, 0 );
		return Shape2();
	}

	Vector2 ctr = { 0, 0 };
	for ( auto &v : worldVerts )
	{
		ctr.x += v.x;
		ctr.y += v.y;
	}
	ctr.x /= worldVerts.size();
	ctr.y /= worldVerts.size();

	Shape2 s( SH2_POIN, ctr, { 1, 1 }, 0 );
	s._type = SH2_POLY;

	for ( auto &v : worldVerts ){ s.addRawVertex({ v.x - ctr.x, v.y - ctr.y }); }

	return s;
}
Shape2 Shape2::Polygon( const Vector2 &ctr, const Vector2 &scl, const V2Vect_t &rawVerts, float angle )
{
	Shape2 s( SH2_POLY, ctr, scl, angle );
	s._verts = rawVerts;
	return s;
}

// ================================== ACCESSORS

V2Vect_t Shape2::getScaledVerts() const
{
	V2Vect_t verts;
	for ( auto &v : _verts )
	{
		Vector2 sv = v;
		sv.x *= _scales.x;
		sv.y *= _scales.y;
		verts.push_back( sv );
	}
	return verts;
}
V2Vect_t Shape2::getWorldVerts() const
{
	V2Vect_t verts;

	for ( auto &v : _verts ){ verts.push_back( RotateVertex( v, _angle )); }

	return verts;
}

// ================= VERTEX ACCESSORS

// compares the angle of each vertex and finds the ID of the one directly to the right of the given angle
int Shape2::getInsertRawID(    float angle ) const
{
	int id = 0;
	float min = INFINITY;

	for ( byte_t i = 0; i < ( byte_t )_verts.size(); i++ )
	{
		float a = atan2( _verts[ i ].y, _verts[ i ].x ) * RtoD;
		if ( a < 0 ){ a += 360.0f; }

		float d = abs( angle - a ); // TODO : check if this is correct
		if ( d < min )
		{
			min = d;
			id  = i;
		}
	}
	return id;
}

int Shape2::getInsertScaledID( float angle ) const
{
	int id = 0;
	float min = INFINITY;

	for ( byte_t i = 0; i < ( byte_t )_verts.size(); i++ )
	{
		Vector2 v = { _verts[ i ].x * _scales.x, _verts[ i ].y * _scales.y };

		float a = atan2( v.y, v.x ) * RtoD; // TODO : check if this is correct
		if ( a < 0 ){ a += 360.0f; }

		float d = abs( angle - a ); // TODO : check if this is correct
		if ( d < min )
		{
			min = d;
			id  = i;
		}
	}
	return id;
}
int Shape2::getInsertWorldID( float angle ) const
{
	int id = 0;
	float min = INFINITY;

	for ( byte_t i = 0; i < ( byte_t )_verts.size(); i++ )
	{
		Vector2 v = RotateVertex( { _verts[ i ].x * _scales.x, _verts[ i ].y * _scales.y }, _angle );

		float a = atan2( v.y, v.x ) * RtoD; // TODO : check if this is correct
		if ( a < 0 ){ a += 360.0f; }

		float d = abs( angle - a ); // TODO : check if this is correct
		if ( d < min )
		{
			min = d;
			id  = i;
		}
	}
	return id;
}

int Shape2::getNearestRawVertexID( const Vector2 &p ) const
{
	int id = 0;
	float min = INFINITY;

	for ( byte_t i = 0; i < ( byte_t )_verts.size(); i++ )
	{
		float d = getDistance( p, getRawVertex( i ));
		if ( d < min )
		{
			min = d;
			id  = i;
		}
	}

	return id;
}
int Shape2::getNearestScaledVertexID( const Vector2 &p ) const
{
	int id = 0;
	float min = INFINITY;

	for ( byte_t i = 0; i < ( byte_t )_verts.size(); i++ )
	{
		float d = getDistance( p, getScaledVertex( i ));
		if ( d < min )
		{
			min = d;
			id  = i;
		}
	}

	return id;
}
int Shape2::getNearestWorldVertexID( const Vector2 &p ) const
{
	int id = 0;
	float min = INFINITY;

	for ( byte_t i = 0; i < ( byte_t )_verts.size(); i++ )
	{
		float d = getDistance( p, getWorldVertex( i )); // TODO : check if this is correct
		if ( d < min )
		{
			min = d;
			id  = i;
		}
	}

	return id;
}

Vector2 Shape2::getRawVertex( int index ) const
{
	index %= _verts.size(); // wrap around

	return _verts[ index ];
}
Vector2 Shape2::getScaledVertex( int index ) const
{
	index %= _verts.size(); // wrap around

	Vector2 v = _verts[ index ];
	v.x *= _scales.x;
	v.y *= _scales.y;

	return v;
}
Vector2 Shape2::getWorldVertex( int index ) const
{
	index %= _verts.size(); // wrap around

	Vector2 v = _verts[ index ];
	v.x *= _scales.x;
	v.y *= _scales.y;

	v = RotateVertex( v, _angle );
	v.x += _center.x;
	v.y += _center.y;

	return v;
}

// ================================== MUTATORS


bool Shape2::addRawVertex( const Vector2 &p ){    return addRawVertex( p,    getInsertRawID(    findAngle( _center, p ))); }
bool Shape2::addRawVertex( const Vector2 &p, int index )
{
	index %= _verts.size(); // wrap around

	_verts.insert( _verts.begin() + index, p ); // TODO : check if this is correct
	return true;
}

bool Shape2::addScaledVertex( const Vector2 &p ){ return addScaledVertex( p, getInsertScaledID( findAngle( _center, p ))); }
bool Shape2::addScaledVertex( const Vector2 &p, int index )
{
	index %= _verts.size(); // wrap around

	Vector2 v = Vector2();
	if ( _scales.x != 0 ){ v.x = p.x / _scales.x; }
	if ( _scales.y != 0 ){ v.y = p.y / _scales.y; }

	_verts.insert( _verts.begin() + index, v ); // TODO : check if this is correct
	return true;
}

bool Shape2::addWorldVertex( const Vector2 &p ){  return addWorldVertex( p,  getInsertWorldID(  findAngle( _center, p ))); }
bool Shape2::addWorldVertex( const Vector2 &p, int index )
{
	index %= _verts.size(); // wrap around

	Vector2 v = Vector2();
	if ( _scales.x != 0 ){ v.x = p.x / _scales.x; }
	if ( _scales.y != 0 ){ v.y = p.y / _scales.y; }

	_verts.insert( _verts.begin() + index, RotateVertex( v, -_angle ) ); // TODO : check if this is correct
	return true;
}

void Shape2::setAngle(  float angle ){ _angle = fmod( angle, 360.0f ); }
void Shape2::moveAngle( float delta ){ setAngle( _angle + delta ); }

void Shape2::setCenter(  const Vector2 &ctr ){   _center = ctr; }
void Shape2::moveCenter( const Vector2 &delta ){ _center.x += delta.x; _center.y += delta.y; }

void Shape2::setScales(    const Vector2 &scl ){    _scales.x = scl.x; _scales.y = scl.y; }
void Shape2::changeScales( const Vector2 &factor ){ _scales.x *= factor.x; _scales.y *= factor.y; }

void Shape2::updateCenter()
{
	flog( 0 );
	// TODO : check if this is correct
	Vector2 ctr = Vector2();
	for ( auto &v : _verts )
	{
		ctr.x += v.x;
		ctr.y += v.y;
	}
	ctr.x /= _verts.size();
	ctr.y /= _verts.size();

	setCenter( ctr );

	Vector2 ctrDiff = { _center.x - ctr.x, _center.y - ctr.y }; // TODO : check if this is correct
	for ( auto &v : _verts )
	{
		v.x += ctrDiff.x;
		v.y += ctrDiff.y;
	}
}

void Shape2::updateType()
{
	flog( 0 );
	// NOTE : skips circular shapes for now
	if ( _type == SH2_CIRC || _type == SH2_ELLI ) return;

	switch( _verts.size() )
	{ // NOTE : ignores squares as they are just rectangles with equal scales anyways
		case 0:  _type = SH2_NULL; break;
		case 1:  _type = SH2_POIN; break;
		case 2:  _type = SH2_LINE; break;
		case 3:  _type = SH2_TRIA; break;
		case 4:  _type = SH2_RECT; break;
		case 5:  _type = SH2_PENT; break;
		case 6:  _type = SH2_HEXA; break;
		case 7:  _type = SH2_OCTA; break;
		case 8:  _type = SH2_DODE; break;
		default: _type = SH2_POLY; break;
	}
}

// ================================== SHAPE PROPERTIES

byte_t Shape2::getFacetC() const
{
	switch( _type )
	{
		case SH2_NULL: return 0;
		case SH2_POIN: return 0;
		case SH2_LINE: return 1;
		case SH2_CIRC: return 0;
		case SH2_ELLI: return 0;
		default:       return _verts.size();
	}
}

Vector2 Shape2::getTop() const // top = lowest y
{
	Vector2 top = Vector2();
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.y < top.y ){ top = sv; }
	}
	top.x += _center.x;
	top.y += _center.y;
	return top;
}
Vector2 Shape2::getBot() const // bottom = highest y
{
	Vector2 bot = Vector2();
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.y > bot.y ){ bot = sv; }
	}
	bot.x += _center.x;
	bot.y += _center.y;
	return bot;
}
Vector2 Shape2::getLeft() const // left = lowest x
{
	Vector2 left = Vector2();
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.x < left.x ){ left = sv; }
	}
	left.x += _center.x;
	left.y += _center.y;
	return left;
}
Vector2 Shape2::getRight() const // right = highest x
{
	Vector2 right = Vector2();
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.x > right.x ){ right = sv; }
	}
	right.x += _center.x;
	right.y += _center.y;
	return right;
}

// TODO : check if these are correct
Vector2 Shape2::getTopLeft() const // top = lowest y, left = lowest x
{
	Vector2 tl = Vector2();
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.x + sv.y < tl.x + tl.y ){ tl = sv; }
	}
	tl.x += _center.x;
	tl.y += _center.y;
	return tl;
}
Vector2 Shape2::getTopRight() const // top = lowest y, right = highest x
{
	Vector2 tr = Vector2();
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.x - sv.y > tr.x - tr.y ){ tr = sv; }
	}
	tr.x += _center.x;
	tr.y += _center.y;
	return tr;
}
Vector2 Shape2::getBotLeft() const // bottom = highest y, left = lowest x
{
	Vector2 bl = Vector2();
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.y - sv.x > bl.y - bl.x ){ bl = sv; }
	}
	bl.x += _center.x;
	bl.y += _center.y;
	return bl;
}
Vector2 Shape2::getBotRight() const // bottom = highest y, right = highest x
{
	Vector2 br = Vector2();
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.x + sv.y > br.x + br.y ){ br = sv; }
	}
	br.x += _center.x;
	br.y += _center.y;
	return br;
}

float Shape2::getMinY() const
{
	float min = -INFINITY;
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.y < min ){ min = sv.y; }
	}
	return min + _center.y;
}
float Shape2::getMaxY() const
{
	float max = INFINITY;
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.y > max ){ max = sv.y; }
	}
	return max + _center.y;
}
float Shape2::getMinX() const
{
	float min = -INFINITY;
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.x < min ){ min = sv.x; }
	}
	return min + _center.x;
}
float Shape2::getMaxX() const
{
	float max = INFINITY;
	for ( auto &v : _verts )
	{
		Vector2 sv = RotateVertex( v, _angle );
		if ( sv.x > max ){ max = sv.x; }
	}
	return max + _center.x;
}

float Shape2::getMinRadius() const
{
	float min = INFINITY;
	for ( auto &v : _verts )
	{
		float r = getDistanceTo00( v );
		if ( r < min ){ min = r; }
	}
	return min;
}
float Shape2::getMaxRadius() const
{
	float max = -INFINITY;
	for ( auto &v : _verts )
	{
		float r = getDistanceTo00( v );
		if ( r > max ){ max = r; }
	}
	return max;
}
float Shape2::getAvgRadius() const
{
	float avg = 0;

	for ( auto &v : _verts ){ avg += getDistanceTo00( v ); }

	return avg / _verts.size();
}

float Shape2::getPerim() const // TODO : check if this is correct
{
	float perim = 0;

	for ( byte_t i = 0; i < ( byte_t )_verts.size(); i++ ) // TODO : check if this is correct
	{
		const Vector2 p1 = _verts[ i ];
		const Vector2 p2 = _verts[( i + 1 ) % _verts.size() ]; // wrap around

		perim += getDistance( p1, p2 );
	}
	return perim;
}

float Shape2::getArea() const // TODO : check if this is correct
{
	if ( isArealess() )
	{
		qlog( "getArea : Not enough vertices to calculate area", WARN, 0 );
		return 0;
	}

	if ( isEliptical() )
	{
		float a = getMaxRadius();
		float b = getMinRadius();
		return PI * a * b;
	}

	if ( isRectangular() )
	{
		float a = getScaleX() * 2;
		float b = getScaleY() * 2;
		return a * b;
	}

	float area = 0;
	for ( byte_t i = 0; i < ( byte_t )_verts.size(); i++ )
	{ // Shoelace formula : TODO : check if this is correc
		const Vector2 p1 = _verts[ i ];
		const Vector2 p2 = _verts[( i + 1 ) % _verts.size() ]; // wrap around

		area += ( p1.x * p2.y ) - ( p2.x * p1.y );
	}
	return abs( area / 2 );
}

// ================================== PROPERTIES COMPARISON METHODS

bool Shape2::hasSameVerts( const Shape2 &s ) const
{ // NOTE : this only checks the vertex positions, not the scales or angles
	if ( _verts.size() != s._verts.size() ){ return false; }

	for ( byte_t i = 0; i < ( byte_t )_verts.size(); i++ )
	{
		if ( _verts[ i ].x != s._verts[ i ].x || _verts[ i ].y != s._verts[ i ].y ){ return false; }
	}
	return true;
}

// ================================== POINT DISTANCE METHODS

float Shape2::getShortCartDist( const Vector2 &p ) const
{
	float x = abs( p.x - _center.x );
	float y = abs( p.y - _center.y );
	return min( x, y );
}
float Shape2::getLongCartDist( const Vector2 &p ) const
{
	float x = abs( p.x - _center.x );
	float y = abs( p.y - _center.y );
	return max( x, y );
}
float Shape2::getSumCartDist( const Vector2 &p ) const
{
	float x = abs( p.x - _center.x );
	float y = abs( p.y - _center.y );
	return x + y;
}

// ================================== SHAPE COLLISION METHODS

// TODO : IMPLEMENT US

bool Shape2::overlaps( const Shape2 &s ) const
{
	if ( _type == SH2_NULL || s._type == SH2_NULL ){ return false; }

	( void )s; // TODO : remove this

	return false;
}

bool Shape2::isOnEdge( const Shape2 &s ) const
{
	if ( _type == SH2_NULL || s._type == SH2_NULL ){ return false; }

	( void )s; // TODO : remove this

	return false;
}

bool Shape2::isWithin( const Shape2 &s ) const
{
	if ( _type == SH2_NULL || s._type == SH2_NULL ){ return false; }

	( void )s; // TODO : remove this

	return false;
}

bool Shape2::englobes( const Shape2 &s ) const
{
	if ( _type == SH2_NULL || s._type == SH2_NULL ){ return false; }

	( void )s; // TODO : remove this

	return false;
}

// ================================== COMPARISON OPERATORS

bool operator==( const Shape2 &lhs, const Shape2 &rhs )
{
	if ( !lhs.hasSameType(  rhs )){ return false; }
	if ( !lhs.hasSameAngle( rhs )){ return false; }
	if ( !lhs.hasSameScl(   rhs )){ return false; }
	if ( !lhs.hasSameCtr(   rhs )){ return false; }
	if ( !lhs.hasSameVerts( rhs )){ return false; }
	return true;
}
bool operator!=( const Shape2 &lhs, const Shape2 &rhs )
{
	if ( !lhs.hasSameType(  rhs )){ return true; }
	if ( !lhs.hasSameAngle( rhs )){ return true; }
	if ( !lhs.hasSameScl(   rhs )){ return true; }
	if ( !lhs.hasSameCtr(   rhs )){ return true; }
	if ( !lhs.hasSameVerts( rhs )){ return true; }
	return false;
}

bool operator> ( const Shape2 &lhs, const Shape2 &rhs )
{
	if ( lhs.getArea() > rhs.getArea() ){ return true; }
	return false;
}
bool operator< ( const Shape2 &lhs, const Shape2 &rhs )
{
	if ( lhs.getArea() < rhs.getArea() ){ return true; }
	return false;
}
bool operator>=( const Shape2 &lhs, const Shape2 &rhs )
{
	if ( lhs.getArea() >= rhs.getArea() ){ return true; }
	return false;
}
bool operator<=( const Shape2 &lhs, const Shape2 &rhs )
{
	if ( lhs.getArea() <= rhs.getArea() ){ return true; }
	return false;
}

// ================================== ARITHMETIC OPERATORS

Shape2 operator*( float lhs, const Shape2 &rhs )
{
	Shape2 s = rhs;
	s.changeScales( { lhs, lhs });
	return s;
}
Shape2 operator*( const Shape2 &lhs, float rhs )
{
	Shape2 s = lhs;
	s.changeScales( { rhs, rhs });
	return s;
}
Shape2 operator/( const Shape2 &lhs, float rhs )
{
	if ( divtest( rhs )){ throw std::invalid_argument( "Invalid shape division" ); }

	Shape2 s = lhs;
	s.changeScales( { 1 / rhs, 1 / rhs });
	return s;
}

// ================================== ASSIGNMENT OPERATORS

Shape2 &operator*=( float rhs, Shape2 &lhs )
{
	lhs.changeScales( { rhs, rhs });
	return lhs;
}
Shape2 &operator*=( Shape2 &lhs, float rhs )
{
	lhs.changeScales( { rhs, rhs });
	return lhs;
}
Shape2 &operator/=( Shape2 &lhs, float rhs )
{
	if ( divtest( rhs )){ throw std::invalid_argument( "Invalid shape division" ); }

	lhs.changeScales( { 1 / rhs, 1 / rhs });
	return lhs;
}