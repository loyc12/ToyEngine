#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

void RenderObject::onAdd()
{
	log( "RenderObject::onAdd()", DEBUG, _id );
	isVisible = true;

	// set default color and shape
	_color = WHITE;
	_shape = SHAPE_CIRCLE;
}

void RenderObject::onCpy( const RenderObject &obj )
{
	log( "RenderObject::onCpy()", DEBUG, _id );
	isVisible = obj.getIsVisible();
}

void RenderObject::onDel()
{
	log( "RenderObject::onDel()", DEBUG, _id );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

RenderObject::RenderObject() : BaseObject( E_RENDER ) { RenderObject::onAdd(); }

RenderObject::RenderObject( const RenderObject &obj ) : BaseObject( obj )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
	RenderObject::onCpy( obj );
}

RenderObject &RenderObject::operator=( const RenderObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	RenderObject::onCpy( obj );

	return *this;
}

RenderObject::~RenderObject() // inverted call order
{
	RenderObject::onDel();
}

// ================================ ACCESSORS

bool RenderObject::getIsVisible() const { return isVisible; }
void RenderObject::setIsVisible( bool visible ) { isVisible = visible; }

shape_e RenderObject::getShape() const { return _shape; }
void    RenderObject::setShape( shape_e shape ) { _shape = shape; }

Color RenderObject::getColor() const { return _color; }
void  RenderObject::setColor( Color color ) { _color = color; }

// ================================ OPERATORS

// ================================ METHODS

void RenderObject::onRenderTick() // (re)renders the object
{
	if ( !isVisible ) return;
	log( "RenderObject::onRenderTick()", DEBUG, _id );

	if ( _shape == SHAPE_CIRCLE )
	{
		DrawCircle( int( _pos.x ), int( _pos.y ), getAvgRadius(), _color );
	}
	else if ( _shape == SHAPE_RECT )
	{
		DrawRectangle( int( getLeft().x ), int( getTop().y ), int( getSize().x * 2 ), int( getSize().y * 2 ), _color );
	}
	else if ( _shape == SHAPE_LINE )
	{
		DrawLine( int( getBot().x ), int( getBot().y ), int( getTop().x ), int( getTop().y ), _color );
	}
	else if ( _shape == SHAPE_BOX )
	{
		DrawLine( int( getTopLeft().x ), int( getTopLeft().y ), int( getTopRight().x ), int( getTopRight().y ), _color );
		DrawLine( int( getTopRight().x ), int( getTopRight().y ), int( getBotRight().x ), int( getBotRight().y ), _color );
		DrawLine( int( getBotRight().x ), int( getBotRight().y ), int( getBotLeft().x ), int( getBotLeft().y ), _color );
		DrawLine( int( getBotLeft().x ), int( getBotLeft().y ), int( getTopLeft().x ), int( getTopLeft().y ), _color );
	}
	else
	{
		log( "RenderObject::onRenderTick() : unknown shape", WARN, _id );
	}

	OnRenderCall( this );
}