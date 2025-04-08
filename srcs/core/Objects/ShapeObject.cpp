#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

void ShapeObject::onAdd()
{
	log( "ShapeObject::onAdd()", DEBUG, getID() );

	_isTangible = true;
	_shape = Shape2();
}

void ShapeObject::onCpy( const ShapeObject &obj )
{
	log( "ShapeObject::onCpy()", DEBUG, getID() );

	_isTangible = obj.getIsTangible();
	_shape = obj.getShape();
}

void ShapeObject::onDel()
{
	log( "ShapeObject::onDel()", DEBUG, getID() );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

ShapeObject::ShapeObject() :
	BaseObject( E_SHAPE )
{
	ShapeObject::onAdd();
}

ShapeObject::ShapeObject( const ShapeObject &obj ) : BaseObject( obj )
{
	if ( this == &obj ) return;

	ShapeObject::onAdd();
	ShapeObject::onCpy( obj );
}

ShapeObject &ShapeObject::operator=( const ShapeObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );

	ShapeObject::onCpy( obj );

	return *this;
}

ShapeObject::~ShapeObject() // automatic inverted call order
{
	ShapeObject::onDel();
	// BaseObject::onDel();
}

// ================================ ACCESSORS

Vector2 ShapeObject::getRelPosition( Vector2 pos ) const
{
	Vector2 relPos = Vector2();
	relPos.x = _shape.getCenter().x - pos.x;
	relPos.y = _shape.getCenter().y - pos.y;
	return relPos;
}
Vector2 ShapeObject::getRelScale( Vector2 scl ) const
{
	Vector2 relScale = Vector2();
	relScale.x = _shape.getScales().x == 0 ? 0 : _shape.getScales().x / scl.x;
	relScale.y = _shape.getScales().y == 0 ? 0 : _shape.getScales().y / scl.y;
	return relScale;
}
float ShapeObject::getRelAngle( float angle ) const
{
	float relAngle = _shape.getAngle() - angle;
	if ( relAngle < 0 ) relAngle += 360; // TODO : normalize() instead
	return relAngle;
}

// ================================ MUTATORS

Vector2 ShapeObject::setPosition( const Vector2 &pos )
{
	_shape.setCenter( pos );
	return _shape.getCenter();
}
Vector2 ShapeObject::movePosition( const Vector2 &delta )
{
	_shape.moveCenter( delta );
	return _shape.getCenter();
}


Vector2 ShapeObject::setScale( const Vector2 &scl )
{
	_shape.setScales( scl );
	return _shape.getScales();
}
Vector2 ShapeObject::moveScale( const Vector2 &delta )
{
	_shape.moveCenter( delta );
	return _shape.getScales();
}
Vector2 ShapeObject::changeScale( const Vector2 &scl )
{
	_shape.changeScales( scl );
	return _shape.getScales();
}

float ShapeObject::setAngle( float angle )
{
	_shape.setAngle( angle );
	return _shape.getAngle();
}
float ShapeObject::moveAngle( float delta )
{
	_shape.moveAngle( delta );
	return _shape.getAngle();
}

// ================================ METHODS

void ShapeObject::onShapeTick() // (re)calculates the object's shape
{

}
