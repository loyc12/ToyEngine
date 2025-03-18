#include "../../incs/core.hpp"

// ================================ CORE METHODS

void InputsObject::onAdd()
{
	log( "InputsObject::onAdd()", DEBUG, _id );
	isControlled = true;
}

void InputsObject::onCpy( const InputsObject &obj )
{
	log( "InputsObject::onCpy()", DEBUG, _id );
	isControlled = obj.getIsControlled();
}

void InputsObject::onDel()
{
	log( "InputsObject::onDel()", DEBUG, _id );
}

// ================================ CONSTRUCTORS / DESTRUCTORS

InputsObject::InputsObject() : BaseObject( E_INPUTS ){ InputsObject::onAdd();}

InputsObject::InputsObject( const InputsObject &obj ) : BaseObject( obj )
{
	if ( this == &obj ) return;

	BaseObject::onCpy( obj );
	InputsObject::onCpy( obj );
}

InputsObject &InputsObject::operator=( const InputsObject &obj )
{
	if ( this == &obj ) return *this;

	BaseObject::onCpy( obj );
	InputsObject::onCpy( obj );

	return *this;
}

InputsObject::~InputsObject() // inverted call order
{
	InputsObject::onDel();
}

// ================================ ACCESSORS

bool InputsObject::getIsControlled() const { return isControlled; }
void InputsObject::setIsControlled( bool controlled ) { isControlled = controlled; }

// ================================ OPERATORS

// ================================ METHODS

void InputsObject::onInput() // checks conditions based on the global engine inputs
{
	if ( !isControlled ) return;
	log( "InputsObject::onInput()", DEBUG, _id );
}