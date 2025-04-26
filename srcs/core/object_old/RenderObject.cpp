#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

void RenderObject::onAdd()
{
	flog( getID() );
	_isVisible = true;

	// set default color and shape
	_color = WHITE;
}

void RenderObject::onCpy( const RenderObject &obj )
{
	flog( getID() );
	_isVisible = obj.getIsVisible();
}

void RenderObject::onDel()
{
	flog( getID() );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

RenderObject::RenderObject() :
	BaseObject( E_RENDER ),
	ShapeObject()
{
	flog( getID() );
	RenderObject::onAdd();
}

RenderObject::RenderObject( const RenderObject &obj ) :
	BaseObject( obj ),
	ShapeObject( obj )
{
	flog( getID() );
	if ( this == &obj ) return;

	RenderObject::onAdd();
	RenderObject::onCpy( obj );
}

RenderObject &RenderObject::operator=( const RenderObject &obj )
{
	flog( getID() );
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	ShapeObject::onCpy( obj );

	RenderObject::onCpy( obj );

	return *this;
}

RenderObject::~RenderObject() // automatic inverted call order
{
	flog( getID() );
	RenderObject::onDel();
	// ShapeObject::onDel();
	// BaseObject::onDel();
}

// ================================ ACCESSORS / MUTATORS

bool RenderObject::getIsVisible() const { return _isVisible; }
void RenderObject::setIsVisible( bool isVisible ){ _isVisible = isVisible; }

Color RenderObject::getColor() const { return _color; }
void  RenderObject::setColor( Color color ){ _color = color; }

// ================================ TICK METHODS

bool RenderObject::renderSelf()
{
	flog( getID() );
	if ( getShapeType() == SH2_NULL ) return false;

	Shape2 s = getShape();
	if ( s.isPoint() )
	{
		DrawCircle( s.getCenter().x, s.getCenter().y, 4, _color );
	}
	elif ( s.isLine() )
	{
		Vector2 p1 = s.getWorldVertex( 0 );
		Vector2 p2 = s.getWorldVertex( 1 );
		DrawLine( p1.x, p1.y, p2.x, p2.y, _color );
	}
	if ( s.isEliptical() ) // NOTE Ellipses are not supported in raylib : Using DrawCircle instead
	{                      // TODO : implement ellipses
		DrawCircle( s.getCenter().x, s.getCenter().y, s.getAvgScale(), _color );
	}
	elif ( s.isTriangle() )
	{
		DrawTriangle( s.getWorldVertex( 1 ), s.getWorldVertex( 0 ), s.getWorldVertex( 2 ), _color);
	}
	elif ( s.isDiamond() )
	{
		DrawTriangle( s.getWorldVertex( 0 ), s.getWorldVertex( 2 ), s.getWorldVertex( 1 ), _color);
		DrawTriangle( s.getWorldVertex( 2 ), s.getWorldVertex( 0 ), s.getWorldVertex( 3 ), _color);
	}
	elif ( s.isRectangular() )
	{
		DrawTriangle( s.getWorldVertex( 0 ), s.getWorldVertex( 2 ), s.getWorldVertex( 1 ), _color);
		DrawTriangle( s.getWorldVertex( 2 ), s.getWorldVertex( 0 ), s.getWorldVertex( 3 ), _color);
	}
	elif ( s.isPolygonal() )
	{
		for ( int i = 0; i < s.getFacetC(); i++ ) // NOTE : loops on all vertex pair and draw a triangle from the center to the vertices
		{
			DrawTriangle( s.getWorldVertex( i ), s.getCenter(), s.getWorldVertex( ( i + 1 )), _color );
		}
	}
	return true;
}

void RenderObject::onRenderTick() // (re)renders the object
{
	flog( getID() );
	if ( !_isVisible ) return;

	renderSelf();

	OnRenderCall( this );
}