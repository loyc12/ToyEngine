#include "../../../incs/core.hpp"
#include "../../../incs/game.hpp"

// ================================ CORE METHODS

void ScriptObject::onAdd()
{
	log( "ScriptObject::onAdd()", DEBUG, getID() );
	_isActive = true;
}

void ScriptObject::onCpy( const ScriptObject &obj )
{
	log( "ScriptObject::onCpy()", DEBUG, getID() );
	_isActive = obj.getIsActive();
}

void ScriptObject::onDel()
{
	log( "ScriptObject::onDel()", DEBUG, getID() );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

ScriptObject::ScriptObject() :
	BaseObject( E_SCRIPT ),
	ShapeObject(),
	RenderObject(),
	PhysicObject()
{
	ScriptObject::onAdd();
}

ScriptObject::ScriptObject( const ScriptObject &obj ) :
	BaseObject( obj ),
	ShapeObject( obj ),
	RenderObject( obj ),
	PhysicObject( obj )
{
	if ( this == &obj ) return;

	ScriptObject::onAdd();
	ScriptObject::onCpy( obj );
}

ScriptObject &ScriptObject::operator=( const ScriptObject &obj )
{
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
	if ( !_isActive ) return;
	log( "ScriptObject::onScriptTick()", DEBUG, getID() );

	OnScriptCall( this ); // DEBUG ?
}
