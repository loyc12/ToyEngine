#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

void Object2D::onAdd()
{
	flog( getID() );
	// _isActive = true;
	// _isDynamic = true;
	// _isCollide = true;
	// _isVisible = true;
}

void Object2D::onCpy( const Object2D &obj )
{
	flog( getID() );
	// _isActive = obj.getIsActive();
	// _isDynamic = obj.getIsDynamic();
	// _isCollide = obj.getIsCollide();
	// _isVisible = obj.getIsVisible();

	( void )obj;
}

void Object2D::onDel()
{
	flog( getID() );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Object2D::Object2D() :
	BaseObject( E_OBJ2D ),
	ShapeObject(),
	RenderObject(),
	PhysicObject(),
	ScriptObject()
{
	flog( getID() );
	Object2D::onAdd();
}

Object2D::Object2D( const Object2D &obj ) :
	BaseObject( E_OBJ2D ),
	ShapeObject( obj ),
	RenderObject( obj ),
	PhysicObject( obj ),
	ScriptObject( obj )
{
	flog( getID() );
	if ( this == &obj ) return;

	Object2D::onAdd();
	Object2D::onCpy( obj );
}

Object2D &Object2D::operator=( const Object2D &obj )
{
	flog( getID() );
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	ShapeObject::onCpy( obj );
	RenderObject::onCpy( obj );
	PhysicObject::onCpy( obj );
	ScriptObject::onCpy( obj );

	Object2D::onCpy( obj );

	return *this;
}

Object2D::~Object2D() // automatic inverted call order
{
	flog( getID() );
	Object2D::onDel();
	// ScriptObject::onDel();
	// PhysicObject::onDel();
	// RenderObject::onDel();
	// ShapeObject::onDel();
	// BaseObject::onDel();
}

// ================================ ACCESSORS / MUTATORS

// ================================ OBJECTS FACTORY

void GenerateObject2D( Shape2 shape, Color color, bool isTangible, bool isDynamic, bool isCollide, bool isVisible, bool isActive )
{
	flog( 0 );

	Object2D *obj = new Object2D; // NOTE : automatically added to the engine's object list

	obj->setShape( shape );
	obj->setColor( color );

	obj->setIsTangible( isTangible );
	obj->setIsDynamic(  isDynamic  );
	obj->setIsCollide(  isCollide  );
	obj->setIsVisible(  isVisible  );
	obj->setIsActive(   isActive   );
}