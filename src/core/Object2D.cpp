#include "../../inc/core.hpp"

// ================================ CORE METHODS

void Object2D::onAdd()
{
	log( "Object2D::onAdd()" );
	// isControlled = true;
	// isActive = true;
	// isDynamic = true;
	// isCollide = true;
	// isVisible = true;
}

void Object2D::onCpy( const Object2D &obj )
{
	log( "Object2D::onCpy()" );
	// isControlled = obj.getIsControlled();
	// isActive = obj.getIsActive();
	// isDynamic = obj.getIsDynamic();
	// isCollide = obj.getIsCollide();
	// isVisible = obj.getIsVisible();
}

void Object2D::onDel()
{
	log( "Object2D::onDel()" );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

Object2D::Object2D() : BaseObject( E_OBJ2D )
{
	BaseObject::onAdd();

	InputsObject::onAdd();
	ScriptObject::onAdd();
	PhysicObject::onAdd();
	RenderObject::onAdd();

	Object2D::onAdd();
}

Object2D::Object2D( const Object2D &obj )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );

	InputsObject::onCpy( obj );
	ScriptObject::onCpy( obj );
	PhysicObject::onCpy( obj );
	RenderObject::onCpy( obj );

	Object2D::onCpy( obj );
}

Object2D &Object2D::operator=( const Object2D &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );

	InputsObject::onCpy( obj );
	ScriptObject::onCpy( obj );
	PhysicObject::onCpy( obj );
	RenderObject::onCpy( obj );

	Object2D::onCpy( obj );

	return *this;
}

Object2D::~Object2D() // inverted call order
{
	Object2D::onDel();

	RenderObject::onDel();
	PhysicObject::onDel();
	ScriptObject::onDel();
	InputsObject::onDel();

	BaseObject::onDel();
}

// ================================ ACCESSORS

// ================================ OPERATORS

// ================================ METHODS