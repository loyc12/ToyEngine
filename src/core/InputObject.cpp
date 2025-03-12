#include "../../inc/core.hpp"

// ================================ CORE METHODS

void InputsObject::onInput()
{
	if ( !isControlled ) return;

	// checks conditions based on the global engine inputs
}

void InputsObject::onAdd()
{
	BaseObject::onAdd();
	_type = E_INPUTS;
}
void InputsObject::onCpy( const InputsObject &obj )
{
	BaseObject::onCpy( obj );
	isControlled = obj.isControlled;
}
void InputsObject::onDel()
{
	BaseObject::onDel();
}

// ================================ CONSTRUCTORS / DESTRUCTORS

// ================================ ACCESSORS

bool InputsObject::getIsControlled() const { return isControlled; }
void InputsObject::setIsControlled( bool controlled ) { isControlled = controlled; }

// ================================ OPERATORS

// ================================ METHODS