#include "../../inc/core.hpp"
#include <cstdlib>

// ================================ MEMORY METHODS

bool BaseObject::setID( objID_t id )
{
	log( "BaseObject::setID()" );

	if ( id == 0 )
	{
		log( "BaseObject::setID() : id cannot be 0", WARN );
		return EXIT_FAILURE;
	}

	_id = id;

	return EXIT_SUCCESS;
}

bool BaseObject::delID()
{
	log( "BaseObject::addToRegister()" );

	if ( _id == 0 )
	{
		log( "BaseObject::setID() : id already 0", INFO );
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

bool BaseObject::addToRegister()
{
	log( "BaseObject::addToRegister()" );

	// add this object to the register here

	return EXIT_SUCCESS;

}

bool BaseObject::delFromRegister()
{
	log( "BaseObject::delFromRegister()" );

	// delete this object from the register here

	return EXIT_SUCCESS;

}
// ================================ CORE METHODS

void BaseObject::onAdd()
{
	log( "BaseObject::onAdd()" );
	if ( _id == 0 ) addToRegister();
}

void BaseObject::onCpy( const BaseObject &obj )
{
	log( "BaseObject::onCpy()" );
	_type = obj.getType();
}

void BaseObject::onDel() // inverted call order
{
	log( "BaseObject::onDel()" );
	if ( _id != 0 ) delFromRegister();
}


// ================================ CONSTRUCTORS / DESTRUCTORS

BaseObject::BaseObject() : _id( 0 ), _type( E_BASEOBJ ){ BaseObject::onAdd(); }
BaseObject::BaseObject( objID_t id ) : _id( id ), _type( E_BASEOBJ ){ BaseObject::onAdd(); }
BaseObject::BaseObject( objectType_e type ) : _type( type ){ BaseObject::onAdd(); }
BaseObject::BaseObject( objID_t id, objectType_e type = E_BASEOBJ ) :  _id( id ), _type( type ){ BaseObject::onAdd(); }

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