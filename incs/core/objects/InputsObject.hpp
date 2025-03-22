#ifndef INPUTSOBJECT_HPP
# define INPUTSOBJECT_HPP

# include "./BaseObject.hpp"

struct inputs_s
{
	float DT;

	//BASE
	bool LEFT;
	bool RIGHT;
	bool FORE;
	bool BACK;
	bool SPACE;
	bool ENTER;
	bool SHIFT;
	bool CTRL;
	bool ALT;
	bool TAB;

	//MOUSE
	bool CLICK_LEFT;
	bool CLICK_MID;
	bool CLICK_RIGHT;
	bool SCROLL_UP;
	bool SCROLL_DOWN;

	//KEYBOARD
	bool Q;
	bool E;
	bool R;
	bool F;
	bool Z;
	bool X;
	bool C;
	bool V;
};

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