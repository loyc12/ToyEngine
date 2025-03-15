#include "../../inc/core.hpp"

// ================================ CORE METHODS

void ScriptObject::onAdd()
{
	log( "ScriptObject::onAdd()", DEBUG, _id );
	isActive = true;
}

void ScriptObject::onCpy( const ScriptObject &obj )
{
	log( "ScriptObject::onCpy()", DEBUG, _id );
	isActive = obj.getIsActive();
}

void ScriptObject::onDel()
{
	log( "ScriptObject::onDel()", DEBUG, _id );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

ScriptObject::ScriptObject() : BaseObject( E_SCRIPT ){ ScriptObject::onAdd();}

ScriptObject::ScriptObject( const ScriptObject &obj ) : BaseObject( obj )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
	ScriptObject::onCpy( obj );
}

ScriptObject &ScriptObject::operator=( const ScriptObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	ScriptObject::onCpy( obj );

	return *this;
}

ScriptObject::~ScriptObject() // inverted call order
{
	ScriptObject::onDel();
}

// ================================ ACCESSORS

bool ScriptObject::getIsActive() const { return isActive; }
void ScriptObject::setIsActive( bool active ) { isActive = active; }

// ================================ OPERATORS

// ================================ METHODS

void ScriptObject::onUpdate()	// runs the object's scripts
{
	if ( !isActive ) return;
	log( "ScriptObject::onUpdate()", DEBUG, _id );
}
