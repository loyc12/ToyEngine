#ifndef INPUTSOBJECT_HPP
# define INPUTSOBJECT_HPP

# include "./BaseObject.hpp"

class InputsObject : virtual public BaseObject
{
	protected:
		// ================================ ATTRIBUTES
		bool isControlled; // whether this object should check for input

	// ================================ CORE METHODS
		void onAdd() override;
		void onCpy( const InputsObject &obj );
		void onDel() override;

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
		void onInput() override; // ENTRYPOINT : acts based on the global engine inputs
};

#endif // INPUTSOBJECT_HPP