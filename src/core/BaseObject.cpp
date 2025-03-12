#include "../../inc/core.hpp"

// ================================ CORE METHODS

bool BaseObject::addToRegister()
{
	_id = 0; // use global id instead ?

	// add this object to the register
	return true;
}
bool BaseObject::delFromRegister()
{
	// delete this object from the register
	return true;
}

void BaseObject::onAdd()
{
	_type = E_BASEOBJ;
}
void BaseObject::onCpy( const BaseObject &obj )
{
	_type = obj._type;
	// copy the object's attributes
}
void BaseObject::onDel()
{
}

// ================================ CONSTRUCTORS / DESTRUCTORS

BaseObject::BaseObject()
{
	addToRegister();
	onAdd();
}
BaseObject::BaseObject( const BaseObject &obj )
{
	onCpy( obj );
}
BaseObject &BaseObject::operator=( const BaseObject &obj )
{
	onCpy( obj );
	return *this;
}
BaseObject::~BaseObject()
{
	delFromRegister();
	onDel();
}

// ================================ ACCESSORS

objectType_e BaseObject::getType() const { return _type; }
uint BaseObject::getID() const { return _id; }

// ================================ OPERATORS

// ================================ METHODS