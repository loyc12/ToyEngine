#include "../../inc/core.hpp"

// ================================ MEMORY METHODS

uint getNewID() // TMP : put in Engine instead
{
	static uint id = 0;
	return id++;
}

bool BaseObject::addToRegister()
{
	log( "BaseObject::addToRegister()" );
	_id = getNewID();

	// add this object to the register here

	return true;
}
bool BaseObject::delFromRegister()
{
	log( "BaseObject::delFromRegister()" );

	// delete this object from the register here

	return true;

}
// ================================ CORE METHODS

void BaseObject::onAdd()
{
	log( "BaseObject::onAdd()" );
	addToRegister();
}

void BaseObject::onCpy( const BaseObject &obj )
{
	log( "BaseObject::onCpy()" );
	_type = obj.getType();
}

void BaseObject::onDel() // inverted call order
{
	log( "BaseObject::onDel()" );
	delFromRegister();
}


// ================================ CONSTRUCTORS / DESTRUCTORS

BaseObject::BaseObject() : _type( E_BASEOBJ ) { BaseObject::onAdd(); }
BaseObject::BaseObject( objectType_e type ) : _type( type ) { BaseObject::onAdd(); }

BaseObject::BaseObject( const BaseObject &obj ) : _type( E_BASEOBJ )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
}

BaseObject &BaseObject::operator=( const BaseObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );

	return *this;
}

BaseObject::~BaseObject() { BaseObject::onDel(); }

// ================================ ACCESSORS

objectType_e BaseObject::getType() const { return _type; }
uint BaseObject::getID() const { return _id; }

// ================================ OPERATORS

// ================================ METHODS