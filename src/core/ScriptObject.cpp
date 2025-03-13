#include "../../inc/core.hpp"

// ================================ CORE METHODS

void ScriptObject::onAdd()
{
	log( "ScriptObject::onAdd()" );
	isActive = true;
}

void ScriptObject::onCpy( const ScriptObject &obj )
{
	log( "ScriptObject::onCpy()" );
	isActive = obj.getIsActive();
}

void ScriptObject::onDel()
{
	log( "ScriptObject::onDel()" );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

ScriptObject::ScriptObject() : BaseObject( E_SCRIPT )
{
	BaseObject::onAdd();
	ScriptObject::onAdd();
}

ScriptObject::ScriptObject( const ScriptObject &obj ) : BaseObject( obj )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
	ScriptObject::onCpy( obj );
}

ScriptObject &ScriptObject::operator=( const ScriptObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::operator=( obj );
	ScriptObject::onCpy( obj );

	return *this;
}

ScriptObject::~ScriptObject() // inverted call order
{
	ScriptObject::onDel();
	BaseObject::onDel();
}

// ================================ ACCESSORS

bool ScriptObject::getIsActive() const { return isActive; }
void ScriptObject::setIsActive( bool active ) { isActive = active; }

// ================================ OPERATORS

// ================================ METHODS

void ScriptObject::onUpdate()	// runs the object's scripts
{
	log( "ScriptObject::onUpdate()" );
	if ( !isActive ) return;
}
