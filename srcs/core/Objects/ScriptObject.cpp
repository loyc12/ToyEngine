#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

void ScriptObject::onAdd()
{
	log( "ScriptObject::onAdd()", DEBUG, _id );
	_isActive = true;
}

void ScriptObject::onCpy( const ScriptObject &obj )
{
	log( "ScriptObject::onCpy()", DEBUG, _id );
	_isActive = obj.getIsActive();
}

void ScriptObject::onDel()
{
	log( "ScriptObject::onDel()", DEBUG, _id );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

ScriptObject::ScriptObject() :
	BaseObject( E_SCRIPT ),
	PhysicObject(),
	RenderObject()
{
	ScriptObject::onAdd();
}

ScriptObject::ScriptObject( const ScriptObject &obj ) :
	BaseObject( obj ),
	PhysicObject( obj ),
	RenderObject( obj )
{
	if ( this == &obj ) return;

	ScriptObject::onAdd();
	ScriptObject::onCpy( obj );
}

ScriptObject &ScriptObject::operator=( const ScriptObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	PhysicObject::onCpy( obj );
	RenderObject::onCpy( obj );
	ScriptObject::onCpy( obj );

	return *this;
}

ScriptObject::~ScriptObject() // automatic inverted call order
{
	ScriptObject::onDel();
	// RenderObject::onDel();
	// PhysicObject::onDel();
	// BaseObject::onDel();
}

// ================================ ACCESSORS

bool ScriptObject::getIsActive() const { return _isActive; }
void ScriptObject::setIsActive( bool isActive ){ _isActive = isActive; }

// ================================ OPERATORS

// ================================ METHODS

void ScriptObject::onScriptTick()	// runs the object's scripts
{
	if ( !_isActive ) return;
	log( "ScriptObject::onScriptTick()", DEBUG, _id );

	OnScriptCall( this ); // DEBUG ?
}
