#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

void ScriptObject::onAdd()
{
	flog( getID() );
	_isActive = true;
}

void ScriptObject::onCpy( const ScriptObject &obj )
{
	flog( getID() );
	_isActive = obj.getIsActive();
}

void ScriptObject::onDel()
{
	flog( getID() );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

ScriptObject::ScriptObject() :
	BaseObject( E_SCRIPT ),
	ShapeObject(),
	RenderObject(),
	PhysicObject()
{
	flog( getID() );
	ScriptObject::onAdd();
}

ScriptObject::ScriptObject( const ScriptObject &obj ) :
	BaseObject( obj ),
	ShapeObject( obj ),
	RenderObject( obj ),
	PhysicObject( obj )
{
	flog( getID() );
	if ( this == &obj ) return;

	ScriptObject::onAdd();
	ScriptObject::onCpy( obj );
}

ScriptObject &ScriptObject::operator=( const ScriptObject &obj )
{
	flog( getID() );
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	ShapeObject::onCpy( obj );
	RenderObject::onCpy( obj );
	PhysicObject::onCpy( obj );

	ScriptObject::onCpy( obj );

	return *this;
}

ScriptObject::~ScriptObject() // automatic inverted call order
{
	flog( getID() );
	ScriptObject::onDel();
	// PhysicObject::onDel();
	// RenderObject::onDel();
	// ShapeObject::onDel();
	// BaseObject::onDel();
}

// ================================ ACCESSORS

bool ScriptObject::getIsActive() const { return _isActive; }
void ScriptObject::setIsActive( bool isActive ){ _isActive = isActive; }

// ================================ OPERATORS

// ================================ METHODS

void ScriptObject::onScriptTick()	// runs the object's scripts
{
	flog( getID() );
	if ( !_isActive ) return;

	OnScriptCall( this ); // DEBUG ?
}
