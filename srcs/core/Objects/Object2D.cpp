#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

void Object2D::onAdd()
{
	log( "Object2D::onAdd()", DEBUG, _id );
	// _isActive = true;
	// _isDynamic = true;
	// _isCollide = true;
	// _isVisible = true;
}

void Object2D::onCpy( const Object2D &obj )
{
	log( "Object2D::onCpy()", DEBUG, _id );
	// _isActive = obj.getIsActive();
	// _isDynamic = obj.getIsDynamic();
	// _isCollide = obj.getIsCollide();
	// _isVisible = obj.getIsVisible();

	( void )obj;
}

void Object2D::onDel()
{
	log( "Object2D::onDel()", DEBUG, _id );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Object2D::Object2D() :
	BaseObject( E_OBJ2D ),
	PhysicObject(),
	RenderObject(),
	ScriptObject()
{
	Object2D::onAdd();
}

Object2D::Object2D( const Object2D &obj ) :
	BaseObject( E_OBJ2D ),
	PhysicObject( obj ),
	RenderObject( obj ),
	ScriptObject( obj )
{
	if ( this == &obj ) return;

	Object2D::onAdd();
	Object2D::onCpy( obj );
}

Object2D &Object2D::operator=( const Object2D &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );

	PhysicObject::onCpy( obj );
	RenderObject::onCpy( obj );
	ScriptObject::onCpy( obj );
	Object2D::onCpy( obj );

	return *this;
}

Object2D::~Object2D() // automatic inverted call order
{
	Object2D::onDel();
	// ScriptObject::onDel();
	// RenderObject::onDel();
	// PhysicObject::onDel();
	// BaseObject::onDel();
}

// ================================ ACCESSORS

// ================================ OPERATORS

// ================================ METHODS

// ================================ OBJECTS FACTORY

void GenerateObject2D( shape_e shape, Color color, Vector2 size, Vector2 pos, bool isActive, bool isDynamic, bool isCollide, bool isVisible )
{
	log( "GenerateObject2D()", DEBUG );

	Object2D *obj = new Object2D;

	obj->setShape( shape );
	obj->setColor( color );
	obj->setSize( size );
	obj->setPosition( pos );

	obj->setIsActive( isActive );
	obj->setIsDynamic( isDynamic );
	obj->setIsCollide( isCollide );
	obj->setIsVisible( isVisible );

}