#include "../../inc/core.hpp"

// ================================ CORE METHODS

void ScriptObject::onUpdate()
{
	if ( !isActive ) return;

	// runs the object's scripts
}

void ScriptObject::onAdd()
{
	BaseObject::onAdd();
	_type = E_SCRIPT;
}
void ScriptObject::onCpy( const ScriptObject &obj )
{
	BaseObject::onCpy( obj );
	isActive = obj.isActive;
}
void ScriptObject::onDel()
{
	BaseObject::onDel();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

// ================================ ACCESSORS

bool ScriptObject::getIsActive() const { return isActive; }
void ScriptObject::setIsActive( bool active ) { isActive = active; }

// ================================ OPERATORS

// ================================ METHODS