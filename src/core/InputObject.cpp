#include "../../inc/core.hpp"

// ================================ CORE METHODS

void InputsObject::onAdd()
{
	log( "InputsObject::onAdd()" );
	isControlled = true;
}

void InputsObject::onCpy( const InputsObject &obj )
{
	log( "InputsObject::onCpy()" );
	isControlled = obj.getIsControlled();
}

void InputsObject::onDel()
{
	log( "InputsObject::onDel()" );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

InputsObject::InputsObject() : BaseObject( E_INPUTS )
{
	BaseObject::onAdd();
	InputsObject::onAdd();
}

InputsObject::InputsObject( const InputsObject &obj ) : BaseObject( obj )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
	InputsObject::onCpy( obj );
}

InputsObject &InputsObject::operator=( const InputsObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::operator=( obj );
	InputsObject::onCpy( obj );

	return *this;
}

InputsObject::~InputsObject() // inverted call order
{
	InputsObject::onDel();
	BaseObject::onDel();
}

// ================================ ACCESSORS

bool InputsObject::getIsControlled() const { return isControlled; }
void InputsObject::setIsControlled( bool controlled ) { isControlled = controlled; }

// ================================ OPERATORS

// ================================ METHODS

void InputsObject::onInput() // checks conditions based on the global engine inputs
{
	log( "InputsObject::onInput()" );
	if ( !isControlled ) return;
}