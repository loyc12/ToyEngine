#include "../../inc/core.hpp"

// ================================ CORE METHODS

void Object2D::onAdd()
{
	InputsObject::onAdd();
	ScriptObject::onAdd();
	PhysicObject::onAdd();
	RenderObject::onAdd();
	_type = E_OBJ2D;
}
void Object2D::onCpy( const Object2D &obj )
{
	InputsObject::onCpy( obj );
	ScriptObject::onCpy( obj );
	PhysicObject::onCpy( obj );
	RenderObject::onCpy( obj );
}
void Object2D::onDel()
{
	InputsObject::onDel();
	ScriptObject::onDel();
	PhysicObject::onDel();
	RenderObject::onDel();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

// ================================ ACCESSORS

// ================================ OPERATORS

// ================================ METHODS