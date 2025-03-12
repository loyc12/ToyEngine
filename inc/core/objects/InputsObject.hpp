#ifndef INPUTSOBJECT_HPP
# define INPUTSOBJECT_HPP

# include "./BaseObject.hpp"

class InputsObject : public BaseObject
{
	protected:
		// ================================ ATTRIBUTES
	bool isControlled; // whether this object should check for input

	// ================================ CORE METHODS
		void onInput(); // ENTRYPOINT : acts based on the global engine inputs

		virtual void onAdd();
		virtual void onCpy( const InputsObject &obj );
		virtual void onDel();

	public:
	// ================================ CONSTRUCTORS / DESTRUCTORS
		InputsObject();
		InputsObject( const InputsObject &obj );
		InputsObject &operator=( const InputsObject &obj );
		~InputsObject();

	// ================================ ACCESSORS
		bool getIsControlled() const;			void setIsControlled( bool controlled );

	// ================================ OPERATORS

	// ================================ METHODS
};

#endif // INPUTSOBJECT_HPP