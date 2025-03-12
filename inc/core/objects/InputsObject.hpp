#ifndef INPUTSOBJECT_HPP
# define INPUTSOBJECT_HPP

# include "./BaseObject.hpp"

class InputsObject : public BaseObject
{
	protected:
	// ================================ ATTRIBUTES

	// ================================ CORE METHODS
		void onAdd();
		void onCpy();
		void ondel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		InputsObject();
		InputsObject( const InputsObject &obj );
		InputsObject &operator=( const InputsObject &obj );
		~InputsObject();

	// ================================ ACCESSORS

	// ================================ OPERATORS

	// ================================ METHODS
};

#endif // INPUTSOBJECT_HPP